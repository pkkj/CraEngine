/*
 * CMapToolSelect.cpp
 *
 *  Created on: 2011-2-3
 *      Author: pkkj
 */

#include "CMapToolSelect.h"
#include "CMapControl.h"
#include "CMap.h"
#include <cstdio>
namespace GUI {
CMapToolSelect::CMapToolSelect(CMapControl *mapControl) :
	CMapTool(mapControl) {
	mRubberBand = NULL;
	shiftOn = false;
}

void CMapToolSelect::mapMouseReleaseEvent(QMouseEvent *e) {
	bool newSelection = true;
	if (e->button() != Qt::LeftButton)
		return;
	mRubberBand->hide();
	if (shiftOn)
		newSelection = false;
	printf("rect %d %d %d %d\n", startPoint.x(), startPoint.y(), e->pos().x(), e->pos().y());
	QRect rect = QRect(QRect(startPoint, e->pos())).normalized();
	rect.setBottom(rect.bottom() - 3);
	rect.setLeft(rect.left() - 3);
	rect.setRight(rect.right() + 3);
	rect.setTop(rect.top() + 3);
	mMapControl->map->selectFeature(rect, newSelection);
	mMapControl->refresh();

}
void CMapToolSelect::mapMouseMoveEvent(QMouseEvent *e) {
	if (!(e->buttons() & Qt::LeftButton))
		return;
	mRubberBand->setGeometry(QRect(startPoint, e->pos()).normalized());

}
void CMapToolSelect::mapMousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		startPoint = e->pos();
		if (!mRubberBand)
			mRubberBand = new QRubberBand(QRubberBand::Rectangle, mMapControl);
		mRubberBand->setGeometry(QRect(startPoint, QSize()));
		mRubberBand->show();

	}
}
void CMapToolSelect::mapWheelEvent(QWheelEvent *e) {
}
void CMapToolSelect::mapKeyPressEvent(QKeyEvent * e) {
	if (e->key() == Qt::Key_Shift)
		shiftOn = true;
}
void CMapToolSelect::mapKeyReleaseEvent(QKeyEvent * e) {
	if (e->key() == Qt::Key_Shift)
		shiftOn = false;
}

}
