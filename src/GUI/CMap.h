/*
 * CMap.h
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */

#ifndef CMAP_H_
#define CMAP_H_
#include <string>
#include <vector>
using namespace std;

#include <QGraphicsItem>
#include <QGraphicsView>
#include "CRectangle.h"
using namespace Geometry;

namespace GUI {
class CLayer;
class CMapControl;
class CFeatureLayer;
class CMapScreenConvert;
class CRenderDescriptor;
class CGraphicsContainer;
class CMap: public QGraphicsItem {
	friend class CMapControl;
public:
	CMap(QGraphicsView *parent);
	~CMap();

public:
	void resize(QSize size);
	/**
	 * Add a layer into the map set.
	 * Attention: once a layer was inserted into a map set, the map set take control this layer.
	 * The layer will be release by CMap!
	 * @param the layer to be add
	 */
	bool addLayer(CLayer *layer);
	size_t findLayer(string layerName);
	void deleteLayer(string layerName);
	void deleteLayer(size_t layerID);
	size_t layerCount();
	CLayer *getLayer(size_t layerID);


	void render();
	void changeScale(int delta);
	void moveMap(QPointF vec);
	void setExtent(QRect screenRect);

	void selectFeature(QRect screenRect, bool clear);

	void setBackColor(QColor color);
	QColor getBackColor();
	CGraphicsContainer *graphicsContainer;
private:

	QPixmap mPixmap;
	CMapScreenConvert *mMapScreenConvert;
	CMapControl *mMapControl;
	vector<CLayer *> mLayers;
	CRenderDescriptor *mDescriptor;
	QColor mBackColor;
protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

}

#endif /* CMAP_H_ */
