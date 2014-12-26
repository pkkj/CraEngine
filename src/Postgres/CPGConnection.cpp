/*
 * CPGConnection.cpp
 *
 *  Created on: 2010-12-27
 *      Author: pkkj
 */
#include "CPGConnection.h"
#include "Utils.h"
namespace DataSource {

vector<CPGConnection*> CPGConnection::vecConn;

CPGConnection::CPGConnection(Core::CPropertySet connInfo) : mConnInfo(connInfo){
	nCursor = 0;
	mConn = NULL;
	connected = false;
}
CPGConnection::~CPGConnection() {
	if (connected)
		disconnect();
}

CPGConnection::CPGConnection(CPGConnection &conn) {

}
void CPGConnection::setConnInfo(const Core::CPropertySet &info) {
	mConnInfo = info;

}
bool CPGConnection::connect() {
	string mPGHost = mConnInfo.getValue("HOST");
	string mPGPort = mConnInfo.getValue("PORT");
	string mPGOptions = mConnInfo.getValue("OPTIONS");
	string mPGTty = mConnInfo.getValue("TTY");
	string mPGDBName = mConnInfo.getValue("DBNAME");
	string mPGUser = mConnInfo.getValue("USER");
	string mPGPasswd = mConnInfo.getValue("PASSWORD");

	mConn = PQsetdbLogin(mPGHost.c_str(), mPGPort.c_str(), mPGOptions.c_str(), mPGTty.c_str(),
			mPGDBName.c_str(), mPGUser.c_str(), mPGPasswd.c_str());
	if (PQstatus(mConn) == CONNECTION_BAD) {
		printf("Connection to database ¡¯%s¡¯ failed.\n", mPGDBName.c_str());
		printf("Message %s", PQerrorMessage());

		disconnect();
		return false;
	}

	//PQsetClientEncoding(mConn, "UTF-8");
	printf("successfully connect to the database\n");
	getPostgisVersion();
	connected = true;
	return true;
}

void CPGConnection::disconnect() {
	if (!connected)
		return;
	connected = false;
	PQfinish(mConn);
	mConn = NULL;
}

void CPGConnection::getPostgisVersion() {
	string query = "SELECT postgis_version()";
	PGresult *res = PQexec(query);
	if (!PQntuples(res)) {
		mPostVer = "";
		return;
	}
	string value = string(PQgetvalue(res, 0, 0)), subres;
	vector<string> reslist = SplitString(value, " ");
	mPostVer = value[0];
	subres = value[1];
	if (subres[subres.size() - 1] == '1')
		mHasGeos = true;
	else
		mHasGeos = false;

	subres = value[2];
	if (subres[subres.size() - 1] == '1')
		mHasProj = true;
	else
		mHasProj = false;
}
string CPGConnection::postgisVersion() {
	return mPostVer;
}

bool CPGConnection::hasGEOS() {
	return mHasGeos;
}

bool CPGConnection::hasPROJ() {
	return mHasProj;
}

PGresult* CPGConnection::PQexec(string query) {
	//#ifdef debug
	printf("EXEC: %s\n", query.c_str());
	//#endif
	return ::PQexec(mConn, query.c_str());
}

PGresult* CPGConnection::PQgetResult() {
	return ::PQgetResult(mConn);
}

bool CPGConnection::PQexecNR(string query) {
	PGresult* res = ::PQexec(mConn, query.c_str());
	//#ifdef debug
	printf("EXECNR: %s\n", query.c_str());
	//#endif
	if (!res)
		return false;
	if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		return true;
	}

	fprintf(stderr, "ERROR FROM POSTGRESQL %s", PQerrorMessage());
	PQclear(res);

	return false;
}

PGresult * CPGConnection::PQprepare(string cmdName, string query, int nParams,
		const Oid* paramTypes) {
	return ::PQprepare(mConn, cmdName.c_str(), query.c_str(), nParams, paramTypes);
}

PGresult * CPGConnection::PQexecPrepared(string cmdName, vector<string> lstPara) {
	size_t nParam = lstPara.size();
	const char **param = new const char*[nParam];
	for (size_t i = 0; i < nParam; i++) {
		param[i] = lstPara[i].c_str();
	}
	return ::PQexecPrepared(mConn, cmdName.c_str(), (int) nParam, param, NULL, NULL, 0);
}

void CPGConnection::PQsendQuery(string query) {
	::PQsendQuery(mConn, query.c_str());
}

vector<CTableInfo> CPGConnection::listTables() {
	vector<CTableInfo> ret;
	string query = "SELECT table_name FROM information_schema.tables "
		"WHERE table_schema = 'public';";
	PGresult *queryRes = PQexec(query);
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
		else
			ret.push_back(CTableInfo(s, CTableInfo::TABLE_COMMON));
	}
	if (existGeometry) {
		query = "SELECT f_table_name FROM geometry_columns";
		queryRes = PQexec(query);
		for (i = 0; i < PQntuples(queryRes); i++) {
			string s = string(PQgetvalue(queryRes, i, 0));
			for (size_t j = 0; j < ret.size(); j++)
				if (s == ret[j].name) {
					ret[j].tableType = CTableInfo::TABLE_GEOMETRY;
					break;
				}
		}
	}
	if (existGeography) {
		query = "SELECT f_table_name FROM geography_columns";
		queryRes = PQexec(query);
		for (i = 0; i < PQntuples(queryRes); i++) {
			string s = string(PQgetvalue(queryRes, i, 0));
			for (size_t j = 0; j < ret.size(); j++)
				if (s == ret[j].name) {
					ret[j].tableType = CTableInfo::TABLE_GEOGRAPHY;
					break;
				}
		}
	}
	return ret;
}


bool CPGConnection::openCursor(string curName, string query) {
	if (!nCursor) {
		PQexecNR("BEGIN WORK");
	}
	nCursor++;
	string cmd = "DECLARE " + curName + " BINARY CURSOR FOR " + query;
#ifdef debug
	//printf("open cursor: %s\n", cmd.c_str());
#endif
	return PQexecNR(cmd);
}
bool CPGConnection::closeCursor(string curName) {
	if (!PQexecNR("CLOSE " + curName))
		return false;
	nCursor--;
	if (!nCursor) {
		PQexecNR("COMMIT");
	}
	return true;
}

char *CPGConnection::PQerrorMessage() {
	return ::PQerrorMessage(mConn);
}
}
