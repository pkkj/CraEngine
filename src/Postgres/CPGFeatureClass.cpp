/*
 * CPGFeatClass.cpp
 *
 *  Created on: 2010-12-28
 *      Author: pkkj
 */

#include "CPGFeatureClass.h"
#include "Utils.h"
#include "CSQLConstructor.h"
#include "CEWKTWriter.h"
using namespace SQLUtils;
namespace DataSource {

CPGFeatClass::CPGFeatClass() {
	mConnRead = NULL;
	mConnWrite = NULL;
}

CPGFeatClass::~CPGFeatClass() {
	disconnect();
}

FIELD_TYPE CPGFeatClass::getPgFieldTypeByName(const char *data_type) {
	if (strcmp(data_type, "bool") == 0)
		return FTYPE_BOOLEAN;
	if (strcmp(data_type, "int4") == 0)
		return FTYPE_INTEGER;
	if (strcmp(data_type, "varchar") == 0)
		return FTYPE_VARCHAR;
	if (strcmp(data_type, "float8") == 0)
		return FTYPE_DOUBLE;
	if (strcmp(data_type, "numeric") == 0)
		return FTYPE_NUMERIC;
	if (strcmp(data_type, "geometry") == 0)
		return FTYPE_GEOMETRY;

	return FTYPE_UNKNOWN;
}

string CPGFeatClass::getPgFieldNameByType(const FIELD_TYPE type) {
	if (type == FTYPE_BOOLEAN)
		return "bool";
	if (type == FTYPE_INTEGER)
		return "int4";
	if (type == FTYPE_VARCHAR)
		return "varchar";
	if (type == FTYPE_DOUBLE)
		return "float8";
	if (type == FTYPE_GEOMETRY)
		return "geometry";
	if (type == FTYPE_NUMERIC)
		return "numeric";
	return "";
}
string CPGFeatClass::insertFieldExp(string fieldName, FIELD_TYPE type) {
	if (type == FTYPE_BOOLEAN) {
		return "boolout(" + fieldName + ")";
	} else if (type == FTYPE_GEOMETRY) {
		return "ST_AsEWKB(" + fieldName + ")";
	}
	return fieldName + "::text";
}
string CPGFeatClass::getSpatialRefFuncByType(CSpatialFilter::SPATIAL_RELATION rel,
		CSpatialFilter::SPATIAL_REL_TYPE &type) {
	string Ret;
	switch (rel) {
	case CSpatialFilter::SPATIALREL_UNDEFINED:
		Ret = "";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_CROSS:
		Ret = "ST_Crosses";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_CONTAIN:
		Ret = "ST_Contains";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_COVER:
		Ret = "ST_Covers";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_COVERED_BY:
		Ret = "ST_CoveredBy";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_DISJOINT:
		Ret = "ST_Disjoint";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_WITHIN:
		Ret = "ST_Within";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_INTERSECT:
		Ret = "ST_Intersects";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_EQUAL:
		Ret = "ST_Equals";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_TOUCH:
		Ret = "ST_Touches";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_OVERLAP:
		Ret = "ST_Overlaps";
		type = CSpatialFilter::SPATIALRELT_FUNC;
		break;
	case CSpatialFilter::SPATIALREL_INTERSECT_RECT:
		Ret = "&&";
		type = CSpatialFilter::SPATIALRELT_OPERATOR;
		break;
	default:
		;
	}
	return Ret;
}

void CPGFeatClass::loadField() {
	string query;
	PGresult *queryRes;
	string oid;
	// get the oid of the table;
	query = "SELECT oid FROM pg_class WHERE relname = " + SQLInsertString(TableName);
	queryRes = mConnRead->PQexec(query);
	oid = string(PQgetvalue(queryRes, 0, 0));
	PQclear(queryRes);

	// get primary key info
	int priKeyIdx = -1;
	query = "SELECT conkey FROM pg_constraint WHERE contype = 'p' AND conrelid = " + oid;
	queryRes = mConnRead->PQexec(query);
	if (PQntuples(queryRes) > 0) {
		string PKStr = string(PQgetvalue(queryRes, 0, 0));
		sscanf(PKStr.c_str(), "{%d}", &priKeyIdx);
	}
	PQclear(queryRes);

	query
			= "SELECT column_name, ordinal_position, udt_name, is_nullable, column_default, character_maximum_length"
				", numeric_precision, numeric_scale FROM information_schema.columns WHERE table_name='"
					+ TableName + "' ORDER BY ordinal_position ASC";

	queryRes = mConnRead->PQexec(query);

	int NumFields = PQntuples(queryRes);

	Fields.normalFID = vector<int> (NumFields + 1);
	Fields.hasGeometry = false;

	for (int i = 0; i < NumFields; i++) {
		CField field;
		field.Name = string(PQgetvalue(queryRes, i, 0));
		field.Num = atoi(PQgetvalue(queryRes, i, 1));
		field.Type = getPgFieldTypeByName(PQgetvalue(queryRes, i, 2));
		field.NotNull = PQgetvalue(queryRes, i, 3)[0] == 'N';
		field.DefaultValue = PQgetvalue(queryRes, i, 4);
		field.Length = 0;
		if (field.Type == FTYPE_VARCHAR) {
			field.Length = atoi(PQgetvalue(queryRes, i, 5));
		}
		if (field.Type == FTYPE_NUMERIC) {
			field.Length = atoi(PQgetvalue(queryRes, i, 6));
			field.Precision = atoi(PQgetvalue(queryRes, i, 7));
		}
		if (field.Type == FTYPE_GEOMETRY) {
			Fields.hasGeometry = true;
		}

		if (field.DefaultValue == "nextval('" + TableName + "_" + field.Name + "_seq'::regclass)")
			field.AutoInc = true;
		else
			field.AutoInc = false;

		if (field.Type == FTYPE_GEOMETRY)
			Fields.mGeoField = field;
		else if (field.Num == priKeyIdx)
			Fields.mPriField = field;
		else {
			Fields.normalFID[i + 1] = Fields.mFields.size();
			Fields.mMapFieldID[field.Name] = Fields.mFields.size();
			Fields.mFields.push_back(field);
		}

	}
}

CFeature *CPGFeatClass::createFeature() {
	CFeature *pFeat = new CFeature(this);
	return pFeat;
}

bool CPGFeatClass::addFeature(CFeature *pFeat) {
	string query;
	bool success = true;
	CSQLInsertConstructor constructor(TableName);

	printf("pFeat->FieldCount() %d\n", pFeat->FieldCount());
	constructor.InsertValue(Fields.mPriField.Name, Int2Str(pFeat->FID), CSQLValueType::SQL_NUMERIAL);
	if (Fields.hasGeometry) {
		IO::CEWKTWriter writer;
		const CGeometry *geom = pFeat->Shape->getGeometry();
		string geostr = writer.WriteGeometry(geom);
		geostr = "ST_GeomFromEWKT('" + geostr + "')";
		constructor.InsertValue(Fields.mGeoField.Name, geostr, CSQLValueType::SQL_NUMERIAL);
	}
	for (size_t i = 0; i < pFeat->FieldCount(); i++) {
		if (pFeat->GetValue(i) != "") {
			switch (Fields.mFields[i].Type) {
			case FTYPE_VARCHAR:
				constructor.InsertValue(pFeat->GetFieldName(i), pFeat->GetValue(i),
						CSQLValueType::SQL_STRING);
				break;
			case FTYPE_BOOLEAN:
				constructor.InsertValue(pFeat->GetFieldName(i), pFeat->GetValue(i),
						CSQLValueType::SQL_BOOLEAN);
				break;
			default:
				constructor.InsertValue(pFeat->GetFieldName(i), pFeat->GetValue(i),
						CSQLValueType::SQL_NUMERIAL);
			}
		}
	}
	query = constructor.Construct();
	try {
		mConnWrite->PQexecNR("BEGIN");
		PGresult *res = mConnWrite->PQexec(query);
		if (PQresultStatus(res) == PGRES_FATAL_ERROR)
			throw(CPostgreException(res));
		PQclear(res);
		mConnWrite->PQexecNR("COMMIT");
	} catch (CPostgreException &e) {
		mConnWrite->PQexecNR("ROLLBACK");
		e.ShowMessage();
		success = false;
	}
	return success;

}
bool CPGFeatClass::deleteFeature(int featID) {
	bool success = true;
	try {
		string query = "DELETE FROM " + TableName + " WHERE " + Fields.mPriField.Name + " = "
				+ Int2Str(featID);
		mConnWrite->PQexecNR("BEGIN");
		PGresult *res = mConnWrite->PQexec(query);
		if (PQresultStatus(res) == PGRES_FATAL_ERROR)
			throw(CPostgreException(res));
		PQclear(res);
		mConnWrite->PQexecNR("COMMIT");
	} catch (CPostgreException &e) {
		mConnWrite->PQexecNR("ROLLBACK");
		e.ShowMessage();
		success = false;
	}
	return success;
}

bool CPGFeatClass::updateFeature(CFeature *pFeat) {
	string query;
	CSQLUpdateConstructor constructor(TableName);
	for (size_t i = 0; i < pFeat->HasValueField.size(); i++) {
		CSQLValueType::SQL_VALUE_TYPE type;
		if (Fields.mFields[i].Type == FTYPE_VARCHAR)
			type = CSQLValueType::SQL_STRING;
		else if (Fields.mFields[i].Type == FTYPE_BOOLEAN)
			type = CSQLValueType::SQL_BOOLEAN;
		else
			type = CSQLValueType::SQL_NUMERIAL;
		string value = pFeat->GetValueByInnerIdx(i);
		if (value != "")
			constructor.InsertValue(pFeat->GetFieldName(i), value, type);
	}
	// Add the geometry key
	if (pFeat->Shape) {
		const CGeometry *geom = pFeat->Shape->getGeometryRO();
		IO::CEWKTWriter writer;
		string geostr = writer.WriteGeometry(geom);
		geostr = "ST_GeomFromEWKT('" + geostr + "')";
		constructor.InsertValue(Fields.mGeoField.Name, geostr, CSQLValueType::SQL_NUMERIAL);
	}
	query = constructor.Construct();
	// Add primary key information
	query += " WHERE " + Fields.mPriField.Name + "=" + Int2Str(pFeat->FID);
	//printf("%s\n", query.c_str());
	bool success = true;
	try {
		mConnWrite->PQexecNR("BEGIN");
		PGresult *res = mConnWrite->PQexec(query);
		if (PQresultStatus(res) == PGRES_FATAL_ERROR)
			throw(CPostgreException(res));
		PQclear(res);
		mConnWrite->PQexecNR("COMMIT");
	} catch (CPostgreException &e) {
		mConnWrite->PQexecNR("ROLLBACK");
		e.ShowMessage();
		success = false;
	}
	return success;
}
bool CPGFeatClass::connect(Core::CPropertySet dbInfo) {
	// the format of dbInfo, splited by ';'
	/*	mPGHost;mPGPort;mPGOptions;mPGTty;mPGDBName;mPGUser;mPGPasswd;tablename	 */

	mConnRead = new CPGConnection(dbInfo);
	mConnRead->connect();

	mConnWrite = new CPGConnection(dbInfo);
	mConnWrite->connect();
	loadField();

	if (Fields.hasGeometry)
		getGeometryType();
	else {
		SRID = -1;
		GeometryType = Core::COpenGISType::OGIS_UNKNOWN;
	}
#ifdef debug
	/*printf("SRID IS %d\n", SRID);
	 printf("GEOTYPE IS %s\n", Core::COpenGISType::GetNameByType(GeometryType).c_str());*/
#endif
	return true;
}

bool CPGFeatClass::disconnect() {
	mConnRead->disconnect();
	delete mConnRead;
	mConnWrite->disconnect();
	delete mConnWrite;

	mConnRead = NULL;
	mConnWrite = NULL;
	return true;
}

void CPGFeatClass::getGeometryType() {
	string query = "SELECT srid, type, coord_dimension FROM geometry_columns WHERE f_table_name = "
			+ SQLInsertString(TableName);
	////printf("%s\n", query.c_str());
	PGresult *queryRes = mConnRead->PQexec(query);
	SRID = atoi(PQgetvalue(queryRes, 0, 0));
	string type = string(PQgetvalue(queryRes, 0, 1));

	GeometryType = Core::COpenGISType::GetTypeByName(type);
	int codim = atoi(PQgetvalue(queryRes, 0, 2));
	if (codim == 3) {
		HasZ = true;
	}
	PQclear(queryRes);
}

CRectangle CPGFeatClass::getExtent() {
	CRectangle rect;
	if (Fields.hasGeometry) {
		try {
			string query = "SELECT st_extent(" + Fields.mGeoField.Name + ")" + " FROM " + TableName;
			PGresult *res = mConnRead->PQexec(query);
			if (PQresultStatus(res) == PGRES_FATAL_ERROR)
				throw(CPostgreException(res));
			double x1, y1, x2, y2;
			sscanf(PQgetvalue(res, 0, 0), "BOX(%lf %lf,%lf %lf)", &x1, &y1, &x2, &y2);
			rect = CRectangle(x1, y1, x2, y2);
		} catch (CPostgreException &e) {
			e.ShowMessage();
		}
	}
	return rect;
}

bool CPGFeatClass::getFeature(CFeatureCursor *cursor, int featnum) {
	bool success = true;
	int nFeat;
	try {
		string query = "FETCH FORWARD " + Int2Str(featnum) + " FROM " + cursor->CursorName;
		PGresult *res = mConnRead->PQexec(query.c_str());
		if ((PQresultStatus(res) != PGRES_TUPLES_OK)) {
			throw(CPostgreException(res));
		}
		nFeat = PQntuples(res);
		if (nFeat == 0) {
			mConnRead->closeCursor(cursor->CursorName);
			return false;
		}
		for (int i = 0; i < nFeat; i++) {
			int j = 0;
			CFeature feature(this);
			// Fetch the primary key
			feature.FID = atoi(PQgetvalue(res, i, j++));
			// Fetch the geometry
			if (cursor->FetchGeometry) {
				int length = PQgetlength(res, i, j);
				unsigned char *ans = (unsigned char *) PQgetvalue(res, i, j);
				CEwkbGeometry *ewkbGeom = new CEwkbGeometry(ans, length);
				feature.Shape = new CGeometryExt();
				feature.Shape->initFromEwkb(ewkbGeom);
				feature.Shape->SRID = SRID;
				j++;
			}
			for (size_t beg = 0; j < (size_t) PQnfields(res); j++, beg++) {
				string value = string(PQgetvalue(res, i, j));
				feature.SetValue(cursor->mSubFieldMap[beg], value);
			}
			cursor->mFeatureQueue.push(feature);
			cursor->mFetched++;

		}
		PQclear(res);
	} catch (CPostgreException &e) {
		e.ShowMessage();
		mConnRead->closeCursor(cursor->CursorName);
		success = false;
	}

	return success;
}

bool CPGFeatClass::featureByID(int fid, CFeature &feature, bool fetchGeometry, string subFields) {
	CQueryFilter filter;
	CFeatureCursor cursor;
	filter.FetchGeometry = fetchGeometry;
	filter.SetSubField(subFields);
	filter.WhereClause = Fields.mPriField.Name + "=" + Int2Str(fid);
	filter.searchLimit = 1;
	if (!search(&filter, cursor))
		return false;
	if (!cursor.NextFeature(feature))
		return false;
	// To close the cursor
	mConnRead->closeCursor(cursor.CursorName);
	return true;
}

bool CPGFeatClass::search(CQueryFilter *filter, CFeatureCursor &cursor) {
	vector<string> subfields = filter->GetAllSubField();
	// If nothing in subfield, then add all fields to the subfield (default search all)
	if (subfields.size() == 0) {
		for (size_t i = 0; i < Fields.FieldCount(); i++) {
			subfields.push_back(Fields.GetField(i).Name);
		}
	}
	// Examine the subfileds in the constructor, whether they are in the CFields
	// And then map the index from subfield to all field;
	cursor.mSubFieldMap.clear();
	for (size_t i = 0; i < subfields.size(); i++) {
		int idx = Fields.FindField(subfields[i]);
		if (idx == -1) // Unable to find a field
		{
			return false;
		} else {
			cursor.mSubFieldMap.push_back(idx);
			subfields[i] = insertFieldExp(Fields.GetField(idx).Name, Fields.GetField(idx).Type);
		}
	}

	// Construct the CSQLSelectConstructor object
	CSQLSelectConstructor constructor(TableName);

	// Add the primary key to the constructor
	constructor.SubField.push_back(insertFieldExp(Fields.mPriField.Name, FTYPE_INTEGER));

	// Add the geometry field to the constructor
	cursor.FetchGeometry = filter->FetchGeometry;
	if (cursor.FetchGeometry) {
		if (Fields.hasGeometry)
			constructor.SubField.push_back(insertFieldExp(Fields.mGeoField.Name, FTYPE_GEOMETRY));
		else
			return false; // Error, no geometry field in this table
	}
	for (size_t i = 0; i < subfields.size(); i++) {
		constructor.SubField.push_back(subfields[i]);
	}
	constructor.searchLimit = filter->searchLimit;

	// Deal with spatial query
	constructor.WhereClause = filter->WhereClause;
	CSpatialFilter *sf = dynamic_cast<CSpatialFilter*> (filter);
	if (sf != NULL) {
		string spatialWhere = consSpatialWhere(sf);
		if (spatialWhere != "") {
			if (filter->WhereClause != "")
				constructor.WhereClause += " AND ";
			constructor.WhereClause += spatialWhere;
		}
	}

	string query = constructor.Construct();

	cursor.SetCursorID();
	cursor.CursorName = "cur" + Int2Str(cursor.CursorID);
	cursor.mFeatClass = this;
	bool success = true;
	if (!mConnRead->openCursor(cursor.CursorName, query))
		success = false;
	return success;
}

string CPGFeatClass::consSpatialWhere(CSpatialFilter *filter) {
	string Ret;

	IO::CEWKTWriter writer;
	CSpatialFilter::SPATIAL_REL_TYPE type;

	// First, check whether there is bounding rectangle
	if (!filter->Rect.isEmpty()) {

		//SetSRID('BOX3D(191232 243117,191232 243119)'::box3d,-1);
		/*Ret += Fields.mGeoField.Name + " && SetSRID(" + filter->Rect.AsBox3d() + ","
				+ Int2Str(SRID) + ") ";*/
		Ret += " intersects(" + Fields.mGeoField.Name + ",SetSRID(" + filter->Rect.AsBox3d() + ","
		 + Int2Str(SRID) + ")) ";

	}
	// Then, check whether there is a geometry.
	if (filter->Geometry == NULL)
		return Ret;
	filter->Geometry->setSRID(SRID);
	string geom = writer.WriteGeometry(filter->Geometry);
	if (filter->Relation != CSpatialFilter::SPATIALREL_UNDEFINED) {
		string func = getSpatialRefFuncByType(filter->Relation, type);
		if (Ret != "")
			Ret += " AND ";
		if (type == CSpatialFilter::SPATIALRELT_FUNC) {
			Ret += func + "(" + Fields.mGeoField.Name + "," + SQLInsertString(geom) + ") ";
		} else {
			Ret += Fields.mGeoField.Name + " " + func + " " + SQLInsertString(geom) + " ";
		}
	} else if (filter->Rel9Dem != "") {
		if (Ret != "")
			Ret += " AND ";
		Ret += "ST_Relate(" + Fields.mGeoField.Name + "," + SQLInsertString(geom) + ","
				+ SQLInsertString(filter->Rel9Dem) + ") ";
	}

	return Ret;
}

bool CPGFeatClass::addField(CField field) {
	bool success = true;
	if (Fields.FindField(field.Name) != -1)
		return false;

	try {
		string query;
		PGresult *res;
		mConnWrite->PQexecNR("BEGIN");
		query = "ALTER TABLE " + TableName + " ADD COLUMN " + field.Name + " "
				+ getPgFieldNameByType(field.Type);
		// special attention: string's length
		if (field.Type == FTYPE_VARCHAR) {
			query += "(" + Int2Str(field.Length) + ")";
		} else if (field.Type == FTYPE_NUMERIC) {
			query += "(" + Int2Str(field.Length) + "," + Int2Str(field.Precision) + ")";
		}
		//printf("%s\n", query.c_str());
		res = mConnWrite->PQexec(query);
		if (PQresultStatus(res) == PGRES_FATAL_ERROR)
			throw(CPostgreException(res));
		PQclear(res);
		if (field.NotNull) {
			query = "ALTER TABLE " + TableName + " ALTER COLUMN " + field.Name + " SET NOT NULL";
			//printf("%s\n", query.c_str());
			res = mConnWrite->PQexec(query);
			if (PQresultStatus(res) == PGRES_FATAL_ERROR)
				throw(CPostgreException(res));
			PQclear(res);
		}
		// Deal with auto increase
		if (field.AutoInc) {
			field.DefaultValue = "nextval(" + TableName + "_" + field.Name + "_seq'::regclass);";
		}
		// Deal with default value
		if (field.DefaultValue != "") {
			string value = field.DefaultValue;
			if (field.Type == FTYPE_VARCHAR)
				value = "'" + value + "'::character varying";
			query = "ALTER TABLE " + TableName + " ALTER COLUMN " + field.Name + " SET DEFAULT "
					+ value;
			res = mConnWrite->PQexec(query);
			if (PQresultStatus(res) == PGRES_FATAL_ERROR)
				throw(CPostgreException(res));
			PQclear(res);
		}
		// Deal with comment
		if (field.Comment != "") {
			query = "COMMENT ON COLUMN " + TableName + "." + field.Name + " IS '" + field.Comment
					+ "'";
			res = mConnWrite->PQexec(query);
			if (PQresultStatus(res) == PGRES_FATAL_ERROR)
				throw(CPostgreException(res));
			PQclear(res);
		}

		mConnWrite->PQexecNR("COMMIT");
	} catch (CPostgreException &e) {
		mConnWrite->PQexecNR("ROLLBACK");
		e.ShowMessage();
		success = false;
	}
	refreshClass();
	return success;
}

bool CPGFeatClass::addGeometryField(string name, int srid, Core::COpenGISType::OPENGIS_TYPE type,
		int dimension) {
	bool success = true;
	// One FeatureClass can have only one geometry field
	if (Fields.hasGeometry)
		return false;
	try {
		mConnWrite->PQexecNR("BEGIN");
		string query = "SELECT AddGeometryColumn(" + SQLInsertString(TableName) + ","
				+ SQLInsertString(name) + "," + Int2Str(srid) + "," + SQLInsertString(
				COpenGISType::GetNameByType(type)) + "," + Int2Str(dimension) + ")";
		PGresult *res = mConnWrite->PQexec(query);
		if (PQresultStatus(res) == PGRES_FATAL_ERROR)
			throw(CPostgreException(res));
		PQclear(res);
		mConnWrite->PQexecNR("COMMIT");
	} catch (CPostgreException &e) {
		mConnWrite->PQexecNR("ROLLBACK");
		e.ShowMessage();
		success = false;
	}
	refreshClass();
	return success;
}

bool CPGFeatClass::deleteField(int fieldID) {
	bool success = true;
	try {
		mConnWrite->PQexecNR("BEGIN");
		string query = "ALTER TABLE " + TableName + " DROP COLUMN " + Fields.GetField(fieldID).Name;
		PGresult *res = mConnWrite->PQexec(query);
		if (PQresultStatus(res) == PGRES_FATAL_ERROR)
			throw(CPostgreException(res));
		PQclear(res);
		mConnWrite->PQexecNR("COMMIT");
	} catch (CPostgreException &e) {
		mConnWrite->PQexecNR("ROLLBACK");
		e.ShowMessage();
		success = false;
	}
	refreshClass();
	return success;
}

void CPGFeatClass::refreshClass() {
	loadField();
}
}
