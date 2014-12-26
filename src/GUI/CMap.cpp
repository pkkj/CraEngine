/*
 * CMap.cpp
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */

#include "CMap.h"
#include "CLayer.h"
#include "CFeatureLayer.h"
#include "CMapScreenConvert.h"
#include "CRectangle.h"
#include "CMapControl.h"
#include "CRenderDescriptor.h"
#include "CGraphicsContainer.h"
namespace GUI {

CMap::CMap(QGraphicsView *parent) {
	mMapScreenConvert = new CMapScreenConvert();
	mDescriptor = new CRenderDescriptor();
	mMapControl = qobject_cast<CMapControl *> (parent);

	graphicsContainer = new CGraphicsContainer();
	graphicsContainer->setMap(this);
	graphicsContainer->setMapScreenConvert(mMapScreenConvert);
}
CMap::~CMap() {
	for (size_t i = 0; i < mLayers.size(); i++) {
		delete mLayers[i];
	}
	delete mMapScreenConvert;
	delete mDescriptor;
	delete graphicsContainer;
}

void CMap::resize(QSize size) {
	mMapScreenConvert->setScreenSize(size);
	mPixmap = QPixmap(size);
	CRectangle rect = mMapScreenConvert->mMapRect;
	printf("rect %lf %lf %lf %lf\n", rect.minx, rect.miny, rect.maxx, rect.maxy);
	QSize sz = mMapScreenConvert->mScrSize;
	printf("size %d %d\n", size.width(), size.height());
}

QRectF CMap::boundingRect() const {
	return QRectF(0, 0, mPixmap.width(), mPixmap.height());
}

void CMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->drawPixmap(0, 0, mPixmap);
}

void CMap::render() {
	mPixmap.fill(mBackColor);
	QPainter painter;
	painter.setRenderHint(QPainter::Antialiasing);
	painter.begin(&mPixmap);
	painter.setClipRect(mPixmap.rect());
	mDescriptor->painter = &painter;
	for (size_t i = 0; i < mLayers.size(); i++) {
		CLayer *pLayer = mLayers[i];
		// Try: it is a CFeatureLayer
		CFeatureLayer *pFeatLayer = dynamic_cast<CFeatureLayer *> (pLayer);
		if (pFeatLayer != NULL) {
			// It is a feature layer
			pFeatLayer->draw(mDescriptor);

		}
	}
	graphicsContainer->draw(mDescriptor);
	painter.end();
	update();
}

void CMap::changeScale(int delta) {
	Geometry::CRectangle rect = mMapScreenConvert->getMapRect();
	double dx = rect.maxx - rect.minx, dy = rect.maxy - rect.miny;
	int amount = delta > 0 ? delta : -delta;
	double sign = delta > 0 ? 1 : -1;
	double rate = 1 + sign * (double) (amount / 120) * 0.25;
	dx *= rate, dy *= rate;
	double midx = (rect.minx + rect.maxx) / 2;
	double midy = (rect.miny + rect.maxy) / 2;
	rect.minx = midx - dx / 2, rect.maxx = midx + dx / 2;
	rect.miny = midy - dy / 2, rect.maxy = midy + dy / 2;

	mMapScreenConvert->setMapExtent(rect);
}

void CMap::moveMap(QPointF vec) {
	double dx = vec.x() / mMapScreenConvert->factor, dy = vec.y() / mMapScreenConvert->factor;
	CRectangle rect = mMapScreenConvert->getMapRect();
	rect.minx -= dx;
	rect.maxx -= dx;
	rect.miny += dy;
	rect.maxy += dy;
	mMapScreenConvert->setMapExtent(rect);
}

void CMap::setExtent(QRect screenRect) {
	screenRect = screenRect.normalized();
	double x1 = screenRect.left();
	double y1 = screenRect.bottom();
	double x2 = screenRect.right();
	double y2 = screenRect.top();
	mMapScreenConvert->transToMap(x1, y1);
	mMapScreenConvert->transToMap(x2, y2);
	CRectangle rect(x1, y1, x2, y2);
	mMapScreenConvert->setMapExtent(rect);
}

void CMap::selectFeature(QRect screenRect, bool clear) {
	double x1, y1, x2, y2;
	screenRect = screenRect.normalized();
	x1 = screenRect.left(), y1 = screenRect.bottom();
	x2 = screenRect.right(), y2 = screenRect.top();
	CRectangle rect = CRectangle(x1, y1, x2, y2);
	for (size_t i = 0; i < mLayers.size(); i++) {
		CFeatureLayer *pFeatLayer = dynamic_cast<CFeatureLayer*> (mLayers[i]);
		if (pFeatLayer != NULL) {
			if (pFeatLayer->getSelectable())
				pFeatLayer->selectFeature(rect, clear);
		}

	}
}
/*
 * Layer operation function
 */
bool CMap::addLayer(CLayer *layer) {
	CFeatureLayer *pFeatLayer = dynamic_cast<CFeatureLayer *> (layer);
	if (pFeatLayer != NULL) {
		if (pFeatLayer->getFeatureClass() == NULL)
			return false;
		Geometry::CRectangle rect = pFeatLayer->mFeatClass->getExtent();
		mMapScreenConvert->setMapExtent(rect);
	}
	mLayers.push_back(layer);
	layer->setMap(this);
	layer->setMapScreenConvert(mMapScreenConvert);

	mMapControl->refresh();
	return true;

}
void CMap::deleteLayer(string layerName) {
	for (vector<CLayer *>::iterator it = mLayers.begin(); it != mLayers.end(); it++)
		if ((*it)->name == layerName) {
			delete *it;
			mLayers.erase(it);
		}

}
void CMap::deleteLayer(size_t layerID) {

}
size_t CMap::layerCount() {
	return mLayers.size();
}
CLayer *CMap::getLayer(size_t layerID) {
	return mLayers[layerID];
}
size_t CMap::findLayer(string layerName) {
	for (size_t i = 0; i < mLayers.size(); i++)
		if (mLayers[i]->name == layerName)
			return i;
	return -1;
}

/*
 * End of layer operation
 */
void CMap::setBackColor(QColor color) {
	mBackColor = color;
}
QColor CMap::getBackColor() {
	return mBackColor;
}
}
