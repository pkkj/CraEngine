/*
 * CLabelEngine.cpp
 *
 *  Created on: 2011-2-4
 *      Author: pkkj
 */
#include "CLabelEngine.h"
#include "CTextSymbol.h"
#include "CRenderDescriptor.h"
namespace GUI {
bool searchCallback(int id, void* arg) {
	return false;
}
CLabelEngine::CLabelEngine() {
	mDescriptor = NULL;
	mTextSymbol = new CTextSymbol();
	ptOffset = 1;
}
CLabelEngine::~CLabelEngine() {
	delete mTextSymbol;
}
void CLabelEngine::setLabelField(string field) {
	labelField = field;
}

void CLabelEngine::setEnable(bool enable) {
	engineEnable = enable;
}
string CLabelEngine::getText(CFeature * pFeature) {
	return pFeature->GetValue(labelField);
}

void CLabelEngine::preparePointFeature(CFeature * pFeature, double x, double y) {
	if (!engineEnable)
		return;
	string text = getText(pFeature);
	QString qtext = QString::fromUtf8(text.c_str());
	PFList.append(PointFeatureList(qtext, x, y));
	double minp[2] = { x - 0.5, y - 0.5 }, maxp[2] = { x + 0.5, y + 0.5};
	mTree.Insert(minp, maxp, 0);
}

bool CLabelEngine::tryPutText(double x, double y, double width, double height, QString text) {
	double minp[2] = { x, y - height }, maxp[2] = { x + width, y };
	int nHits = mTree.Search(minp, maxp, searchCallback, NULL);
	if (nHits == 0) {
		mTree.Insert(minp, maxp, 0);
		//mDescriptor->painter->drawRect(x, y - height,width, height);
		mDescriptor->painter->drawText(QPoint(x, y), text);
		return true;
	}
	return false;
}
void CLabelEngine::preparePolygonFeature(CFeature * pFeature, QPolygon &polygon) {
	string text = getText(pFeature);
	prepareSymbol(mDescriptor);

}
void CLabelEngine::preparePolylineFeature(CFeature * pFeature, QPolygon &polyline) {
	string text = getText(pFeature);
	prepareSymbol(mDescriptor);
}

void CLabelEngine::setTextSymbbol(CTextSymbol *pTextSymbol) {
	delete mTextSymbol;
	mTextSymbol = pTextSymbol;
}

const CTextSymbol *CLabelEngine::getTextSymbol() {
	return mTextSymbol;

}
void CLabelEngine::prepareSymbol(CRenderDescriptor *descriptor) {
	descriptor->painter->setFont(mTextSymbol->getFont());
	descriptor->painter->setPen(mTextSymbol->getColor());
}

void CLabelEngine::beginLabeling(CRenderDescriptor *descriptor,
		COpenGISType::OPENGIS_TYPE featureType) {
	mDescriptor = descriptor;
	mFeatureType = featureType;
	mTree.RemoveAll();
	PFList.clear();

}
void CLabelEngine::labelPointFeature(QString text, double x, double y) {
	prepareSymbol(mDescriptor);

	// Try all the direction
	QFontMetricsF fm(mDescriptor->painter->font());
	double textWidth = fm.width(text) ;
	double textHeight = fm.height()-5;
	if (tryPutText(x + ptOffset, y - ptOffset, textWidth, textHeight, text))
		return;
	if (tryPutText(x + ptOffset, y +ptOffset + textHeight, textWidth, textHeight, text))
		return;
	if (tryPutText(x - ptOffset - textWidth, y - ptOffset, textWidth, textHeight, text))
		return;
	if (tryPutText(x - ptOffset - textWidth, y +ptOffset + textHeight, textWidth, textHeight, text))
		return;

	if (tryPutText(x - textWidth / 2, y - ptOffset, textWidth, textHeight, text))
		return;
	if (tryPutText(x - textWidth / 2, y + ptOffset + textHeight, textWidth, textHeight, text))
		return;
	if (tryPutText(x + ptOffset, y + textHeight / 2, textWidth, textHeight, text))
		return;
	if (tryPutText(x - ptOffset - textWidth, y + textHeight / 2, textWidth, textHeight, text))
		return;
	//mDescriptor->painter->drawText(QPoint(x - ptOffset - textWidth/2, y + ptOffset + textHeight/2), text);
}
void CLabelEngine::endLabeling() {
	if (!engineEnable)
		return;
	switch (mFeatureType) {
	case COpenGISType::OGIS_POINT:
	case COpenGISType::OGIS_MULTIPOINT:
		for (QList<PointFeatureList>::iterator it = PFList.begin(); it != PFList.end(); it++) {
			labelPointFeature(it->text, it->x, it->y);
		}
		break;
	default:
		break;
	}

}
}
