/*
 * CGeometryType.h
 *
 *  Created on: 2011-2-1
 *      Author: pkkj
 */

#ifndef CGEOMETRYTYPE_H_
#define CGEOMETRYTYPE_H_

namespace Core{
enum WkbGeometryType {
	wkbPoint = 1,
	wkbLineString = 2,
	wkbPolygon = 3,
	wkbMultiPoint = 4,
	wkbMultiLineString = 5,
	wkbMultiPolygon = 6,
	wkbGeometryCollection = 7
};
}
#endif /* CGEOMETRYTYPE_H_ */
