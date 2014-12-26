/*
 * CTextElement.h
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#ifndef CTEXTELEMENT_H_
#define CTEXTELEMENT_H_
#include <string>
#include <QColor>
using namespace std;
#include "CElement.h"
#include "CCoordinate.h"
namespace GUI {
class CTextSymbol;
class CTextElement: public CElement {
public:
	enum TEXT_ALIGN{
		LEFT_TOP,
		LEFT_BOTTOM,
		RIGHT_TOP,
		RIGHT_BOTTOM
	};
public:
	CTextElement();
	CTextElement(CTextElement &textElement);
	~CTextElement();

	void setPos(Geometry::CCoordinate pos);
	Geometry::CCoordinate getPos();
	void setText(string text);
	string getText();

	void setTextSymbol(CTextSymbol *textSymbol);
	CTextSymbol* getTextSymbol();

	void setTextAlign(TEXT_ALIGN align);
	TEXT_ALIGN getTextAlign();

	virtual Geometry::CRectangle getBoundingRect() const;
	virtual void draw(CRenderDescriptor *descriptor);
private:
	Geometry::CCoordinate mPos;
	string mText;
	CTextSymbol *mSymbol;
	TEXT_ALIGN mAlign;

};
}
#endif /* CTEXTELEMENT_H_ */
