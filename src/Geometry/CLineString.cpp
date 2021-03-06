//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : PSDE
//  @ File Name : CLineString.cpp
//  @ Date : 2010/12/20
//  @ Author : 
//
//


#include "CLineString.h"

namespace Geometry {
CLineString::CLineString() {
	mCoord = new CCoVecSequence();
}

CLineString::CLineString(const CLineString & ln) :
	CGeometry(ln) {
	mCoord = ln.mCoord->clone();
}

CLineString::CLineString(const CCoVecSequence & seq) {
	mCoord = seq.clone();
}

CLineString::~CLineString() {
	delete mCoord;
}

void CLineString::reverse() {
	if (mCoord)
		mCoord->reverse();
}

CPoint* CLineString::getPointAt(size_t pos) {
	return new CPoint(mCoord->getAt(pos));
}
CPoint* CLineString::getStartPoint() {
	if (mCoord && !mCoord->isEmpty())
		return getPointAt(0);
	return NULL;
}

CPoint* CLineString::getEndPoint() {
	if (mCoord && !mCoord->isEmpty())
		return getPointAt(getNumPoints() - 1);
	return NULL;
}

CGeometry* CLineString::clone() const {
	return new CLineString(*this);
}

double CLineString::getArea() const {
	return 0.00;
}

double CLineString::getLength() const {
	// to be done
	return 0.0;
}

size_t CLineString::getNumPoints() const {
	return mCoord->getSize();
}

size_t CLineString::getNumGeometries() const {
	return isEmpty() ? 0 : 1;
}

CCoVecSequence *CLineString::getCoordinates() const {
	return mCoord->clone();
}

bool CLineString::equalExact(CGeometry* geom, double eps) const {
	if (!isEquivalentClass(geom))
		return false;
	const CLineString *other = dynamic_cast<const CLineString*> (geom);
	return CCoVecSequence::equal(*mCoord, *(other->mCoord));
}

CCoordinate CLineString::getCoordinateAt(size_t pos) const {
	if (mCoord == NULL || mCoord->isEmpty())
		return CCoordinate();
	if (0 <= pos && pos < mCoord->getSize())
		return mCoord->getAt(pos);
	return CCoordinate();
}


CRectangle CLineString::getBoundingRect()const{
	return mCoord->getBoundingRect();
}

string CLineString::getGeometryType() const {
	return "CLineString";
}

bool CLineString::isSimple() const {
	// to be done
	return true;
}

bool CLineString::isEmpty() const {
	return mCoord->getSize() == 0;
}

bool CLineString::isClosed() const {
	if (isEmpty())
		return false;
	return getCoordinateAt(0) == getCoordinateAt(getNumPoints() - 1);
}
bool CLineString::isRing() const {
	return isSimple() && isClosed();
}

COpenGISType::OPENGIS_TYPE CLineString::getOGISType() const {
	return COpenGISType::OGIS_LINESTRING;
}
std::ostream & operator <<(std::ostream &out, const CLineString &ls) {
	for (size_t i = 0, n = ls.getNumPoints(); i < n; i++)
		out << ls.getCoordinateAt(i);
	return out;
}

}
