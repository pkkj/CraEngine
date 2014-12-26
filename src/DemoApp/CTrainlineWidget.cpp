/*
 * CTrainlineWidget.cpp
 *
 *  Created on: 2011-2-20
 *      Author: pkkj
 */

#include "CTrainlineWidget.h"

CTrainlineWidget::CTrainlineWidget() {
	QFont f1;
	f1.setFamily("Tahoma");
	this->setFont(f1);
	this->resize(250, this->height());
	QVBoxLayout *mainLayout = new QVBoxLayout();
	//mainLayout->setMargin(3);
	lbTitle = new QLabel(QString::fromUtf8(string("车次").c_str()));
	QFont f2;
	f2.setPointSize(16);
	this->setFont(f1);

	lbTitle->setFont(f2);

	f2.setPointSize(12);
	lbFrom = new QLabel(QString::fromUtf8(string("发站").c_str()));
	lbFrom->setFont(f2);
	lbTo = new QLabel(QString::fromUtf8(string("终到").c_str()));
	lbTo->setFont(f2);

	lstStation = new QTreeView();
	mainLayout->addWidget(lbTitle);
	mainLayout->addWidget(lbFrom);
	mainLayout->addWidget(lbTo);
	mainLayout->addWidget(lstStation);
	setLayout(mainLayout);

}
