/*
 * CFeatureLayer.h
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */

#ifndef CFEATURELAYER_H_
#define CFEATURELAYER_H_

#include <string>
#include <QSet>
using namespace std;

#include <QPainter>

#include "CLayer.h"
#include "CFeatureClass.h"
#include "CLabelEngine.h"
#include "CFeature.h"
#include "CRenderDescriptor.h"
using namespace DataSource;
namespace GUI {
class CMap;
class CRenderer;
class CFeatureLayer: public CLayer {
	friend class CMap;
public:
	CFeatureLayer();
	~CFeatureLayer();
public:

	void draw(CRenderDescriptor *descriptor);
	/**
	 * Set the feature class for this feature layer.
	 * Attention: once the feature class was assigned to the layer. Do not delete this feature class.
	 * The CFeatureLayer class will deal with it.
	 */
	void setFeatureClass(CFeatureClass * fc);
	CFeatureClass *getFeatureClass();

	void setRenderer(CRenderer *renderer);
	CRenderer *getRenderer();

	void selectFeature(CRectangle rect,bool clear);
	void clearSelectedSet();
	void setSelectable(bool selectable);
	bool getSelectable();

	CLabelEngine *labelEngine;

protected:

private:
	CFeatureClass *mFeatClass;
	CRenderer *mRenderer;

	void drawFeature(CFeature *pFeature, CRenderDescriptor *descriptor, bool selected);
	void drawCoordSeq(const unsigned char **shape, CRenderDescriptor *descriptor);
	void drawPolygon(const unsigned char **shape, CRenderDescriptor *descriptor);

	bool mSelectable;
	QSet<int> mSelectedFeatureId;
};

}

#endif /* CFEATURELAYER_H_ */
