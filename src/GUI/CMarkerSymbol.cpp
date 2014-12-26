/*
 * CMarkerSymbol.cpp
 *
 *  Created on: 2011-2-6
 *      Author: pkkj
 */

#include "CMarkerSymbol.h"
#include "CRenderDescriptor.h"
#include <QPen>
#include <QColor>
#include <QBrush>
namespace GUI {
CMarkerSymbol::CMarkerSymbol() {
	mWidth = 1;
	mInColor = Qt::darkMagenta;
	mOutColor = Qt::darkGray;
	mPen.setStyle(Qt::SolidLine);
	mPen.setWidthF(mWidth);
	mPen.setColor(mOutColor);
	mBrush.setColor(mInColor);
	mBrush.setStyle(Qt::SolidPattern);
	mSize = 2;
	mStyle = MARKER_SQUARE;
}
CMarkerSymbol::CMarkerSymbol(const CMarkerSymbol &symbol) :
	mWidth(symbol.mWidth), mOutColor(symbol.mOutColor), mInColor(symbol.mInColor),
			mPen(symbol.mPen), mBrush(symbol.mBrush) , mSize(symbol.mSize) , mStyle(symbol.mStyle) {

}
CMarkerSymbol::~CMarkerSymbol() {

}
CSymbol* CMarkerSymbol::clone() const {
	return new CMarkerSymbol(*this);
}
QColor CMarkerSymbol::getInColor() {
	return mInColor;
}
void CMarkerSymbol::setInColor(QColor color) {
	mInColor = color;
	mBrush.setColor(mInColor);
}

QColor CMarkerSymbol::getOutColor() {
	return mOutColor;
}
void CMarkerSymbol::setOutColor(QColor color) {
	mOutColor = color;
	mPen.setColor(mOutColor);
}
void CMarkerSymbol::setWidth(double width) {
	mWidth = width;
	mPen.setWidthF(mWidth);
}
double CMarkerSymbol::getWidth() {
	return mWidth;
}

QPen CMarkerSymbol::getPen() {
	return mPen;
}
QBrush CMarkerSymbol::getBrush() {
	return mBrush;
}

void CMarkerSymbol::setSize(int size) {
	mSize = size;
}
int CMarkerSymbol::getSize() {
	return mSize;
}

void CMarkerSymbol::setMarkerStyle(MarkerStyle style) {
	mStyle = style;
}
CMarkerSymbol::MarkerStyle CMarkerSymbol::getMarkerStyle() {
	return mStyle;
}
void CMarkerSymbol::renderPointFeature(CRenderDescriptor *descriptor, double x, double y) {
	if (mStyle == MARKER_CIRCLE) {
		descriptor->painter->drawEllipse(QPointF(x - mSize/2, y - mSize/2), mSize, mSize);
	} else if (mStyle == MARKER_SQUARE) {
		QRect rect(QPoint(x - mSize, y - mSize), QPoint(x + mSize, y + mSize));
		descriptor->painter->drawRect(rect);
	} else if (mStyle == MARKER_DIAMOND) {
		QPolygonF polygon(4);
		polygon[0].setX(x - mSize), polygon[0].setY(y);
		polygon[1].setX(x), polygon[1].setY(y - mSize);
		polygon[2].setX(x + mSize), polygon[2].setY(y);
		polygon[3].setX(x), polygon[3].setY(y + mSize);
		descriptor->painter->drawConvexPolygon(polygon);
	} else if (mStyle == MARKER_CROSS) {
		descriptor->painter->drawLine(x - mSize, y - mSize, x + mSize, y + mSize);
		descriptor->painter->drawLine(x - mSize, y + mSize, x + mSize, y - mSize);
	}
}
}
