/*
 * CTrainlineQuery.cpp
 *
 *  Created on: 2011-2-9
 *      Author: pkkj
 */

#include "CTrainlineQuery.h"
CTrainlineQuery::CTrainlineQuery(QWidget *parent) :
QGroupBox(parent) {
	QVBoxLayout *vbox = new QVBoxLayout;
	lb1 = new QLabel(QString::fromUtf8(string("车次: ").c_str()) );
	txtTrainline = new QLineEdit();
	this->resize(250, this->height());
	btSearch = new QPushButton(QString::fromUtf8(string("搜索: ").c_str()) );

	setMaximumHeight(100);

	vbox->addWidget(lb1);
	vbox->addWidget(txtTrainline);
	vbox->addWidget(btSearch);
	vbox->addStretch(1);

	this->setLayout(vbox);
	connect(txtTrainline, SIGNAL(returnPressed()), btSearch , SLOT(click()));

}

