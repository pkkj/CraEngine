/*
 * CTextSymbol.cpp
 *
 *  Created on: 2011-2-4
 *      Author: pkkj
 */
#include "CTextSymbol.h"
namespace GUI {
CTextSymbol::CTextSymbol() :
	mColor(Qt::black), mFont("Tahoma", 10),mBackColor(Qt::white), mBackStyle(BACK_NONE) {

}
CTextSymbol::~CTextSymbol() {
}
CTextSymbol::CTextSymbol(CTextSymbol &textSymbol) {
	mColor = textSymbol.mColor;
	mFont = textSymbol.mFont;
}
void CTextSymbol::setColor(QColor color) {
	mColor = color;
}
QColor CTextSymbol::getColor() {
	return mColor;
}

void CTextSymbol::setFont(QFont font) {
	mFont = font;
}
QFont CTextSymbol::getFont() {
	return mFont;
}

void CTextSymbol::setBackColor(QColor color) {
	mBackColor = color;
}
QColor CTextSymbol::getBackColor() {
	return mBackColor;
}

void CTextSymbol::setBackStyle(CTextSymbol::TEXT_BACKGROUND style) {
	mBackStyle = style;
}
CTextSymbol::TEXT_BACKGROUND CTextSymbol::getBackStyle() {
	return mBackStyle;
}
}
