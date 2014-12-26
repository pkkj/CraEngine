/*
 * CMarkerSymbol.h
 *
 *  Created on: 2011-2-6
 *      Author: pkkj
 */

#ifndef CMARKERSYMBOL_H_
#define CMARKERSYMBOL_H_
#include "CSymbol.h"
namespace GUI {
class CRenderDescriptor;
class CMarkerSymbol: public CSymbol {
public:
	enum MarkerStyle {
		MARKER_CIRCLE, MARKER_SQUARE, MARKER_DIAMOND, MARKER_CROSS
	};
public:
	CMarkerSymbol();
	CMarkerSymbol(const CMarkerSymbol &symbol);
	~CMarkerSymbol();

	virtual CSymbol* clone() const;
	void setWidth(double width);

	double getWidth();

	QColor getInColor();
	void setInColor(QColor color);

	QColor getOutColor();
	void setOutColor(QColor color);

	QPen getPen();
	QBrush getBrush();

	void setSize(int size);
	int getSize();

	void setMarkerStyle(MarkerStyle style);
	MarkerStyle getMarkerStyle();

	void renderPointFeature(CRenderDescriptor *descriptor, double x, double y);
protected:
	double mWidth;
	QColor mOutColor;
	QColor mInColor;
	QPen mPen;
	QBrush mBrush;
	int mSize;
	MarkerStyle mStyle;
};
}
#endif /* CMARKERSYMBOL_H_ */
