/*
 * CRenderer.h
 *
 *  Created on: 2011-2-1
 *      Author: pkkj
 */

#ifndef CRENDERER_H_
#define CRENDERER_H_
#include "CFeature.h"
#include <string>
#include <QPen>
namespace GUI{
class CRenderDescriptor;
class CSymbol;

enum RenderType{
	RENDER_SIMPLE
};
class CRenderer{
public:
	CRenderer();
	virtual ~CRenderer();

	string name;
	virtual void preRenderFeature(DataSource::CFeature *pFeat, CRenderDescriptor *descriptor, bool selected) = 0;
	virtual void afterRenderFeature(DataSource::CFeature *pFeat, const QPolygonF &info,
				CRenderDescriptor *descriptor, bool selected) = 0;
	virtual CSymbol* symbolForFeature(DataSource::CFeature *pFeat) = 0;
	virtual RenderType getType() = 0;
	static void defaultRenderer(DataSource::CFeature *pFeat, CRenderDescriptor *descriptor, bool selected);
	static void selectedtRendererPen(CRenderDescriptor *descriptor);

private:
	static QPen selectedPen;
};

}


#endif /* CRENDERER_H_ */
