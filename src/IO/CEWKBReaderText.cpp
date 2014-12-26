/*
 * CEWKBReaderText.cpp
 *
 *  Created on: 2011-1-23
 *      Author: pkkj
 */


#include "CEWKBReaderText.h"
#include "CIO.h"

#include <vector>
#include <cstdio>
using namespace Geometry;
using namespace std;
namespace IO {

CEWKBReaderText::CEWKBReaderText() :
	mSRID(-1) {
}
byte CEWKBReaderText::ForwardByte(char **buf) {
	byte hexV[255];
	CHexStringParser::ParseByte1(*buf, hexV);
	byte ret = CBinaryParser::readByte(hexV);
	(*buf) += 2;
	return ret;
}
unsigned short CEWKBReaderText::ForwardUInt16(char **buf) {
	byte hexV[255];
	CHexStringParser::ParseByte2(*buf, hexV);
	unsigned short ret = CBinaryParser::readUInt16(hexV, mEndian);
	(*buf) += 4;
	return ret;
}

int CEWKBReaderText::ForwardInt(char **buf) {
	byte hexV[255];
	CHexStringParser::ParseByte4(*buf, hexV);
	int ret = CBinaryParser::readInt(hexV, mEndian);
	(*buf) += 8;
	return ret;
}

long long CEWKBReaderText::ForwardInt64(char **buf) {
	byte hexV[255];
	CHexStringParser::ParseByte8(*buf, hexV);
	long long ret = CBinaryParser::readInt64(hexV, mEndian);
	(*buf) += 16;
	return ret;
}
double CEWKBReaderText::ForwardDouble(char **buf) {
	byte hexV[255];
	CHexStringParser::ParseByte8(*buf, hexV);
	double ret = CBinaryParser::readDouble(hexV, mEndian);
	(*buf) += 16;
	return ret;
}
void CEWKBReaderText::GetGeometryInfo(char **buf) {
	// Check Endian
	byte endian = ForwardByte(buf);
	mEndian = endian == 1 ? ENDIAN_LITTLE : ENDIAN_BIG;

	// Check geometry type
	mGeoType = ForwardByte(buf);
	ForwardUInt16(buf);
	// Check dimension of geometry
	/*
	 *
	 NN 01 01 00 00 20 0400
	 NZ 01 01 00 00 A0 0400
	 MN 01 01 00 00 60 0400
	 MZ 01 01 00 00 E0 0400
	 20 00100000
	 a0 10100000
	 60 01100000
	 e0 11100000
	 */
	byte mzBit = ForwardByte(buf);
	mHasM = (0x40 & mzBit) ? true : false;
	mHasZ = (0x80 & mzBit) ? true : false;
}
CGeometry* CEWKBReaderText::readGeometry(char **buf, bool withSRID) {
	// Prevent empty object
	if (*buf == 0)
		return NULL;
	GetGeometryInfo(buf);
	// Check SRID
	if (withSRID)
		mSRID = ForwardInt(buf);
	CGeometry *geom = NULL;
	switch (mGeoType) {
	case wkbPoint:
		geom = readPoint(buf);
		break;
	case wkbLineString:
		geom = readLineString(buf);
		break;
	case wkbPolygon:
		geom = readPolygon(buf);
		break;
	case wkbMultiPoint:
		geom = readMultiPoint(buf);
		break;
	case wkbMultiLineString:
		geom = readMultiLineString(buf);
		break;
	case wkbMultiPolygon:
		geom = readMultiPolygon(buf);
		break;
	}
	if (geom != NULL) {
		geom->setSRID(mSRID);
		geom->HasM = mHasM;
		geom->HasZ = mHasZ;
	}
	if (withSRID)
		mSRID = -1;
	return geom;
}

CCoordinate CEWKBReaderText::readCoordinate(char **buf) {
	CCoordinate ret;
	double x, y, z = DOUBLE_NAN, m = DOUBLE_NAN;
	x = ForwardDouble(buf);
	y = ForwardDouble(buf);
	if (mHasM && !mHasZ)
		m = ForwardDouble(buf);
	else if (!mHasM && mHasZ)
		z = ForwardDouble(buf);
	else if (mHasM && mHasZ) {
		z = ForwardDouble(buf);
		m = ForwardDouble(buf);
	}
	return CCoordinate(x, y, z, m);
}
CCoVecSequence* CEWKBReaderText::readCoordinateSequence(char **buf) {
	size_t sz = (size_t) ForwardInt(buf);
	CCoVecSequence *pCoSeq = new CCoVecSequence(sz);
	for (size_t i = 0; i < sz; i++) {
		pCoSeq->setAt(i, readCoordinate(buf));
	}
	return pCoSeq;
}
CPoint* CEWKBReaderText::readPoint(char **buf) {
	CCoordinate pCoord = readCoordinate(buf);
	CPoint *pPoint = new CPoint(pCoord);
	return pPoint;
}
CLineString* CEWKBReaderText::readLineString(char **buf) {
	CCoVecSequence *pCoSeq = readCoordinateSequence(buf);
	CLineString *pLineString = new CLineString(*pCoSeq);
	return pLineString;
}

CLinearRing* CEWKBReaderText::readLinearRing(char **buf) {
	CCoVecSequence *pCoSeq = readCoordinateSequence(buf);
	CLinearRing *pLinearRing = new CLinearRing(*pCoSeq);
	return pLinearRing;
}

CPolygon* CEWKBReaderText::readPolygon(char **buf) {
	size_t nRing = (size_t) ForwardInt(buf);
	CLinearRing* shell = NULL;
	vector<CGeometry *> *holes = NULL;
	if (nRing > 0)
		shell = readLinearRing(buf);
	if (nRing > 1) {
		holes = new vector<CGeometry *> (nRing - 1);
		for (size_t i = 1; i < nRing; i++) {
			(*holes)[i] = (CGeometry *) readLinearRing(buf);
		}
	}
	CPolygon *pPolygon = new CPolygon(shell, holes);
	return pPolygon;

}
CMultiPoint* CEWKBReaderText::readMultiPoint(char **buf) {
	vector<CGeometry *> * geos = NULL;
	size_t sz = ForwardInt(buf);
	if (sz > 0) {
		geos = new vector<CGeometry *> (sz);
		for (size_t i = 0; i < sz; i++) {
			(*geos)[i] = readGeometry(buf, false);
			// Some operation should be done to ensure the object is correct
		}
	}
	CMultiPoint* pMPoint = new CMultiPoint(geos);
	return pMPoint;
}
CMultiLineString* CEWKBReaderText::readMultiLineString(char **buf) {
	vector<CGeometry *> * geos = NULL;
	size_t sz = ForwardInt(buf);
	if (sz > 0) {
		geos = new vector<CGeometry *> (sz);
		for (size_t i = 0; i < sz; i++) {
			(*geos)[i] = readGeometry(buf, false);
			// Some operation should be done to ensure the object is correct
		}
	}
	CMultiLineString* pMLineString = new CMultiLineString(geos);
	return pMLineString;
}

CMultiPolygon* CEWKBReaderText::readMultiPolygon(char **buf) {
	vector<CGeometry *> * geos = NULL;
	size_t sz = ForwardInt(buf);
	if (sz > 0) {
		geos = new vector<CGeometry *> (sz);
		for (size_t i = 0; i < sz; i++) {
			(*geos)[i] = readGeometry(buf, false);
			// Some operation should be done to ensure the object is correct
		}
	}
	CMultiPolygon* pMPolygon = new CMultiPolygon(geos);
	return pMPolygon;
}
}
