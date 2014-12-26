/*
 * CEWKBReader.h
 *
 *  Created on: 2010-12-26
 *      Author: pkkj
 */

#ifndef CEWKBREADER_H_
#define CEWKBREADER_H_
#include "CIO.h"
#include "CCoordinate.h"
#include "CCoVecSequence.h"
#include "CBinaryParser.h"
#include "CHexStringParser.h"
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

class CEWKBReader {
public:
	CEWKBReader();

	CGeometry* readGeometry(unsigned char  **buf,bool withSRID = true);
	CPoint* readPoint(unsigned char  **buf);
	CLineString* readLineString(unsigned char  **buf);
	CLinearRing* readLinearRing(unsigned char  **buf);
	CPolygon* readPolygon(unsigned char  **buf);
	CMultiPoint* readMultiPoint(unsigned char  **buf);
	CMultiLineString* readMultiLineString(unsigned char  **buf);
	CMultiPolygon* readMultiPolygon(unsigned char  **buf);

private:
	CCoordinate readCoordinate(unsigned char  **buf);
	CCoVecSequence* readCoordinateSequence(unsigned char  **buf);
	CGeometry *Proccess();
	void GetGeometryInfo(unsigned char  **buf);
	ENDIAN mEndian;
	bool mHasM;
	bool mHasZ;
	int mSRID;
	byte mGeoType;
};

}

#endif /* CEWKBREADER_H_ */
