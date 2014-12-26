/*
 * COpenGISInfo.h
 *
 *  Created on: 2011-1-9
 *      Author: pkkj
 */

#ifndef COPENGISINFO_H_
#define COPENGISINFO_H_
#include <string>
#include "CGeometryType.h"
using namespace std;
namespace Core
{
class COpenGISType {
public:
	enum OPENGIS_TYPE {
		OGIS_POINT = 1,
		OGIS_LINESTRING = 2,
		OGIS_LINEARRING = 3,
		OGIS_POLYGON = 4,
		OGIS_MULTIPOINT = 5,
		OGIS_MULTILINESTRING = 6,
		OGIS_MULTIPOLYGON = 7,
		OGIS_LINE = 8,
		OGIS_GEOMCOLLECTION = 9,
		OGIS_CIRCLE = 50,
		OGIS_UNKNOWN = 100
	};
public:
	static OPENGIS_TYPE GetTypeByName(string Name);
	static  string GetNameByType(OPENGIS_TYPE Type);
	static  OPENGIS_TYPE GetTypeByWkbType(WkbGeometryType wkb);
};
}


#endif /* COPENGISINFO_H_ */
