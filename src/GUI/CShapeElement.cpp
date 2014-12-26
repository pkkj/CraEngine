/*
 * CShapeElement.cpp
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#include "CShapeElement.h"
#include "CSymbol.h"
namespace GUI {

CShapeElement::CShapeElement() {
}
CShapeElement::CShapeElement(CShapeElement &element) :CElement(element){
	mGeometry = element.mGeometry->clone();
	mSymbol = element.mSymbol->clone();
}
CShapeElement::~CShapeElement() {
}

void CShapeElement::setGeometry(CGeometry *pGeometry) {
	mGeometry = pGeometry;
}
CGeometry *CShapeElement::getGeometry() {
	return mGeometry;
}
void CShapeElement::setSymbol(CSymbol *pSymbol) {
	mSymbol = pSymbol;

}
CSymbol* CShapeElement::getSymbol() {
	return mSymbol;
}
Geometry::CRectangle CShapeElement::getBoundingRect()const{
	return mGeometry->getBoundingRect();
}
}
