/*
 * CPostgresqlDataSrcFactory.h
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#include "CDataSrcFactory.h"
#ifndef CPOSTGRESQLDATASRCFACTORY_H_
#define CPOSTGRESQLDATASRCFACTORY_H_

namespace DataSource {

class CPostgresqlDataSrcFactory {
public:
	CPostgresqlDataSrcFactory();
	~CPostgresqlDataSrcFactory();
	/**
	 * Open a PostgreSQL data source from database, and then return the pointer of CDataSrc
	 * Attention: The user should release the returned CDataSrc object manually
	 * @param The connection info descriptor
	 */
	CDataSrc* open(Core::CPropertySet connInfo);

	CDataSrc* openFile(string name);
};
}

#endif /* CPOSTGRESQLDATASRCFACTORY_H_ */
