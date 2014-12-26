/*
 * CPolygonElement.h
 *
 *  Created on: 2011-2-5
 *      Author: pkkj
 */

#ifndef CPOLYGONELEMENT_H_
#define CPOLYGONELEMENT_H_
#include "CShapeElement.h"
#include "CPolygon.h"
using namespace Geometry;
namespace GUI{
class CPolygonElement : public CShapeElement{
public:
	CPolygonElement();
	~CPolygonElement();
	virtual void draw(CRenderDescriptor *descriptor);
protected:
	CPolygon *geometry;
};

}

#endif /* CPOLYGONELEMENT_H_ */
