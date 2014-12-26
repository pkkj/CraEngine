/*
 * CMapControlSetting.h
 *
 *  Created on: 2011-1-29
 *      Author: pkkj
 */

#ifndef CMAPCONTROLSETTING_H_
#define CMAPCONTROLSETTING_H_
#include <QPoint>
#include <QPointF>
namespace GUI {

class CMapControlSetting {
	friend class CMapControl;

public:
	CMapControlSetting();
	~CMapControlSetting();
private:
	bool panMap;
	QPointF mouseStartPoint;
	QPointF mapPos;
};
}

#endif /* CMAPCONTROLSETTING_H_ */
