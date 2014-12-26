/*
 * CEWKTWriter.h
 *
 *  Created on: 2010-12-26
 *      Author: pkkj
 */

#ifndef CEWKTWRITER_H_
#define CEWKTWRITER_H_
#include <string>
#include <cstdio>
using namespace std;

#include "CIO.h"
#include "CCoordinate.h"
#include "CCoVecSequence.h"
#include "CGeometry.h"
#include "CPoint.h"
#include "CLineString.h"
#include "CLinearRing.h"
#include "CPolygon.h"
#include "CMultiPoint.h"
#include "CMultiLineString.h"
#include "CMultiPolygon.h"
#include "CGeomCollection.h"
using namespace Geometry;
namespace IO {

class CEWKTWriter {

public:
	CEWKTWriter();
	~CEWKTWriter();
	string WriteCoordinate(const CCoordinate &cord);
	string WriteCCoVecSequence(const CCoVecSequence *seq);
	string WriteGeometry(const CGeometry *geom);
	string WritePoint(const CPoint *geom);
	string WriteLineString(const CLineString *geom);
	string WritePolygon(const CPolygon *geom);
	string WriteMultiPoint(const CMultiPoint *geom);
	string WriteMultiLineString(const CMultiLineString *geom);
	string WriteMultiPolygon(const CMultiPolygon *geom);
private:
	bool HasM;
	bool HasZ;

};
}
#endif /* CEWKTWRITER_H_ */
