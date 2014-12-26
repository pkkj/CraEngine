/*
 * CDataClass.h
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#ifndef CDATACLASS_H_
#define CDATACLASS_H_
#include <string>
using namespace std;
namespace DataSource {


class CDataClass {
public:
	string Name;
	CDataClass();
	virtual ~CDataClass();
};

}

#endif /* CDATACLASS_H_ */
