/*
 * CGraphicsContainer.cpp
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#include "CGraphicsContainer.h"
#include "CElement.h"
#include "CRenderDescriptor.h"

using namespace Geometry;
namespace GUI {
bool searchCallback(CElement *pElement, void *context) {
	QList<CElement*>* list = static_cast<QList<CElement*>*> (context);
	list->push_back(pElement);
	return true;

}
bool compareDisplayLevel(const CElement *pEle1,const  CElement *pEle2){
	return pEle1->getDisplayLevel() > pEle2->getDisplayLevel();
}
CGraphicsContainer::CGraphicsContainer() {
}
CGraphicsContainer::~CGraphicsContainer() {
	clear();
}

void CGraphicsContainer::addElement(CElement *pElement) {
	CRectangle rect = pElement->getBoundingRect();
	pElement->setGraphicsContainer(this);
	double minp[2], maxp[2];
	rect.getBoundingBox(minp, maxp);
	mTree.Insert(minp, maxp, pElement);

}
void CGraphicsContainer::removeElement(CElement *pElement) {
	double minp[2], maxp[2];
	pElement->setGraphicsContainer(NULL);
	CRectangle rect= pElement->getBoundingRect();
	rect.getBoundingBox(minp, maxp);
	mTree.Remove(minp, maxp, pElement);
}
void CGraphicsContainer::draw(CRenderDescriptor *descriptor) {
	CRectangle rect = mConvert->getMapRect();
	QList<CElement *> lstElement;
	search(rect, lstElement);
	qSort(lstElement.begin(), lstElement.end(),compareDisplayLevel);
	QList<CElement *>::iterator it;
	for (it = lstElement.begin(); it != lstElement.end(); it++) {
		CElement *pElement = *it;
		pElement->draw(descriptor);
	}
}

void CGraphicsContainer::search(CRectangle rect, QList<CElement *> &lstRes) {
	double minp[2], maxp[2];
	rect.getBoundingBox(minp, maxp);
	mSearchResult.clear();
	int nHits = mTree.Search(minp, maxp, searchCallback, &mSearchResult);
	//printf("hits %d\n", nHits);
	lstRes = mSearchResult;
}
void CGraphicsContainer::clear() {
	CRTree<CElement*, double, 2, double>::iterator it;
	for (mTree.GetFirst(it); !mTree.IsNull(it); mTree.GetNext(it)) {
		delete mTree.GetAt(it);
		mTree.GetNext(it);
	}
	mTree.RemoveAll();
}
}
