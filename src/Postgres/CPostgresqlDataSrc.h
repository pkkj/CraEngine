/*
 * CPostgresqlDataSrc.h
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#ifndef CPOSTGRESQLDATASRC_H_
#define CPOSTGRESQLDATASRC_H_
#include "CDataSrc.h"
#include "CPGConnection.h"
namespace DataSource{

class CPostgresqlDataSrc : public CDataSrc
{
	friend class CPostgresqlDataSrcFactory;
public:
	CPostgresqlDataSrc(Core::CPropertySet connInfo);
	~CPostgresqlDataSrc();
	/**
	 * Generate and returen a dataclass to the user
	 * Attention: user should release this CDataClass manually
	 * @return The next CDataClass
	 */
	CEnumDataClass getDataClassSet();
	CDataClass* getDataClass(string name);
private:
	CPGConnection *mConn;
	Core::CPropertySet mConnInfo;
};

}
#endif /* CPOSTGRESQLDATASRC_H_ */
