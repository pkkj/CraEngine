/*
 * CMapTool.h
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */

#ifndef CMAPTOOL_H_
#define CMAPTOOL_H_

#include <QGraphicsView>
#include <QResizeEvent>
#include <QRect>
#include <QWheelEvent>
#include <QGraphicsScene>

namespace GUI {
class CMapControl;
class CMapTool {

public:
	CMapTool(CMapControl *mapControl);
	virtual void mapMouseReleaseEvent(QMouseEvent *e);
	virtual void mapMouseMoveEvent(QMouseEvent *e);
	virtual void mapMousePressEvent(QMouseEvent *e);
	virtual void mapWheelEvent(QWheelEvent *e);
	virtual void mapKeyPressEvent(QKeyEvent * e);
	virtual void mapKeyReleaseEvent(QKeyEvent * e);
protected:
	CMapControl *mMapControl;

};

}

#endif /* CMAPTOOL_H_ */
