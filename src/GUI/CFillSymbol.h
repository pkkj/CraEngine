/*
 * CFillSymbol.h
 *
 *  Created on: 2011-2-3
 *      Author: pkkj
 */

#ifndef CFILLSYMBOL_H_
#define CFILLSYMBOL_H_
#include "CSymbol.h"
#include "CLineSymbol.h"
namespace GUI {
class CLineSymbol;
class CFillSymbol: public CSymbol {
public:
	CFillSymbol();
	CFillSymbol(const CFillSymbol &symbol);
	~CFillSymbol();

	virtual CSymbol* clone() const;
	QPen getPen();
	QBrush getBrush();

	CLineSymbol getOutline();
	void setOutline(CLineSymbol outline);

	QColor getColor();
	void setColor(QColor color);

	Qt::BrushStyle getStyle();
	void setStyle(Qt::BrushStyle style);
private:
	QColor mColor;
	Qt::BrushStyle mStyle;
	QBrush mBrush;
	CLineSymbol mOutline;

};
}

#endif /* CFILLSYMBOL_H_ */
