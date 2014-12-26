/*
 * CLineList.h
 *
 *  Created on: 2011-2-22
 *      Author: pkkj
 */

#ifndef CLINELIST_H_
#define CLINELIST_H_
#include <QtGui>
class CLineList: public QWidget {
Q_OBJECT
public:
	CLineList();
	QTableView *lstLine;
	QPushButton *btSearch;
	QPushButton *btRefresh;

public:
	void refreshData();



};

#endif /* CLINELIST_H_ */
