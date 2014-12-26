/*
 * CGraphicsContainer.h
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#ifndef CGRAPHICSCONTAINER_H_
#define CGRAPHICSCONTAINER_H_
#include <QList>
#include "CRTree.hpp"
#include "CRectangle.h"
#include "CLayer.h"
using namespace Algorithm;
namespace GUI {
class CElement;
class CRenderDescriptor;
class CGraphicsContainer: public CLayer {
public:
	CGraphicsContainer();
	~CGraphicsContainer();

	void addElement(CElement *pElement);
	void removeElement(CElement *pElement);
	void clear();
	void draw(CRenderDescriptor *descriptor);
private:
	void search(Geometry::CRectangle rect, QList<CElement *> &lstRes);

	CRTree<CElement*, double, 2, double> mTree;
	QList<CElement*> mSearchResult;

};
}

#endif /* CGRAPHICSCONTAINER_H_ */
