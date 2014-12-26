/*
 * CPGConnection.h
 *
 *  Created on: 2010-12-27
 *      Author: pkkj
 */

#ifndef CPGConnection_H_
#define CPGConnection_H_

#include <string>
#include <vector>
using namespace std;

#include "CPGCommon.h"
#include "CPropertySet.h"
namespace DataSource {

struct CTableInfo {
	enum TABLE_TYPE {
		TABLE_COMMON = 0, TABLE_GEOMETRY = 1, TABLE_GEOGRAPHY = 2
	};
	string name;
	TABLE_TYPE tableType;
	CTableInfo() {
	}
	CTableInfo(string name, TABLE_TYPE tableType) :
		name(name), tableType(tableType) {
	}
};

class CPGConnection {
public:
	CPGConnection(Core::CPropertySet connInfo);
	CPGConnection(CPGConnection &conn);
	~CPGConnection();

	void getPostgisVersion();
	string postgisVersion();
	bool hasGEOS();
	bool hasPROJ();

	PGresult* PQexec(string query);
	PGresult* PQgetResult();
	bool PQexecNR(string query);
	PGresult * PQprepare(string cmdName, string query, int nParams, const Oid* paramTypes);
	PGresult * PQexecPrepared(string cmdName, vector<string> lstPara);
	char *PQerrorMessage();
	void PQsendQuery(string query);
	vector<CTableInfo> listTables();

	// Cursor management
	bool openCursor(string curName, string query);
	bool closeCursor(string curName);

	// Connect/disconnect from db
	void setConnInfo(const Core::CPropertySet &info);
	bool connect();
	void disconnect();
private:
	PGconn *mConn;
	int nCursor;
	Core::CPropertySet mConnInfo;

	bool mHasGeos;
	bool mHasProj;
	string mPostVer;
	static vector<CPGConnection *> vecConn;

	bool connected;

};

}
#endif /* CPGConnection_H_ */
