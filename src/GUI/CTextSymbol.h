/*
 * CTextSymbol.h
 *
 *  Created on: 2011-2-4
 *      Author: pkkj
 */

#ifndef CTEXTSYMBOL_H_
#define CTEXTSYMBOL_H_
#include <QColor>
#include <QFontInfo>
#include <QFont>
namespace GUI {

class CTextSymbol {
public:
	enum TEXT_BACKGROUND {
		BACK_NONE, BACK_RECT, BACK_CIRCLE
	};
public:
	CTextSymbol();
	CTextSymbol(CTextSymbol &textSymbol);
	~CTextSymbol();

	void setColor(QColor color);
	QColor getColor();

	void setFont(QFont font);
	QFont getFont();

	void setBackColor(QColor color);
	QColor getBackColor();

	void setBackStyle(TEXT_BACKGROUND style);
	TEXT_BACKGROUND getBackStyle();
private:
	QColor mColor;
	QFont mFont;
	QColor mBackColor;
	TEXT_BACKGROUND mBackStyle;
};
}

#endif /* CTEXTSYMBOL_H_ */
