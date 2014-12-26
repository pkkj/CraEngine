/*
 * CElement.cpp
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#include "CElement.h"
#include "CSymbol.h"
using namespace Geometry;
namespace GUI {
CElement::CElement() {
	mGraphicsContainer = NULL;
}
CElement::~CElement() {
}
CElement::CElement(CElement &element) {
	mGraphicsContainer = element.mGraphicsContainer;
}

void CElement::setGraphicsContainer(CGraphicsContainer *pGraphicsContainter) {
	mGraphicsContainer = pGraphicsContainter;
}

void CElement::setDisplayLevel(int level) {
	displayLevel = level;
}
int CElement::getDisplayLevel()const {
	return displayLevel;
}
}

