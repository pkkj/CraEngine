/*
 * CMapScreenConvert.cpp
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */
#include <cstdio>

#include "CMapScreenConvert.h"

namespace GUI {

CMapScreenConvert::CMapScreenConvert() {
}

CMapScreenConvert::~CMapScreenConvert() {

}

CRectangle CMapScreenConvert::getMapRect() {
	return mMapRect;

}
void CMapScreenConvert::calcFactor() {
	double h = mScrSize.height(), w = mScrSize.width(), x, y;
	double ox = mMapRect.maxx - mMapRect.minx;
	double oy = mMapRect.maxy - mMapRect.miny;
	x = ox;
	y = oy;

	double bi1 = h / w;
	double bi2 = y / x;

	if (bi1 > bi2) {
		y = h * x / w;
	} else {
		x = w * y / h;
	}

	factor = w / x;
	double dx = (x - ox) * 0.5;
	double dy = (y - oy) * 0.5;
	mMapRect.minx -= dx;
	mMapRect.maxx += dx;
	mMapRect.miny -= dy;
	mMapRect.maxy += dy;
}
void CMapScreenConvert::setMapExtent(CRectangle rect) {
	mMapRect = rect;
	calcFactor();

}
void CMapScreenConvert::setScreenSize(QSize size) {
	mScrSize = size;
	calcFactor();
}

void CMapScreenConvert::transToScreen(double &x, double &y) {
	x = x - mMapRect.minx;
	y = mMapRect.maxy - y;
	x *= factor;
	y *= factor;
}
void CMapScreenConvert::transToMap(double &x, double &y) {
	x /= factor;
	y /= factor;
	x = x + mMapRect.minx;
	y = mMapRect.maxy - y;
}

void CMapScreenConvert::transRectToScreen(CRectangle &rect) {
	transToScreen(rect.minx, rect.miny);
	transToScreen(rect.maxx, rect.maxy);
}
void CMapScreenConvert::transRectToMap(CRectangle &rect) {
	transToMap(rect.minx, rect.miny);
	transToMap(rect.maxx, rect.maxy);
}
}
