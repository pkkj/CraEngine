/*
 * CTrainlineQuery.h
 *
 *  Created on: 2011-2-9
 *      Author: pkkj
 */

#ifndef CTRAINLINEQUERY_H_
#define CTRAINLINEQUERY_H_
#include <QGroupBox>
#include <QtGui>

#include <string>
using namespace std;
class CTrainlineQuery: public QGroupBox {
Q_OBJECT
public:
	CTrainlineQuery(QWidget *parent = 0);

	QLabel *lb1;
	QLineEdit *txtTrainline;
	QPushButton *btSearch;

};
#endif /* CTRAINLINEQUERY_H_ */
