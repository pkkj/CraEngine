/*
 * CMapToolSelect.h
 *
 *  Created on: 2011-2-3
 *      Author: pkkj
 */

#ifndef CMAPTOOLSELECT_H_
#define CMAPTOOLSELECT_H_
#include "CMapTool.h"
#include <QRubberBand>
namespace GUI{

class CMapToolSelect : public CMapTool{
public:
	CMapToolSelect(CMapControl *mapControl);
	virtual void mapMouseReleaseEvent(QMouseEvent *e);
	virtual void mapMouseMoveEvent(QMouseEvent *e);
	virtual void mapMousePressEvent(QMouseEvent *e);
	virtual void mapWheelEvent(QWheelEvent *e);
	virtual void mapKeyPressEvent(QKeyEvent * e);
		virtual void mapKeyReleaseEvent(QKeyEvent * e);
private:
	QPoint startPoint;
	QRubberBand *mRubberBand;
	bool shiftOn;
};
}

#endif /* CMAPTOOLSELECT_H_ */
