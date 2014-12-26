/*
 * CZoomInTool.cpp
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */
#include <QMouseEvent>
#include <QRubberBand>

#include "CMapToolZoom.h"
#include "CMapControl.h"
#include "CMap.h"
namespace GUI {

CMapToolZoom::CMapToolZoom(CMapControl *mapControl) :
	CMapTool(mapControl) {
	mRubberBand = NULL;
}

void CMapToolZoom::mapMouseReleaseEvent(QMouseEvent *e) {
	if (e->button() != Qt::LeftButton)
		return;
	mRubberBand->hide();
	mMapControl->map->setExtent(QRect(startPoint, e->pos()));
	mMapControl->refresh();

}
void CMapToolZoom::mapMouseMoveEvent(QMouseEvent *e) {
	if (!(e->buttons() & Qt::LeftButton))
		return;
	mRubberBand->setGeometry(QRect(startPoint, e->pos()).normalized());

}
void CMapToolZoom::mapMousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		startPoint = e->pos();
		if (!mRubberBand)
			mRubberBand = new QRubberBand(QRubberBand::Rectangle, mMapControl);
		mRubberBand->setGeometry(QRect(startPoint, QSize()));
		mRubberBand->show();

	}
}
void CMapToolZoom::mapWheelEvent(QWheelEvent *e) {
}
void CMapToolZoom::mapKeyPressEvent(QKeyEvent * e) {
}
void CMapToolZoom::mapKeyReleaseEvent(QKeyEvent * e) {
}
}
