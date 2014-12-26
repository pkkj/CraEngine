/*
 * CMarkerElement.h
 *
 *  Created on: 2011-2-6
 *      Author: pkkj
 */

#ifndef CMARKERELEMENT_H_
#define CMARKERELEMENT_H_
#include "CElement.h"

namespace GUI {
class CMarkerSymbol;
class CMarkerElement: public CElement {
public:
	CMarkerElement();
	CMarkerElement(CMarkerElement &element);
	~CMarkerElement();

	virtual Geometry::CRectangle getBoundingRect()const;
	virtual void draw(CRenderDescriptor *descriptor);
	void setPos(double x, double y);
	void getPos(double &x, double &y);

	void setSymbol(CMarkerSymbol *pSymbol);
	CMarkerSymbol *getSymbol();
protected:
	double mPosX, mPosY;
	CMarkerSymbol *mSymbol;

};
}

#endif /* CMARKERELEMENT_H_ */
