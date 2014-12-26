/*
 * main.cpp
 *
 *  Created on: 2010-12-26
 *      Author: pkkj
 */
#include <QtGui>
#include "CMainWindow.h"
#include "MainWindow1.h"
#include "CTrainlineQuery.h"
#include <cstdio>

int main(int argc, char **argv) {
	//freopen("out.txt","w",stdout);
	QApplication app(argc, argv);
	CMainWindow t1;
	t1.show();

	return app.exec();

}
