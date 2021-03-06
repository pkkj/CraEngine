//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : PSDE
//  @ File Name : CLine.h
//  @ Date : 2010/12/20
//  @ Author : 
//
//


#if !defined(_CLINE_H)
#define _CLINE_H

#include "CLineString.h"

namespace Geometry {
class CLine: public CLineString {
public:
	CLine();
	CLine(const CLine & ln);
	CLine(const CCoVecSequence & seq);
	CLine(const CCoordinate &c1, const CCoordinate &c2);
public:
	CGeometry* clone() const;
	double getArea() const;
	double getLength() const;
	size_t getNumPoints();
	bool equalExact(CGeometry* geom, double eps) const;
	string getGeometryType() const;
	COpenGISType::OPENGIS_TYPE getOGISType() const;

	bool isEmpty() const;
private:
	void validateConstruction();
};
}

#endif  //_CLINE_H
