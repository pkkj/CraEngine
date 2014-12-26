/*
 * CShapeElement.h
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#ifndef CSHAPEELEMENT_H_
#define CSHAPEELEMENT_H_
#include "CElement.h"
#include "CGeometry.h"
using namespace Geometry;
namespace GUI {
class CShapeElement: public CElement {
public:
	CShapeElement();
	CShapeElement(CShapeElement &element);
	~CShapeElement();
	virtual void draw(CRenderDescriptor *descriptor) = 0;
	virtual Geometry::CRectangle getBoundingRect() const;
	void setGeometry(CGeometry *pGeometry);
	CGeometry *getGeometry();

	void setSymbol(CSymbol *pSymbol);
	CSymbol* getSymbol();
protected:
	CSymbol *mSymbol;
	CGeometry *mGeometry;
};
}

#endif /* CSHAPEELEMENT_H_ */
