/*
 * CPolygonElement.cpp
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#include "CPolygonElement.h"
#include "CPolygon.h"
#include "CRenderDescriptor.h"
#include "CGraphicsContainer.h"
#include "CMapScreenConvert.h"
#include <CSymbol.h>
#include <QPolygonF>
#include <QPainterPath>
namespace GUI {
CPolygonElement::CPolygonElement(){
	displayLevel = 1;
}
CPolygonElement::~CPolygonElement() {
}
/*CRectangle CPolygonElement::getBoundingRect(){
	return CShapeElement::getBoundingRect();
}*/
void CPolygonElement::draw(CRenderDescriptor *descriptor) {
	if (!mGeometry)
		return;
	if (mGeometry->getOGISType() != COpenGISType::OGIS_POLYGON)
		return;
	descriptor->painter->setPen(mSymbol->getPen());
	descriptor->painter->setBrush(mSymbol->getBrush());
	CPolygon *pPolygon = dynamic_cast<CPolygon*> (mGeometry);
	if (pPolygon->getNumHoles() == 0) {
		CLineString* pLinestring = pPolygon->getShell();
		size_t nPoint = pLinestring->getNumPoints();
		QPolygonF poly((int) nPoint);
		for (size_t i = 0; i < nPoint; i++) {
			double x = pLinestring->getCoordinateAt(i).x;
			double y = pLinestring->getCoordinateAt(i).y;
			mGraphicsContainer->getMapScreenConvert()->transToScreen(x, y);
			poly[i].setX(x);
			poly[i].setY(y);
		}
		descriptor->painter->drawPolygon(poly);
	} else {
		QPainterPath path;
		CLineString* pLinestring = pPolygon->getShell();
		size_t nPoint = pLinestring->getNumPoints();
		QPolygonF poly((int) nPoint);
		for (size_t i = 0; i < nPoint; i++) {
			double x = pLinestring->getCoordinateAt(i).x;
			double y = pLinestring->getCoordinateAt(i).y;
			mGraphicsContainer->getMapScreenConvert()->transToScreen(x, y);
			poly[i].setX(x);
			poly[i].setY(y);
		}
		path.addPolygon(poly);
		for (size_t i = 0; i < pPolygon->getNumHoles(); i++) {
			CLineString* pLinestring = pPolygon->getHoleAt(i);
			size_t nPoint = pLinestring->getNumPoints();
			QPolygonF poly((int) nPoint);
			for (size_t j = 0; j < nPoint; j++) {
				double x = pLinestring->getCoordinateAt(j).x;
				double y = pLinestring->getCoordinateAt(j).y;
				mGraphicsContainer->getMapScreenConvert()->transToScreen(x, y);
				poly[j].setX(x);
				poly[j].setY(y);
			}
			path.addPolygon(poly);
		}
		descriptor->painter->drawPath(path);
	}
	//for(size_t i = 0;i < pPolygon->)

}
}
