/*
 * CCircle.cpp
 *
 *  Created on: 2011-2-6
 *      Author: pkkj
 */
#include "CCircle.h"
#include "Maths.h"
namespace Geometry {
CCircle::CCircle() {
	radius = 0;
}
CCircle::CCircle(const CCircle &circle) :
	CPoint(circle) {
	radius = circle.radius;
}
CCircle::CCircle(const CCoordinate &c, double r) :
	CPoint(c) {
	radius = r;

}
CCircle::CCircle(const double x, const double y, const double r) :
	CPoint(x, y) {
	radius = r;
}

CRectangle CCircle::getBoundingRect() const {
	double x = getCoordinate().x, y = getCoordinate().y;
	return CRectangle(x - radius, y - radius, x + radius, y + radius);
}

string CCircle::getGeometryType() const {
	return "CCircle";
}

COpenGISType::OPENGIS_TYPE CCircle::getOGISType() const {
	return COpenGISType::OGIS_CIRCLE;
}

bool CCircle::equalExact(CGeometry* geom, double eps) const {
	if (!isEquivalentClass(geom))
		return false;
	bool em1 = isEmpty();
	bool em2 = geom->isEmpty();
	if (em1 != em2)
		return false;
	if (em1 && em2)
		return true;
	CCircle *pOther = dynamic_cast<CCircle *> (geom);
	if (!CCoordinate::equalCCoordinate(getCoordinate(), pOther->getCoordinate(), eps))
		return false;
	return General::double_cmp(radius - pOther->radius, eps) == 0;
}
}
