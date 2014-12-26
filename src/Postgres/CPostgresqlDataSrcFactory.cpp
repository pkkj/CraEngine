/*
 * CPostgresqlDataSrcFactory.cpp
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */
#include <libpq-fe.h>
#include "CPostgresqlDataSrcFactory.h"
#include "CPostgresqlDataSrc.h"
#include "CPGConnection.h"
namespace DataSource {

CPostgresqlDataSrcFactory::CPostgresqlDataSrcFactory() {

}
CPostgresqlDataSrcFactory::~CPostgresqlDataSrcFactory() {
}

CDataSrc* CPostgresqlDataSrcFactory::open(Core::CPropertySet connInfo) {
	CPostgresqlDataSrc *pPostgresqlDataSrc = new CPostgresqlDataSrc(connInfo);
	pPostgresqlDataSrc->mConn = new CPGConnection(connInfo);
	pPostgresqlDataSrc->mConn->connect();
	CDataSrc *pDataSrc = dynamic_cast<CDataSrc *>(pPostgresqlDataSrc);
	return pDataSrc;
}
CDataSrc* CPostgresqlDataSrcFactory::openFile(string name) {
	return NULL;
}
}
