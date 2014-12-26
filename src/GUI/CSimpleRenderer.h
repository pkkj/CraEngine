/*
 * CSimpleRenderer.h
 *
 *  Created on: 2011-2-1
 *      Author: pkkj
 */

#ifndef CSIMPLERENDERER_H_
#define CSIMPLERENDERER_H_
#include "CRenderer.h"
#include <QPolygonF>
namespace GUI {
class CSymbol;
class CSimpleRenderer: public CRenderer {
public:
	CSimpleRenderer();
	virtual ~CSimpleRenderer();

	void
	preRenderFeature(DataSource::CFeature *pFeat, CRenderDescriptor *descriptor, bool selected);

	void afterRenderFeature(DataSource::CFeature *pFeat, const QPolygonF &info,
			CRenderDescriptor *descriptor, bool selected);
	CSymbol* symbolForFeature(DataSource::CFeature *pFeat);

	CSymbol* getSymbol();
	void setSymbol(CSymbol *symbol);
	RenderType getType();

private:

	CSymbol* mSymbol;
};
}

#endif /* CSIMPLERENDERER_H_ */
