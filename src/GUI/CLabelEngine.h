/*
 * CLabelEngine.h
 *
 *  Created on: 2011-2-4
 *      Author: pkkj
 */

#ifndef CLABELENGINE_H_
#define CLABELENGINE_H_
#include "CFeature.h"
#include "CRTree.hpp"
#include <string>
#include <QPainterPath>
using namespace std;
using namespace DataSource;
using namespace Algorithm;
namespace GUI {

class CRenderDescriptor;
class CTextSymbol;

struct PointFeatureList {
	PointFeatureList() {
	}
	PointFeatureList(QString text, double x, double y) :
		text(text), x(x), y(y) {
	}
	QString text;
	double x;
	double y;

};

class CLabelEngine {
public:
	CLabelEngine();
	~CLabelEngine();
	void setLabelField(string field);
	void setEnable(bool enable);
	void preparePointFeature(CFeature * pFeature, double x, double y);
	void preparePolygonFeature(CFeature * pFeature, QPolygon &polygon);
	void preparePolylineFeature(CFeature * pFeature, QPolygon &polyline);

	void setTextSymbbol(CTextSymbol *pTextSymbol);
	const CTextSymbol *getTextSymbol();

	void beginLabeling(CRenderDescriptor *descriptor, COpenGISType::OPENGIS_TYPE featureType);
	void endLabeling();
	void insertFeature(CFeature *pFeature, double x, double y);
protected:
	string getText(CFeature * pFeature);
	void prepareSymbol(CRenderDescriptor *descriptor);
	bool tryPutText(double x, double y, double width, double height, QString text);

	void labelPointFeature(QString text, double x, double y);

	double ptOffset;
	string labelField;
	bool engineEnable;
	CTextSymbol *mTextSymbol;
	CRTree<int, double, 2, double> mTree;
	CRenderDescriptor *mDescriptor;
	COpenGISType::OPENGIS_TYPE mFeatureType;
	QList<PointFeatureList> PFList;
};

}
#endif /* CLABELENGINE_H_ */
