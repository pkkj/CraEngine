/*
 * CMainWindow.h
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */

#ifndef MAINWINDOW1_H_
#define MAINWINDOW1_H_



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
#include "CTrainlineQuery.h"
#include "CTrainlineWidget.h"
#include "CLineList.h"
#include <QtGui>
#include <QMainWindow>
#include <QAction>
using namespace Core;
using namespace DataSource;
using namespace Geometry;
using namespace IO;
using namespace GUI;
using namespace std;

class CMainWindow: public QMainWindow {
Q_OBJECT

public:
	CMainWindow();
private slots:
	void panMap();
	void zoomInMap();
	void getTrainLineInfo();
	void getClickLine(const QModelIndex & index);

private:
	void createActions();
	void createMenus();

	void createToolBars();
	void createStatusBar();

	CMapControl *view;

	QMenu *viewMenu;
	QMenu *editMenu;
	QMenu *helpMenu;

	CTrainlineWidget *lineView;
	CTrainlineQuery *trainQuery;
	CLineList *lineList;
	QAction *panMapAct;
	QAction *zoomInMapAct;

	CFeatureClass *pFeatClass1;
	CFeatureClass *pFeatClass2;
	CFeatureClass *pFeatClass3;
};

#endif /* MAINWINDOW1_H_ */
