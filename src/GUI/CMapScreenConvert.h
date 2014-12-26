/*
 * CMapScreenConvert.h
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */

#ifndef CMAPSCREENCONVERT_H_
#define CMAPSCREENCONVERT_H_

#include <QSize>
#include "CRectangle.h"
#include "CCoordinate.h"

using namespace Geometry;
namespace GUI {

/**
 * @class Managing how to convert the point between map and screen
 *
 */
class CMapScreenConvert {
	friend class CMap;
public:
	CMapScreenConvert();
	~CMapScreenConvert();

	void setMapExtent(CRectangle mMapRect);
	void setScreenSize(QSize mScrSize);

public:

	double factor;
	void calcFactor();
	void transToScreen(double &x, double &y);
	void transToMap(double &x, double &y);

	void transRectToScreen(CRectangle &rect);
	void transRectToMap(CRectangle &rect);
	CRectangle getMapRect();
private:
	CRectangle mMapRect;
	QSize mScrSize;
};

}
#endif /* CMAPSCREENCONVERT_H_ */
