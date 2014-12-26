/*
 * CMapControl.h
 *
 *  Created on: 2011-1-27
 *      Author: pkkj
 */

#ifndef CMAPCONTROL_H_
#define CMAPCONTROL_H_
#include <QGraphicsView>
#include <QResizeEvent>
#include <QRect>
#include <QWheelEvent>
#include <QGraphicsScene>
#include "CRectangle.h"
namespace GUI {

/**
 * @class A map control that display maps
 * Using the QGraphicsView to display graphic items
 */
class CMap;
class CMapControlSetting;
class CMapTool;
class CMapControl: public QGraphicsView {
Q_OBJECT
public:
	CMapControl(QWidget * parent = 0, const char *name = 0);
	~CMapControl();
public:
	void refresh();

	void setMapTool(CMapTool *mapTool);
	CMap *map;
	void panMap(QPointF startPoint, QPointF curPos, QPointF mapPos);
private:
	/**
	 * The map object that containing maps.
	 */

	/**
	 * The render that render all the map
	 */
	QGraphicsScene* mScene;
	CMapControlSetting *mSetting;
	CMapTool *mCurrentMapTool;

protected:
	void resizeEvent(QResizeEvent * e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void wheelEvent(QWheelEvent *e);
};

}
#endif /* CMAPCONTROL_H_ */
