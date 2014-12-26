/*
 * CCircle.h
 *
 *  Created on: 2011-2-6
 *      Author: pkkj
 */

#ifndef CCIRCLE_H_
#define CCIRCLE_H_
#include "CPoint.h"
namespace Geometry {
class CCircle : public CPoint{
public:
	CCircle();
	CCircle(const CCircle &circle);
	CCircle(const CCoordinate & c, double r);
	CCircle(const double x, const double y, const double r);

	CRectangle getBoundingRect() const;
	string getGeometryType() const;
	COpenGISType::OPENGIS_TYPE getOGISType()const;

	bool equalExact(CGeometry* geom, double eps) const;
protected:
	double radius;
};
}

#endif /* CCIRCLE_H_ */
