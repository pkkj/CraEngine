/*
 * CMapControl.cpp
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */
#include <cstdio>
#include "CMapControl.h"
#include "CMap.h"
#include "CMapControlSetting.h"
#include "CMapScreenConvert.h"
#include "CMapTool.h"
namespace GUI {

CMapControl::CMapControl(QWidget * parent, const char *name) {
	mScene = new QGraphicsScene();
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(mScene);

	mSetting = new CMapControlSetting();
	map = new CMap(this);
	mScene->addItem(map);
	mScene->update();

	mCurrentMapTool = NULL;
}
CMapControl::~CMapControl() {
	delete map;
	delete mSetting;
}

void CMapControl::refresh() {
	map->render();
}

void CMapControl::setMapTool(CMapTool *mapTool) {
	if (mCurrentMapTool)
		delete mCurrentMapTool;
	mCurrentMapTool = mapTool;
}
void CMapControl::resizeEvent(QResizeEvent * e) {
	map->resize(e->size());
	mScene->setSceneRect(QRectF(0, 0, width(), height()));
	refresh();
}
void CMapControl::mouseReleaseEvent(QMouseEvent *e) {
	if (mCurrentMapTool != NULL) {
		mCurrentMapTool->mapMouseReleaseEvent(e);
		return;
	}

}
void CMapControl::mouseMoveEvent(QMouseEvent *e) {
	if (mCurrentMapTool != NULL) {
		mCurrentMapTool->mapMouseMoveEvent(e);
		return;
	}

}
void CMapControl::mousePressEvent(QMouseEvent *e) {
	if (mCurrentMapTool != NULL) {
		mCurrentMapTool->mapMousePressEvent(e);
		return;
	}

}
void CMapControl::keyPressEvent(QKeyEvent *e) {
	if (mCurrentMapTool != NULL) {
		mCurrentMapTool->mapKeyPressEvent(e);
		return;
	}
}
void CMapControl::keyReleaseEvent(QKeyEvent *e) {
	if (mCurrentMapTool != NULL) {
		mCurrentMapTool->mapKeyReleaseEvent(e);
		return;
	}
}
void CMapControl::panMap(QPointF startPoint, QPointF curPos, QPointF mapPos) {
	QPointF current = curPos - startPoint + mapPos;
	map->setPos(current);
}
void CMapControl::wheelEvent(QWheelEvent *e) {
	map->changeScale(e->delta());
	refresh();
}

}
