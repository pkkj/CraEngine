/*
 * CGeometryExt.cpp
 *
 *  Created on: 2011-1-23
 *      Author: pkkj
 */

#include "CGeometryExt.h"
#include "CEWKBReader.h"
#include <cstdio>
namespace Geometry {

CGeometryExt::CGeometryExt() {
	mGeom = NULL;
	mEwkb = NULL;
	mEwkbCorrect = false;
	mGeomCorrect = false;
}

CGeometryExt::CGeometryExt(const CGeometryExt & geom) {
	if (geom.mGeom)
		mGeom = geom.mGeom->clone();
	else
		mGeom = NULL;
	if (geom.mEwkb)
		mEwkb = geom.mEwkb->clone();
	else
		mEwkb = NULL;
	mEwkbCorrect = geom.mEwkbCorrect;
	mGeomCorrect = geom.mGeomCorrect;
	SRID = geom.SRID;
}

CGeometryExt::~CGeometryExt() {
	delete mGeom;
	delete mEwkb;
}
CGeometryExt* CGeometryExt::clone() const {
	return new CGeometryExt(*this);
}

void CGeometryExt::initFromEwkb(CEwkbGeometry *ewkb) {
	mEwkb = ewkb;
	mEwkbCorrect = true;
	mGeomCorrect = false;
}
void CGeometryExt::initFromGeom(CGeometry *geom) {
	mGeom = geom;
	mGeomCorrect = true;
	mEwkbCorrect = false;
}

void CGeometryExt::toGeom() {
	if (mGeomCorrect)
		return;
	if (!mEwkb)
		return;
	delete mGeom;
	IO::CEWKBReader reader;
	unsigned char *tmp = mEwkb->mEWKBstr;
	mGeom = reader.readGeometry(&tmp, SRID != -1);
	mGeomCorrect = true;
}
void CGeometryExt::toEwkb() {
	if (mEwkbCorrect)
		return;
	mEwkbCorrect = true;
}

const CGeometry* CGeometryExt::getGeometryRO() {
	toGeom();
	return mGeom;
}
CGeometry* CGeometryExt::getGeometry() {
	mEwkbCorrect = false;
	toGeom();
	return mGeom;
}
const unsigned char *CGeometryExt::getEwkbStr() {
	return mEwkb->mEWKBstr;
}
CGeometry* CGeometryExt::getGeometryPtr(){
	return mGeom;
}
}
