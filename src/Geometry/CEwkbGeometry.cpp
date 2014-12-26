/*
 * CEWKBGeometry.cpp
 *
 *  Created on: 2011-1-23
 *      Author: pkkj
 */
#include <cstring>
#include "CEWKBGeometry.h"
namespace Geometry {

CEwkbGeometry::CEwkbGeometry(unsigned char *geomstr, int mStrSize) {
	mEWKBstrSize = mStrSize;
	if (mEWKBstrSize) {
		mEWKBstr = new unsigned char[mEWKBstrSize];
		memset(mEWKBstr, '\0', mEWKBstrSize);
		memcpy(mEWKBstr, geomstr, mEWKBstrSize);
	} else
		mEWKBstr = NULL;
}
CEwkbGeometry::CEwkbGeometry() {
	mEWKBstr = NULL;
	mEWKBstrSize = 0;
}
CEwkbGeometry::~CEwkbGeometry() {
	if (mEWKBstr)
		delete[] mEWKBstr;
}
void CEwkbGeometry::setGeomStr(unsigned char *geomstr, int mStrSize) {
	if (mEWKBstr) {
		delete[] mEWKBstr;
		mEWKBstr = NULL;
	}
	mEWKBstrSize = mStrSize;
	if (mStrSize) {
		mEWKBstr = new unsigned char[mEWKBstrSize];
		memset(mEWKBstr, '\0', mEWKBstrSize);
		memcpy(mEWKBstr, geomstr, mEWKBstrSize);
	}
}
CEwkbGeometry::CEwkbGeometry(CEwkbGeometry &geom) {
	mEWKBstr = NULL;
	mEWKBstrSize = 0;
	if (geom.mEWKBstr) {
		delete[] mEWKBstr;
		mEWKBstrSize = geom.mEWKBstrSize;
		if (mEWKBstrSize) {
			mEWKBstr = new unsigned char[mEWKBstrSize];
			memcpy(mEWKBstr, geom.mEWKBstr, mEWKBstrSize);
		}
	}
}

CEwkbGeometry *CEwkbGeometry::clone() {
	return new CEwkbGeometry(*this);
}

}
