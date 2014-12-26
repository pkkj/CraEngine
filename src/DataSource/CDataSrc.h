/*
 * CDataSrc.h
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#ifndef CDATASRC_H_
#define CDATASRC_H_
#include <string>
using namespace std;

namespace DataSource {
class CEnumDataClass;
class CDataClass;
class CDataSrc {
public:
	CDataSrc();
	virtual ~CDataSrc();
	virtual CEnumDataClass getDataClassSet() = 0;
	virtual CDataClass* getDataClass(string name) = 0;


};


}

#endif /* CDATASRC_H_ */
