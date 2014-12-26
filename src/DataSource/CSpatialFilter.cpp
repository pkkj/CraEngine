/*
 * CSpatialFilter.cpp
 *
 *  Created on: 2011-1-14
 *      Author: pkkj
 */

#include "CSpatialFilter.h"

namespace DataSource {

CSpatialFilter::CSpatialFilter() :
	Rect(0, 0, 0, 0) {
	Relation = SPATIALREL_UNDEFINED;
	Geometry = NULL;
}
CSpatialFilter::~CSpatialFilter() {
}
string CSpatialFilter::FilterType() {
	return "CSpatialFilter";
}
}
