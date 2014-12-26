/*
 * CSimpleRenderer.cpp
 *
 *  Created on: 2011-2-1
 *      Author: pkkj
 */

#include "CSimpleRenderer.h"
#include "CSymbol.h"
#include "CMarkerSymbol.h"
#include "CRenderDescriptor.h"
#include "COpenGISInfo.h"
using namespace Core;
namespace GUI {

CSimpleRenderer::CSimpleRenderer() {
}
CSimpleRenderer::~CSimpleRenderer() {
}

void CSimpleRenderer::preRenderFeature(DataSource::CFeature *pFeat, CRenderDescriptor *descriptor,
		bool selected) {
	if (!mSymbol)
		return;
	COpenGISType::OPENGIS_TYPE ty = pFeat->getGeometryType();
	switch (ty) {
	case COpenGISType::OGIS_MULTILINESTRING:
	case COpenGISType::OGIS_LINESTRING:
		if (selected) {
			CRenderer::selectedtRendererPen(descriptor);
		} else
			descriptor->painter->setPen(mSymbol->getPen());
		break;
	case COpenGISType::OGIS_MULTIPOLYGON:
	case COpenGISType::OGIS_POLYGON:
	case COpenGISType::OGIS_POINT:
	case COpenGISType::OGIS_MULTIPOINT:
		descriptor->painter->setBrush(mSymbol->getBrush());
		if (selected)
			CRenderer::selectedtRendererPen(descriptor);
		else
			descriptor->painter->setPen(mSymbol->getPen());
		break;
	default:
		;
	}
}

void CSimpleRenderer::afterRenderFeature(DataSource::CFeature *pFeat, const QPolygonF &info,
		CRenderDescriptor *descriptor, bool selected) {
	COpenGISType::OPENGIS_TYPE ty = pFeat->getGeometryType();
	if (ty == COpenGISType::OGIS_POINT || ty == COpenGISType::OGIS_MULTIPOINT) {
		CMarkerSymbol *pMarkerSymbol = dynamic_cast<CMarkerSymbol *> (mSymbol);
		if (pMarkerSymbol != NULL) {
			pMarkerSymbol->renderPointFeature(descriptor, info[0].x(), info[0].y());
		}
	}

}
CSymbol* CSimpleRenderer::symbolForFeature(DataSource::CFeature *pFeat) {
	return mSymbol;
}

CSymbol* CSimpleRenderer::getSymbol() {
	return mSymbol;

}
void CSimpleRenderer::setSymbol(CSymbol *symbol) {
	mSymbol = symbol;
}

RenderType CSimpleRenderer::getType() {
	return RENDER_SIMPLE;
}
}
