/*
 * CEnumDataClass.h
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#ifndef CENUMDATACLASS_H_
#define CENUMDATACLASS_H_
#include <vector>
using namespace std;
namespace DataSource{
class CDataClass;
class CEnumDataClass {
	friend class CPostgresqlDataSrc;
public:
	CEnumDataClass();
	~CEnumDataClass();
	CDataClass* next();
private:
	vector<CDataClass *> mVecDataClass;
	size_t vecPos;
};

}


#endif /* CENUMDATACLASS_H_ */
