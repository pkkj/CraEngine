/*
 * CEWKBReader::CEWKBReader.cpp
 *
 * CEWKBReader:: Created on: 2010-12-26
 * CEWKBReader::     Author: pkkj
 */

#include "CEWKBReader.h"
#include "CIO.h"

#include <vector>
#include <cstdio>
using namespace Geometry;
using namespace std;
namespace IO {

CEWKBReader::CEWKBReader() :
	mSRID(-1) {
}

void CEWKBReader::GetGeometryInfo(unsigned char **buf) {
	// Check Endian
	//byte *endian = ForwardByte(buf);
	byte *endian = (byte *) *buf;
	(*buf)++;
	mEndian = *endian == 1 ? ENDIAN_LITTLE : ENDIAN_BIG;

	// Check geometry type
	//mGeoType = ForwardByte(buf);
	byte *geotype = (byte *) *buf;
	mGeoType = *geotype;
	(*buf) += 3;
	//ForwardUInt16(buf);
	// Check dimension of geometry
	//byte mzBit = ForwardByte(buf);
	byte *mzBit = (byte *) *buf;
	mHasM = (0x40 & *mzBit) ? true : false;
	mHasZ = (0x80 & *mzBit) ? true : false;
	(*buf)++;
}
CGeometry* CEWKBReader::readGeometry(unsigned char **buf, bool withSRID) {
	// Prevent empty object
	if (*buf == 0)
		return NULL;
	GetGeometryInfo(buf);
	// Check SRID
	if (withSRID) {
		//mSRID =ForwardInt(buf);
		mSRID = *(int*) (*buf);
		(*buf) += sizeof(int);
	}
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

	mSRID = -1;
	return geom;
}

CCoordinate CEWKBReader::readCoordinate(unsigned char **buf) {
	CCoordinate ret;
	double x, y, z = DOUBLE_NAN, m = DOUBLE_NAN;
	x = *(double*) (*buf);
	(*buf) += sizeof(double);
	y = *(double*) (*buf);
	(*buf) += sizeof(double);
	if (mHasM && !mHasZ) {
		m = *(double*) (*buf);
		(*buf) += sizeof(double);
	} else if (!mHasM && mHasZ) {
		z = *(double*) (*buf);
		(*buf) += sizeof(double);
	} else if (mHasM && mHasZ) {
		z = *(double*) (*buf);
		(*buf) += sizeof(double);
		m = *(double*) (*buf);
		(*buf) += sizeof(double);
	}

	return CCoordinate(x, y, z, m);
}
CCoVecSequence* CEWKBReader::readCoordinateSequence(unsigned char **buf) {
	//size_t sz = (size_t) ForwardInt(buf);
	size_t sz = *(size_t *) (*buf);
	(*buf) += sizeof(int);
	CCoVecSequence *pCoSequence = new CCoVecSequence(sz);
	for (size_t i = 0; i < sz; i++) {
		pCoSequence->setAt(i, readCoordinate(buf));
	}
	return pCoSequence;
}
CPoint* CEWKBReader::readPoint(unsigned char **buf) {
	CCoordinate pCoord = readCoordinate(buf);
	CPoint *pPoint = new CPoint(pCoord);
	return pPoint;
}
CLineString* CEWKBReader::readLineString(unsigned char **buf) {
	CCoVecSequence *pCoSequence = readCoordinateSequence(buf);
	CLineString *pLineString = new CLineString(*pCoSequence);
	return pLineString;
}

CLinearRing* CEWKBReader::readLinearRing(unsigned char **buf) {
	CCoVecSequence *pCoSequence = readCoordinateSequence(buf);
	CLinearRing *pLinearRing = new CLinearRing(*pCoSequence);
	return pLinearRing;
}

CPolygon* CEWKBReader::readPolygon(unsigned char **buf) {
	size_t nRing = *(size_t *) (*buf);
	(*buf) += sizeof(int);
	CLinearRing* shell = NULL;
	vector<CGeometry *> *holes = NULL;
	if (nRing > 0)
		shell = readLinearRing(buf);
	if (nRing > 1) {
		holes = new vector<CGeometry *> (nRing - 1);
		for (size_t i = 1; i < nRing; i++) {
			(*holes)[i-1] = (CGeometry *) readLinearRing(buf);
		}
	}
	CPolygon *pPolygon = new CPolygon(shell, holes);
	return pPolygon;

}
CMultiPoint* CEWKBReader::readMultiPoint(unsigned char **buf) {
	vector<CGeometry *> * geos = NULL;
	//size_t sz = ForwardInt(buf);
	size_t sz = *(size_t *) (*buf);
	(*buf) += sizeof(int);
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
CMultiLineString* CEWKBReader::readMultiLineString(unsigned char **buf) {
	vector<CGeometry *> * geos = NULL;
	size_t sz = *(size_t *) (*buf);
	(*buf) += sizeof(int);
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

CMultiPolygon* CEWKBReader::readMultiPolygon(unsigned char **buf) {
	vector<CGeometry *> * geos = NULL;
	size_t sz = *(size_t *) (*buf);
	(*buf) += sizeof(int);
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
