/*
 * CLineSymbol.cpp
 *
 *  Created on: 2011-1-31
 *      Author: pkkj
 */

#ifndef CLINESYMBOL_CPP_
#define CLINESYMBOL_CPP_
#include <Qt>
#include "CLineSymbol.h"
namespace GUI {
CLineSymbol::CLineSymbol() {
	mWidth = 1;
	mColor = Qt::black;
	mLineStyle = Qt::SolidLine;
	mPen.setStyle(mLineStyle);
	mPen.setWidthF(mWidth);
	mPen.setStyle(mLineStyle);

}

CLineSymbol::~CLineSymbol() {

}
CLineSymbol::CLineSymbol(const CLineSymbol &symbol) :
	mWidth(symbol.mWidth), mColor(symbol.mColor), mPen(symbol.mPen), mLineStyle(symbol.mLineStyle) {
	mWidth = symbol.mWidth;
	mColor = symbol.mColor;
	mPen = symbol.mPen;
	mLineStyle = symbol.mLineStyle;
}
CSymbol* CLineSymbol::clone() const {
	return new CLineSymbol(*this);

}
void CLineSymbol::setWidth(double width) {
	mWidth = width;
	mPen.setWidthF(mWidth);
}
void CLineSymbol::setColor(QColor color) {

	mColor = color;
	mPen.setColor(mColor);
}
void CLineSymbol::setLineStyle(Qt::PenStyle style) {
	mLineStyle = style;
	mPen.setStyle(mLineStyle);
}

double CLineSymbol::getWidth() {
	return mWidth;
}
QColor CLineSymbol::getColor() {
	return mColor;
}
Qt::PenStyle CLineSymbol::getLineStyle() {
	return mLineStyle;
}

QPen CLineSymbol::getPen() {
	return mPen;
}

QBrush CLineSymbol::getBrush() {
	return QBrush();
}
}

#endif /* CLINESYMBOL_CPP_ */

