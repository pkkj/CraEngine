/*
 * CSpatialFilter.h
 *
 *  Created on: 2011-1-14
 *      Author: pkkj
 */

#ifndef CSPATIALFILTER_H_
#define CSPATIALFILTER_H_
#include "CGeometry.h"
#include "CQueryFilter.h"
#include <string>
using namespace std;
namespace DataSource {
class CSpatialFilter: public CQueryFilter {
public:
	enum SPATIAL_RELATION {
		SPATIALREL_UNDEFINED,
		SPATIALREL_CROSS,
		SPATIALREL_CONTAIN,
		SPATIALREL_COVER,
		SPATIALREL_COVERED_BY,
		SPATIALREL_DISJOINT,
		SPATIALREL_WITHIN,
		SPATIALREL_INTERSECT,
		SPATIALREL_EQUAL,
		SPATIALREL_TOUCH,
		SPATIALREL_OVERLAP,
		SPATIALREL_INTERSECT_RECT
	};
	enum SPATIAL_REL_TYPE {
		SPATIALRELT_FUNC, SPATIALRELT_OPERATOR
	};
	enum SPATIAL_9DEM_MAX {
		SPATIALM_INT, SPATIALM_BOUND, SPATIALM_OUT
	};
public:
	CSpatialFilter();
	~CSpatialFilter();

	string FilterType();

public:
	Geometry::CGeometry *Geometry;
	SPATIAL_RELATION Relation;
	string Rel9Dem;
	Geometry::CRectangle Rect;
};
}
#endif /* CSPATIALFILTER_H_ */
