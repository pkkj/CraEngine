/*
 * CRenderer.cpp
 *
 *  Created on: 2011-2-1
 *      Author: pkkj
 */

#include "CRenderer.h"
#include "CRenderDescriptor.h"
#include <Qt>
#include <QBrush>
namespace GUI {
QPen CRenderer::selectedPen(Qt::cyan, 2.0);

CRenderer::CRenderer() {

}

CRenderer::~CRenderer() {

}
void CRenderer::defaultRenderer(DataSource::CFeature *pFeat, CRenderDescriptor *descriptor,
		bool selected) {
	if (selected)
		descriptor->painter->setPen(selectedPen);
	else {
		QPen pen;
		pen.setColor(Qt::black);
		pen.setStyle(Qt::SolidLine);
		descriptor->painter->setPen(pen);
	}
	if (pFeat->getGeometryType() == COpenGISType::OGIS_MULTIPOINT || pFeat->getGeometryType()
			== COpenGISType::OGIS_POINT)
		descriptor->painter->setBrush(Qt::darkRed);
	else
		descriptor->painter->setBrush(QBrush());
}

void CRenderer::selectedtRendererPen(CRenderDescriptor *descriptor) {
	descriptor->painter->setPen(selectedPen);
}
}
