/*
 * CEWKTWriter.cpp
 *
 *  Created on: 2010-12-26
 *      Author: pkkj
 */

#include "CEWKTWriter.h"
#include "Utils.h"
namespace IO {

CEWKTWriter::CEWKTWriter() {

}
CEWKTWriter::~CEWKTWriter() {
}
string CEWKTWriter::WriteCoordinate(const CCoordinate &cord) {
	char ss[1000];
	if (!HasZ && !HasM)
		sprintf(ss, "%lf %lf", cord.x, cord.y);
	else if (HasZ && !HasM)
		sprintf(ss, "%lf %lf %lf", cord.x, cord.y, cord.z);
	else if (!HasZ && HasM)
		sprintf(ss, "%lf %lf %lf", cord.x, cord.y, cord.m);
	else if (HasZ && HasM)
		sprintf(ss, "%lf %lf %lf %lf", cord.x, cord.y, cord.z, cord.m);
	return string(ss);
}
string CEWKTWriter::WriteCCoVecSequence(const CCoVecSequence *seq) {
	string res;
	for (size_t i = 0; i < seq->getSize(); i++) {
		if (i != 0)
			res += ",";
		res += WriteCoordinate(seq->getAt(i));
	}
	return res;
}

string CEWKTWriter::WriteGeometry(const CGeometry *geom) {
	if(geom == NULL)return "";
	string res = "";
	if (geom->getSRID() != -1)
		res = "SRID=" + Int2Str(geom->getSRID()) + ";";
	HasZ = geom->HasZ;
	HasM = geom->HasM;
	// something should be done with M, POINTM etc
	switch (geom->getOGISType()) {
	case COpenGISType::OGIS_POINT:
		res += "POINT" + WritePoint((CPoint *) geom);
		break;
	case COpenGISType::OGIS_LINESTRING:
		res += "LINESTRING" + WriteLineString((CLineString *) geom);
		break;
	case COpenGISType::OGIS_POLYGON:
		res += "POLYGON" + WritePolygon((CPolygon *) geom);
		break;
	case COpenGISType::OGIS_MULTIPOINT:
		res += "MULTIPOINT" + WriteMultiPoint((CMultiPoint *) geom);
		break;
	case COpenGISType::OGIS_MULTILINESTRING:
		res += "MULTILINESTRING" + WriteMultiLineString((CMultiLineString *) geom);
		break;
	case COpenGISType::OGIS_MULTIPOLYGON:
		res += "MULTIPOLYGON" + WriteMultiPolygon((CMultiPolygon *) geom);
		break;
	default:
		;
	}
	return res;
}
string CEWKTWriter::WritePoint(const CPoint *geom) {
	string res = "(" + WriteCoordinate(geom->getCoordinate()) + ")";
	return res;
}
string CEWKTWriter::WriteLineString(const CLineString *geom) {
	CCoVecSequence *seq = geom->getCoordinates();
	string res = "(" + WriteCCoVecSequence(seq);
	delete seq;
	return res + ")";
}
string CEWKTWriter::WritePolygon(const CPolygon *geom) {
	string res = "(";
	res += WriteLineString(geom->getShell());
	for (size_t i = 0; i < geom->getNumHoles(); i++) {
		res += ",";
		res += WriteLineString(geom->getHoleAt(i));
	}
	return res + ")";
}
string CEWKTWriter::WriteMultiPoint(const CMultiPoint *geom) {
	string res = "(";
	for (size_t i = 0; i < geom->getNumGeometries(); i++) {
		if (i != 0)
			res += ",";

		const CPoint *pPoint = dynamic_cast<const CPoint *>(geom->getGeometryAt(i));
		res += WriteCoordinate(pPoint->getCoordinate());
	}
	return res + ")";
}
string CEWKTWriter::WriteMultiLineString(const CMultiLineString *geom) {
	string res = "(";
	for (size_t i = 0; i < geom->getNumGeometries(); i++) {
		if (i != 0)
			res += ",";
		res += WriteLineString((CLineString *) geom->getGeometryAt(i));
	}
	return res + ")";

}
string CEWKTWriter::WriteMultiPolygon(const CMultiPolygon *geom) {
	string res = "(";
	for (size_t i = 0; i < geom->getNumGeometries(); i++) {
		if (i != 0)
			res += ",";
		res += WriteLineString((CLineString *) geom->getGeometryAt(i));
	}
	return res + ")";
}

}
