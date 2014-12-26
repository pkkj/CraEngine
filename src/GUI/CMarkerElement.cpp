/*
 * CMarkerElement.cpp
 *
 *  Created on: 2011-2-6
 *      Author: pkkj
 */

#include "CMarkerElement.h"
#include "CMarkerSymbol.h"
#include "CRenderDescriptor.h"
#include "CGraphicsContainer.h"
namespace GUI {
CMarkerElement::CMarkerElement() {
	mSymbol = new CMarkerSymbol();
	displayLevel = 1;
}
CMarkerElement::CMarkerElement(CMarkerElement &element) :
	CElement(element) {
	mSymbol = new CMarkerSymbol(*element.mSymbol);
	mPosX = element.mPosX;
	mPosY = element.mPosY;
}
CMarkerElement::~CMarkerElement() {
	delete mSymbol;
}

Geometry::CRectangle CMarkerElement::getBoundingRect() const {
	int size = mSymbol->getSize();
	return Geometry::CRectangle(mPosX - size, mPosY - size, mPosX + size, mPosY + size);
}
void CMarkerElement::draw(CRenderDescriptor *descriptor) {
	double x = mPosX, y = mPosY;
	descriptor->painter->setPen(mSymbol->getPen());
	descriptor->painter->setBrush(mSymbol->getBrush());
	mGraphicsContainer->getMapScreenConvert()->transToScreen(x, y);
	mSymbol->renderPointFeature(descriptor, x, y);

}
void CMarkerElement::setPos(double x, double y) {
	mPosX = x;
	mPosY = y;
}
void CMarkerElement::getPos(double &x, double &y) {
	x = mPosX;
	y = mPosY;
}

void CMarkerElement::setSymbol(CMarkerSymbol *pSymbol) {
	delete mSymbol;
	mSymbol = pSymbol;
}
CMarkerSymbol *CMarkerElement::getSymbol() {
	return mSymbol;
}
}
