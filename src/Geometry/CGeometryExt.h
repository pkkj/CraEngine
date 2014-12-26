/*
 * CGeometryExt.h
 *
 *  Created on: 2011-1-23
 *      Author: pkkj
 */

#ifndef CGEOMETRYEXT_H_
#define CGEOMETRYEXT_H_
#include "CGeometry.h"
#include "CEwkbGeometry.h"
namespace Geometry {

class CGeometryExt {

public:
	CGeometryExt();
	CGeometryExt(const CGeometryExt & geom);
	~CGeometryExt();
public:
	CGeometryExt* clone() const;

	void initFromEwkb(CEwkbGeometry *ewkb);
	void initFromGeom(CGeometry *geom);

	const CGeometry* getGeometryRO();
	CGeometry* getGeometry();
	CGeometry* getGeometryPtr();
	const unsigned char *getEwkbStr();
public:
	int SRID;

private:
	CGeometry *mGeom;
	CEwkbGeometry *mEwkb;

	bool mEwkbCorrect;
	bool mGeomCorrect;

private:
	void toGeom();
	void toEwkb();
};
}

#endif /* CGEOMETRYEXT_H_ */
