/*
 * CFillSymbol.cpp
 *
 *  Created on: 2011-2-3
 *      Author: pkkj
 */

#include "CFillSymbol.h"

namespace GUI {

CFillSymbol::CFillSymbol() {

}
CFillSymbol::CFillSymbol(const CFillSymbol &symbol) :
	mColor(symbol.mColor), mStyle(symbol.mStyle), mBrush(symbol.mBrush), mOutline(
			(symbol.mOutline)) {
}

CFillSymbol::~CFillSymbol() {
}

CSymbol* CFillSymbol::clone() const {
	return new CFillSymbol(*this);
}
QPen CFillSymbol::getPen() {
	return mOutline.getPen();
}
QBrush CFillSymbol::getBrush() {
	return mBrush;
}

CLineSymbol CFillSymbol::getOutline() {
	return mOutline;
}
void CFillSymbol::setOutline(CLineSymbol outline) {
	mOutline = outline;
}

QColor CFillSymbol::getColor() {
	return mColor;
}
void CFillSymbol::setColor(QColor color) {
	mColor = color;
	mBrush.setColor(mColor);
}

Qt::BrushStyle CFillSymbol::getStyle() {
	return mStyle;

}
void CFillSymbol::setStyle(Qt::BrushStyle style) {
	mStyle = style;
	mBrush.setStyle(mStyle);
}
}
