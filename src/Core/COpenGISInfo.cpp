/*
 * COpenGISInfo.cpp
 *
 *  Created on: 2011-1-9
 *      Author: pkkj
 */

#include "COpenGISInfo.h"
namespace Core {

COpenGISType::OPENGIS_TYPE COpenGISType::GetTypeByName(string Name) {
	if (Name == "POINT")
		return OGIS_POINT;
	if (Name == "LINESTRING")
		return OGIS_LINESTRING;
	if (Name == "LINEARRING")
		return OGIS_LINEARRING;
	if (Name == "POLYGON")
		return OGIS_POLYGON;
	if (Name == "MULTIPOINT")
		return OGIS_MULTIPOINT;
	if (Name == "MULTILINESTRING")
		return OGIS_MULTILINESTRING;
	if (Name == "MULTIPOLYGON")
		return OGIS_MULTIPOLYGON;
	if (Name == "GEOMETRYCOLLECTION")
		return OGIS_GEOMCOLLECTION;
	return OGIS_UNKNOWN;

}

string COpenGISType::GetNameByType(COpenGISType::OPENGIS_TYPE Type) {
	if (Type == OGIS_POINT)
		return "POINT";
	if (Type == OGIS_LINESTRING)
		return "LINESTRING";
	if (Type == OGIS_LINEARRING)
		return "LINEARRING";
	if (Type == OGIS_POLYGON)
		return "POLYGON";
	if (Type == OGIS_MULTIPOINT)
		return "MULTIPOINT";
	if (Type == OGIS_MULTILINESTRING)
		return "MULTILINESTRING";
	if (Type == OGIS_MULTIPOLYGON)
		return "MULTIPOLYGON";
	if (Type == OGIS_GEOMCOLLECTION)
		return "GEOMETRYCOLLECTION";
	return "UNKNOWN";
}

COpenGISType::OPENGIS_TYPE COpenGISType::GetTypeByWkbType(WkbGeometryType wkb) {
/*
 * wkbPoint = 1,
	wkbLineString = 2,
	wkbPolygon = 3,
	wkbMultiPoint = 4,
	wkbMultiLineString = 5,
	wkbMultiPolygon = 6,
	wkbGeometryCollection = 7
 */
	if(wkb == wkbPoint)return OGIS_POINT;
	if(wkb == wkbLineString)return OGIS_LINESTRING;
	if(wkb == wkbPolygon)return OGIS_POLYGON;
	if(wkb == wkbMultiPoint)return OGIS_MULTIPOINT;
	if(wkb == wkbMultiLineString)return OGIS_MULTILINESTRING;
	if(wkb == wkbMultiPolygon)return OGIS_MULTIPOLYGON;
	if(wkb == wkbGeometryCollection)return OGIS_GEOMCOLLECTION;
	return OGIS_UNKNOWN;
}
}
