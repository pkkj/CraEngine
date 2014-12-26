/*
 * CElement.h
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#ifndef CELEMENT_H_
#define CELEMENT_H_
#include "CRectangle.h"
namespace GUI {
class CSymbol;
class CRenderDescriptor;
class CGraphicsContainer;


class CElement {

public:
	CElement();
	CElement(CElement &element);
	~CElement();

	virtual Geometry::CRectangle getBoundingRect() const = 0;
	virtual void draw(CRenderDescriptor *descriptor) = 0;
	void setGraphicsContainer(CGraphicsContainer *pGraphicsContainter );

	void setDisplayLevel(int level);
	int getDisplayLevel() const;
protected:
	CGraphicsContainer *mGraphicsContainer;
	int displayLevel;
};
}

#endif /* CELEMENT_H_ */
