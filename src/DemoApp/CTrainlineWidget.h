/*
 * CTrainlineWidget.h
 *
 *  Created on: 2011-2-20
 *      Author: pkkj
 */

#ifndef CTRAINLINEWIDGET_H_
#define CTRAINLINEWIDGET_H_
#include <QtGui>
#include <string>
using namespace std;
class CTrainlineWidget: public QWidget {
Q_OBJECT
public:
	CTrainlineWidget();
	QLabel *lbTitle;
	QLabel *lbFrom;
	QLabel *lbTo;
	QTreeView *lstStation;

};
#endif /* CTRAINLINEWIDGET_H_ */
