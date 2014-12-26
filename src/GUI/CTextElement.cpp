/*
 * CTextElement.cpp
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */
#include <QPainter>
#include "CRenderDescriptor.h"
#include "CTextElement.h"
#include "CTextSymbol.h"
#include "CGraphicsContainer.h"
#include "CMapScreenConvert.h"
namespace GUI {
CTextElement::CTextElement() {
	mSymbol = new CTextSymbol();
	displayLevel = 0;
}
CTextElement::CTextElement(CTextElement &textElement) :
	CElement(textElement) {
	mPos = textElement.mPos;
	mText = textElement.mText;
	mSymbol = new CTextSymbol(*mSymbol);
}
CTextElement::~CTextElement() {
	delete mSymbol;
}

void CTextElement::setPos(Geometry::CCoordinate pos) {
	mPos = pos;
}
Geometry::CCoordinate CTextElement::getPos() {
	return mPos;
}
void CTextElement::setText(string text) {
	mText = text;
}
string CTextElement::getText() {
	return mText;
}
void CTextElement::setTextSymbol(CTextSymbol *textSymbol) {
	delete mSymbol;
	mSymbol = textSymbol;
}

CTextSymbol* CTextElement::getTextSymbol() {
	return mSymbol;
}

Geometry::CRectangle CTextElement::getBoundingRect() const {
	Geometry::CRectangle rect(mPos.x, mPos.y, mPos.x + 1, mPos.y + 1);
	return rect;
}
void CTextElement::setTextAlign(CTextElement::TEXT_ALIGN align) {
	mAlign = align;
}
CTextElement::TEXT_ALIGN CTextElement::getTextAlign() {
	return mAlign;
}
void CTextElement::draw(CRenderDescriptor *descriptor) {
	QString qtext = QString::fromUtf8(mText.c_str());
	int sizeFontRect = 100;
	double x = mPos.x, y = mPos.y;
	mGraphicsContainer->getMapScreenConvert()->transToScreen(x, y);
	if (mSymbol->getBackStyle() != CTextSymbol::BACK_NONE) {
		QFontMetricsF fm(descriptor->painter->font());
		double textWidth = fm.width(qtext) + 2;
		double textHeight = fm.height() + 2;
		descriptor->painter->setPen(Qt::NoPen);
		descriptor->painter->setBrush(mSymbol->getBackColor());
		if (mSymbol->getBackStyle() == CTextSymbol::BACK_CIRCLE) {
			double r = max(textHeight, textWidth);
			switch (mAlign) {
			case LEFT_TOP: {
				double cx = x - textWidth / 2.0, cy = y - textHeight / 2.0;
				descriptor->painter->drawEllipse(cx - r / 2, cy - r / 2, r, r);
			}
				break;
			case LEFT_BOTTOM: {
				double cx = x + textWidth / 2.0, cy = y - textHeight / 2.0;
				descriptor->painter->drawEllipse(cx - r / 2, cy - r / 2, r, r);
			}
				break;
			case RIGHT_TOP: {
				double cx = x - textWidth / 2.0, cy = y + textHeight / 2.0;
				descriptor->painter->drawEllipse(cx - r / 2, cy - r / 2, r, r);
			}
				break;
			case RIGHT_BOTTOM: {
				double cx = x + textWidth / 2.0, cy = y + textHeight / 2.0;
				descriptor->painter->drawEllipse(cx - r / 2, cy - r / 2, r, r);
			}
				break;
			}

		} else if (mSymbol->getBackStyle() == CTextSymbol::BACK_RECT) {
			switch (mAlign) {
			case LEFT_TOP:
				descriptor->painter->drawRect(x - textWidth, y - textHeight, textWidth, textHeight);
				break;
			case LEFT_BOTTOM:
				descriptor->painter->drawRect(x - textWidth, y, textWidth, textHeight);
				break;
			case RIGHT_TOP:
				descriptor->painter->drawRect(x, y - textHeight, textWidth, textHeight);
				break;
			case RIGHT_BOTTOM:
				descriptor->painter->drawRect(x, y, textWidth, textHeight);
				break;
			}

		}
	}
	descriptor->painter->setPen(Qt::SolidLine);
	descriptor->painter->setPen(mSymbol->getColor());
	descriptor->painter->setFont(mSymbol->getFont());
	//descriptor->painter->drawText(QPointF(x, y), qtext);
	switch (mAlign) {
	case RIGHT_TOP:
		descriptor->painter->drawText(x, y - sizeFontRect, sizeFontRect, sizeFontRect,
				Qt::AlignLeft | Qt::AlignBottom, qtext);
		break;
	case RIGHT_BOTTOM:
		descriptor->painter->drawText(x, y, sizeFontRect, sizeFontRect, Qt::AlignLeft
				| Qt::AlignTop, qtext);
		break;
	case LEFT_TOP:
		descriptor->painter->drawText(x - sizeFontRect, y - sizeFontRect, sizeFontRect,
				sizeFontRect, Qt::AlignRight | Qt::AlignBottom, qtext);
		break;
	case LEFT_BOTTOM:
		descriptor->painter->drawText(x - sizeFontRect, y, sizeFontRect, sizeFontRect,
				Qt::AlignRight | Qt::AlignTop, qtext);
		break;
	default:
		descriptor->painter->drawText(x, y - sizeFontRect, sizeFontRect, sizeFontRect,
				Qt::AlignLeft | Qt::AlignBottom, qtext);
	}

}
}
