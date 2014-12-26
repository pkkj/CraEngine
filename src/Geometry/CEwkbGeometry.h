/*
 * CEWKBGeometry.h
 *
 *  Created on: 2011-1-23
 *      Author: pkkj
 */

#ifndef CEWKBGEOMETRY_H_
#define CEWKBGEOMETRY_H_

namespace Geometry {
class CEwkbGeometry {
	friend class CGeometryExt;
public:
	CEwkbGeometry();
	CEwkbGeometry(unsigned char *geomstr, int mStrSize);
	CEwkbGeometry(CEwkbGeometry &geom);
	~CEwkbGeometry();
	void setGeomStr(unsigned char *geomstr, int mStrSize);
	CEwkbGeometry *clone();
private:
	unsigned char *mEWKBstr;
	int mEWKBstrSize;
};
}
#endif /* CEWKBGEOMETRY_H_ */
