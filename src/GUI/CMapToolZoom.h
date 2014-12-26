/*
 * CZoomInTool.h
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */

#ifndef CMAPTOOLZOOM_H_
#define CMAPTOOLZOOM_H_
#include <QPoint>
#include <QRubberBand>
#include "CMapTool.h"
namespace GUI {
class CMapControl;
class CMapToolZoom: public CMapTool {
public:
	CMapToolZoom(CMapControl *mapControl);
	virtual void mapMouseReleaseEvent(QMouseEvent *e);
	virtual void mapMouseMoveEvent(QMouseEvent *e);
	virtual void mapMousePressEvent(QMouseEvent *e);
	virtual void mapWheelEvent(QWheelEvent *e);
	virtual void mapKeyPressEvent(QKeyEvent * e);
		virtual void mapKeyReleaseEvent(QKeyEvent * e);
private:
	QPoint startPoint;
	QRubberBand *mRubberBand;

};

}
#endif /* CMAPTOOLZOOM_H_ */
