/*
 * CMapToolPan.h
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */

#ifndef CMAPTOOLPAN_H_
#define CMAPTOOLPAN_H_
#include "CMapTool.h"
namespace GUI{

class CMapControl;
class CMapToolPan : public CMapTool{

public:
	CMapToolPan(CMapControl *mapControl);
	virtual void mapMouseReleaseEvent(QMouseEvent *e);
	virtual void mapMouseMoveEvent(QMouseEvent *e);
	virtual void mapMousePressEvent(QMouseEvent *e);
	virtual void mapWheelEvent(QWheelEvent *e);
	virtual void mapKeyPressEvent(QKeyEvent * e);
		virtual void mapKeyReleaseEvent(QKeyEvent * e);
private:
	QPointF startPoint;
	QPointF mapPos;

};

}


#endif /* CMAPTOOLPAN_H_ */
