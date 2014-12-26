/*
 * CLayer.h
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */

#ifndef CLAYER_H_
#define CLAYER_H_
#include <string>

#include "CMapScreenConvert.h"
#include "CMap.h"
using namespace std;
namespace GUI {
class CRenderDescriptor;
class CLayer {

public:
	CLayer();
	~CLayer();
	string name;

	void setMapScreenConvert(CMapScreenConvert *convert);
	CMapScreenConvert* getMapScreenConvert();
	void setMap(CMap *map);
	virtual void draw(CRenderDescriptor *descriptor) = 0;
	/** The CMap that contains this CFeatureLayer */

protected:
	CMapScreenConvert *mConvert;
	CMap *mMap;
};
}

#endif /* CLAYER_H_ */
