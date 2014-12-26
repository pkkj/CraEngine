/*
 * CPostgresqlDataSrc.cpp
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */
#include <libpq-fe.h>
#include "CPostgresqlDataSrc.h"
#include "CPGFeatureClass.h"
#include "CEnumDataClass.h"
namespace DataSource {

CPostgresqlDataSrc::CPostgresqlDataSrc(Core::CPropertySet connInfo) :
	mConnInfo(connInfo) {

}

CPostgresqlDataSrc::~CPostgresqlDataSrc() {
	mConn->disconnect();
}
CEnumDataClass CPostgresqlDataSrc::getDataClassSet() {
	CEnumDataClass enumDataClass;
	string query = "SELECT table_name FROM information_schema.tables "
		"WHERE table_schema = 'public';";
	PGresult *queryRes = mConn->PQexec(query);
	bool existGeometry = false;
	bool existGeography = false;
	int i;
	for (i = 0; i < PQntuples(queryRes); i++) {
		string s = string(PQgetvalue(queryRes, i, 0));
		if (s == "geometry_columns")
			existGeometry = true;
		else if (s == "geography_columns")
			existGeography = true;
		else if (s == "spatial_ref_sys")
			;
	}
	PQclear(queryRes);
	if (existGeometry) {
		query = "SELECT f_table_name FROM geometry_columns";
		queryRes = mConn->PQexec(query);
		for (i = 0; i < PQntuples(queryRes); i++) {
			string name = string(PQgetvalue(queryRes, i, 0));
			CPGFeatClass *pDataSrc = new CPGFeatClass();
			pDataSrc->Name = name;
			pDataSrc->TableName = name;
			pDataSrc->connect(mConnInfo);
			enumDataClass.mVecDataClass.push_back((CDataClass *) pDataSrc);
		}
	}
	// Something should be done with geography
	return enumDataClass;

}

CDataClass* CPostgresqlDataSrc::getDataClass(string name) {
	string query = "SELECT table_name FROM information_schema.tables "
		"WHERE table_schema = 'public' AND table_name = 'geometry_columns'";
	PGresult *queryRes = mConn->PQexec(query);
	if (PQntuples(queryRes) == 0)
		return NULL;
	PQclear(queryRes);

	query = "SELECT f_table_name FROM geometry_columns WHERE f_table_name = '" + name + "'";
	queryRes = mConn->PQexec(query);
	if (PQntuples(queryRes) == 0)
		return NULL;
	PQclear(queryRes);

	CPGFeatClass *pPgFeatClass = new CPGFeatClass();
	pPgFeatClass->Name = name;
	pPgFeatClass->TableName = name;
	pPgFeatClass->connect(mConnInfo);
	return pPgFeatClass;
}

}
