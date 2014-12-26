/*
 * CEWKBReaderText.h
 *
 *  Created on: 2011-1-23
 *      Author: pkkj
 */

#ifndef CEWKBREADERTEXT_H_
#define CEWKBREADERTEXT_H_
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

class CEWKBReaderText {
public:
	CEWKBReaderText();
	byte ForwardByte(char **buf);
	int ForwardInt(char **buf);
	unsigned short ForwardUInt16(char **buf);
	long long ForwardInt64(char **buf);
	double ForwardDouble(char **buf);

	CGeometry* readGeometry(char **buf,bool withSRID = true);
	CPoint* readPoint(char **buf);
	CLineString* readLineString(char **buf);
	CLinearRing* readLinearRing(char **buf);
	CPolygon* readPolygon(char **buf);
	CMultiPoint* readMultiPoint(char **buf);
	CMultiLineString* readMultiLineString(char **buf);
	CMultiPolygon* readMultiPolygon(char **buf);

private:
	CCoordinate readCoordinate(char **buf);
	CCoVecSequence* readCoordinateSequence(char **buf);
	CGeometry *Proccess();
	void GetGeometryInfo(char **buf);
	ENDIAN mEndian;
	bool mHasM;
	bool mHasZ;
	int mSRID;
	byte mGeoType;
};

}

#endif /* CEWKBREADERTEXT_H_ */
