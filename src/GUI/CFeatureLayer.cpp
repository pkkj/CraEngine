/*
 * CFeatureLayer.cpp
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */

#include "CFeatureLayer.h"
#include "CFeatureCursor.h"
#include "CRectangle.h"
#include "CMap.h"
#include "CRenderer.h"
#include "CIO.h"

#include <QPainterPath>
using namespace DataSource;
using namespace Geometry;
typedef unsigned char byte;

namespace GUI {

CFeatureLayer::CFeatureLayer() :
	mSelectable(true) {
	mFeatClass = NULL;
	mRenderer = NULL;
	labelEngine = new CLabelEngine();
	labelEngine->setEnable(false);

}
CFeatureLayer::~CFeatureLayer() {
	delete mFeatClass;
	delete mRenderer;
	delete labelEngine;
}

CFeatureClass *CFeatureLayer::getFeatureClass() {
	return mFeatClass;
}

void CFeatureLayer::setFeatureClass(CFeatureClass * fc) {
	delete mFeatClass;
	mFeatClass = fc;
	name = fc->Name;
}

void CFeatureLayer::setRenderer(CRenderer *renderer) {
	delete mRenderer;
	mRenderer = renderer;
}
CRenderer *CFeatureLayer::getRenderer() {
	return mRenderer;
}

void CFeatureLayer::draw(CRenderDescriptor *descriptor) {
	if (mFeatClass == NULL)
		return;
	labelEngine->beginLabeling(descriptor, mFeatClass->GetShapeType());
	// Fetch the data
	CFeatureCursor cursor;
	CSpatialFilter *filter = new CSpatialFilter();
	filter->Rect = mConvert->getMapRect();
	CFeature *pFeat = new CFeature(mFeatClass);
	mFeatClass->search(filter, cursor);

	while (cursor.NextFeature(*pFeat)) {
		bool selected = mSelectedFeatureId.contains(pFeat->GetFID());
		drawFeature(pFeat, descriptor, selected);
	}

	delete pFeat;
	labelEngine->endLabeling();
}
void CFeatureLayer::drawFeature(CFeature *pFeature, CRenderDescriptor *descriptor, bool selected) {
	if (mRenderer)
		mRenderer->preRenderFeature(pFeature, descriptor, selected);
	else {
		CRenderer::defaultRenderer(pFeature, descriptor, selected);
	}
	const unsigned char *shape = pFeature->Shape->getEwkbStr();
	if (shape == NULL)
		return;
	shape++;
	byte geotype = *(byte *) shape;
	shape += 4;
	if (mFeatClass->SRID != -1)
		shape += sizeof(int);
	switch (geotype) {
	case Core::wkbPoint: {
		double x, y;
		x = *(double *) (shape);
		shape += sizeof(double);
		y = *(double *) (shape);
		shape += sizeof(double);
		mConvert->transToScreen(x, y);

		QPolygonF poly(1);
		poly[0].setX(x), poly[0].setY(y);

		if (mRenderer)
			mRenderer->afterRenderFeature(pFeature, poly, descriptor, selected);
		else
			descriptor->painter->drawRect(x - 2, y - 2, 4, 4);

		labelEngine->preparePointFeature(pFeature, x, y);
	}
		break;
	case Core::wkbLineString:
		drawCoordSeq(&shape, descriptor);
		break;
	case Core::wkbPolygon:
		drawPolygon(&shape, descriptor);
		break;
	case Core::wkbMultiPoint:

		break;
	case Core::wkbMultiLineString: {
		int nPart = *(int *) (shape);
		shape += sizeof(int);
		for (int i = 0; i < nPart; i++) {
			shape += 5;
			drawCoordSeq(&shape, descriptor);
		}
	}
		break;
	case Core::wkbMultiPolygon: {
		int nPart = *(int *) (shape);
		shape += sizeof(int);
		for (int i = 0; i < nPart; i++) {
			shape += 5;
			drawPolygon(&shape, descriptor);
		}
	}
		break;
	}
}
void CFeatureLayer::drawCoordSeq(const unsigned char **shape, CRenderDescriptor *descriptor) {
	int nPoint = *(int *) (*shape);
	(*shape) += sizeof(int);
	QPolygonF poly(nPoint);
	for (int j = 0; j < nPoint; j++) {
		double x, y;
		x = *(double *) (*shape);
		*shape += sizeof(double);
		y = *(double *) (*shape);
		*shape += sizeof(double);
		mConvert->transToScreen(x, y);
		poly[j].setX(x);
		poly[j].setY(y);
	}
	descriptor->painter->drawPolyline(poly);
}

void CFeatureLayer::drawPolygon(const unsigned char **shape, CRenderDescriptor *descriptor) {
	int nRings = *(int *) (*shape);
	(*shape) += sizeof(int);

	if (nRings == 1) {
		int nPoint = *(int *) (*shape);
		(*shape) += sizeof(int);
		QPolygonF poly(nPoint);
		for (int j = 0; j < nPoint; j++) {
			double x, y;
			x = *(double *) (*shape);
			*shape += sizeof(double);
			y = *(double *) (*shape);
			*shape += sizeof(double);
			mConvert->transToScreen(x, y);
			poly[j].setX(x);
			poly[j].setY(y);
		}
		descriptor->painter->drawPolygon(poly);
	} else {
		QPainterPath path;
		for (int i = 0; i < nRings; i++) {

			int nPoint = *(int *) (*shape);
			(*shape) += sizeof(int);
			QPolygonF poly(nPoint);
			for (int j = 0; j < nPoint; j++) {
				double x, y;
				x = *(double *) (*shape);
				*shape += sizeof(double);
				y = *(double *) (*shape);
				*shape += sizeof(double);
				mConvert->transToScreen(x, y);
				poly[j].setX(x);
				poly[j].setY(y);
			}
			path.addPolygon(poly);
		}
		descriptor->painter->drawPath(path);
	}

}
void CFeatureLayer::setSelectable(bool selectable) {
	mSelectable = selectable;
}
bool CFeatureLayer::getSelectable() {
	return mSelectable;
}
void CFeatureLayer::selectFeature(CRectangle rect, bool clear) {
	if (clear)
		clearSelectedSet();
	if (mFeatClass == NULL)
		return;
	CFeatureCursor cursor;
	CSpatialFilter *filter = new CSpatialFilter();
	mConvert->transRectToMap(rect);
	filter->Rect = rect;
	filter->FetchGeometry = false;
	CFeature *pFeat = new CFeature(mFeatClass);
	mFeatClass->search(filter, cursor);
	while (cursor.NextFeature(*pFeat)) {
		int fid = pFeat->GetFID();
		if (!clear) {
			QSet<int>::iterator it = mSelectedFeatureId.find(fid);
			if (it == mSelectedFeatureId.end())
				mSelectedFeatureId.insert(fid);
			else
				mSelectedFeatureId.erase(it);
		} else
			mSelectedFeatureId.insert(fid);
	}
	delete pFeat;
}
void CFeatureLayer::clearSelectedSet() {

	mSelectedFeatureId.clear();
}


}
