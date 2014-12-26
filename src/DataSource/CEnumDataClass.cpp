/*
 * CEnumDataClass.cpp
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#include "CEnumDataClass.h"
#include "CDataClass.h"
namespace DataSource {

CEnumDataClass::CEnumDataClass() {
	vecPos = 0;
}
CEnumDataClass::~CEnumDataClass() {
	for(;vecPos < mVecDataClass.size();vecPos++)
		delete mVecDataClass[vecPos];
}
CDataClass* CEnumDataClass::next() {
	if (vecPos == mVecDataClass.size())
		return NULL;
	return mVecDataClass[vecPos++];
}

}
