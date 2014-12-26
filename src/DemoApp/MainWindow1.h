/*
 * MainWindow1.h
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */

#ifndef MAINWINDOW1_H_
#define MAINWINDOW1_H_

#include <QtGui>

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

#include "CPropertySet.h"
#include "CPostgresqlDataSrcFactory.h"
#include "CDataSrc.h"
#include "CEnumDataClass.h"
#include "CDataClass.h"
#include "CFeatureClass.h"
#include "CQueryFilter.h"
#include "CGeometry.h"
#include "CFeatureCursor.h"
#include "CEWKTWriter.h"
#include "CMapControl.h"
#include "CMap.h"
#include "CFeatureLayer.h"
#include "CMapToolZoom.h"
#include "CMapToolPan.h"

#include <QtGui>
#include <QAction>
using namespace Core;
using namespace DataSource;
using namespace Geometry;
using namespace IO;
using namespace GUI;
using namespace std;

class MainWindow1: public QMainWindow {
Q_OBJECT

public:
	MainWindow1();
private slots:
	void panMap();
	void zoomInMap();

private:
	void createActions();
	void createMenus();
	     void createToolBars();
	 void createStatusBar();

	CMapControl *view;

	QMenu *viewMenu;
	QMenu *editMenu;
	QMenu *helpMenu;

	QAction *panMapAct;
	QAction *zoomInMapAct;

};

#endif /* MAINWINDOW1_H_ */
