/*
 * CLineSymbol.h
 *
 *  Created on: 2011-1-31
 *      Author: pkkj
 */

#ifndef CLINESYMBOL_H_
#define CLINESYMBOL_H_
#include "CSymbol.h"
#include <QColor>
#include <QPen>
#include <QBrush>

namespace GUI {
class CLineSymbol: public CSymbol {
public:
	CLineSymbol();
	CLineSymbol(const CLineSymbol &symbol);
	~CLineSymbol();
	virtual CSymbol* clone() const;

	void setWidth(double width);
	void setColor(QColor color);
	void setLineStyle(Qt::PenStyle style);

	double getWidth();
	QColor getColor();
	Qt::PenStyle getLineStyle();

	QPen getPen();
	QBrush getBrush();
protected:
	double mWidth;
	QColor mColor;
	QPen mPen;
	Qt::PenStyle mLineStyle;
};
}

#endif /* CLINESYMBOL_H_ */
