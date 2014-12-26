/*
 * CDataSrcFactory.h
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#ifndef CDATASRCFACTORY_H_
#define CDATASRCFACTORY_H_

#include <string>
using namespace std;

#include "CPropertySet.h"
namespace DataSource {

class CDataSrc;
class CDataSrcFactory {
public:
	CDataSrcFactory();
	~CDataSrcFactory();

	virtual CDataSrc* open(Core::CPropertySet connInfo) = 0;
	virtual CDataSrc* openFile(string name) = 0;
};


}

#endif /* CDATASRCFACTORY_H_ */
