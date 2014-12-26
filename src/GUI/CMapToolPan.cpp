/*
 * CMapToolPan.cpp
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */

#include "CMapToolPan.h"
#include "CMapControl.h"
#include "CMap.h"
namespace GUI {
CMapToolPan::CMapToolPan(CMapControl *mapControl) :
	CMapTool(mapControl) {
}
void CMapToolPan::mapMouseReleaseEvent(QMouseEvent *e) {
	if (e->button() != Qt::LeftButton)
		return;
	QPointF vec = e->posF() - startPoint;
	mMapControl->map->moveMap(vec);
	mMapControl->map->setPos(QPoint(0, 0));
	mMapControl->refresh();

}
void CMapToolPan::mapMouseMoveEvent(QMouseEvent *e) {
	if (!(e->buttons() & Qt::LeftButton))
		return;
	mMapControl->panMap(startPoint, e->posF(), mapPos);

}
void CMapToolPan::mapMousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		startPoint = e->posF();
		mapPos = mMapControl->map->pos();
	}
}
void CMapToolPan::mapWheelEvent(QWheelEvent *e) {
}

void CMapToolPan::mapKeyPressEvent(QKeyEvent * e) {
}
void CMapToolPan::mapKeyReleaseEvent(QKeyEvent * e) {
}

}
