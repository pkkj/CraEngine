/*
 * CMainWindow.cpp
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */
#include <Qt>
#include <QtGui>
#include "CTrainlineQuery.h"
#include "CMainWindow.h"
#include "CSimpleRenderer.h"
#include "CMapToolSelect.h"
#include "CLineSymbol.h"
#include "CFillSymbol.h"
#include "CMultiPolygon.h"
#include "CPolygonElement.h"
#include "CGraphicsContainer.h"
#include "CTextElement.h"
#include "CTextSymbol.h"
#include "CMarkerSymbol.h"
#include "CMarkerElement.h"
#include "CTrainlineInfo.h"

#include "Utils.h"
using namespace Geometry;
CMainWindow::CMainWindow() {
	this->setWindowTitle(QString::fromUtf8(string("OGISKit测试程序").c_str()) );
	lineList = new CLineList();
	QDockWidget *dock = new QDockWidget(QString::fromUtf8(string("线路列表").c_str()) , this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock->setWidget(lineList);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	trainQuery = new CTrainlineQuery();
	dock = new QDockWidget(QString::fromUtf8(string("车次查询").c_str()) , this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea);
	dock->setWidget(trainQuery);
	//trainQuery->resize(250, trainQuery->height());
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	lineView = new CTrainlineWidget();
	dock = new QDockWidget(QString::fromUtf8(string("车次信息").c_str()) , this);
	dock->setWidget(lineView);
	//lineView->resize(250, lineView->height());
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	view = new CMapControl();
	setCentralWidget(view);
	//resize(QSize(1000, 600));

	view->map->setBackColor(QColor("#CAFF70"));

	CPostgresqlDataSrcFactory factory;
	CPropertySet info;
	info.setProperty("HOST", "localhost");
	info.setProperty("PORT", "5432");
	info.setProperty("DBNAME", "railway");
	info.setProperty("USER", "postgres");
	info.setProperty("PASSWORD", "198811");

	CDataSrc *pDataSrc = factory.open(info);
	CDataClass *pDataClass1 = pDataSrc->getDataClass("grailway");
	CDataClass *pDataClass2 = pDataSrc->getDataClass("gstation");
	CDataClass *pDataClass3 = pDataSrc->getDataClass("gchina");
	delete pDataSrc;
	pFeatClass1 = dynamic_cast<CFeatureClass *> (pDataClass1);
	pFeatClass2 = dynamic_cast<CFeatureClass *> (pDataClass2);
	pFeatClass3 = dynamic_cast<CFeatureClass *> (pDataClass3);

	{
		CLineSymbol *pLineSymbol = new CLineSymbol();
		pLineSymbol->setColor(Qt::gray);
		pLineSymbol->setWidth(1);
		CSimpleRenderer *pRenderer1 = new CSimpleRenderer();
		pRenderer1->setSymbol(pLineSymbol);

		CFeatureLayer *pFeatLayer3 = new CFeatureLayer();
		pFeatLayer3->setFeatureClass(pFeatClass3);
		pFeatLayer3->setRenderer(pRenderer1);
		view->map->addLayer(pFeatLayer3);
	}

	{
		CLineSymbol *pLineSymbol = new CLineSymbol();
		pLineSymbol->setColor(Qt::white);
		pLineSymbol->setWidth(3);
		CSimpleRenderer *pRenderer1 = new CSimpleRenderer();
		pRenderer1->setSymbol(pLineSymbol);

		CFeatureLayer *pFeatLayer1 = new CFeatureLayer();
		pFeatLayer1->setFeatureClass(pFeatClass1);
		pFeatLayer1->setRenderer(pRenderer1);
		view->map->addLayer(pFeatLayer1);
	}

	{
		CMarkerSymbol *pMarkerSymbol = new CMarkerSymbol();
		pMarkerSymbol->setMarkerStyle(CMarkerSymbol::MARKER_CIRCLE);
		pMarkerSymbol->setSize(3);
		pMarkerSymbol->setInColor("#EEC900");

		CFeatureLayer *pFeatLayer2 = new CFeatureLayer();
		CSimpleRenderer *pRenderer2 = new CSimpleRenderer();
		CTextSymbol *pTextSymbol = new CTextSymbol();
		pTextSymbol->setColor(QColor("#CD8162"));
		pRenderer2->setSymbol(pMarkerSymbol);
		pFeatLayer2->setRenderer(pRenderer2);
		pFeatLayer2->setFeatureClass(pFeatClass2);
		pFeatLayer2->labelEngine->setEnable(true);
		pFeatLayer2->labelEngine->setLabelField("name");
		pFeatLayer2->labelEngine->setTextSymbbol(pTextSymbol);
		view->map->addLayer(pFeatLayer2);
	}
	createActions();
	createMenus();
	connect(trainQuery->btSearch, SIGNAL(clicked()), this, SLOT(getTrainLineInfo()));
	connect(lineList->lstLine, SIGNAL(doubleClicked(const QModelIndex &)), this,
			SLOT(getClickLine(const QModelIndex &)));
	setWindowState(windowState() ^ Qt::WindowMaximized);
}

void CMainWindow::createActions() {
	panMapAct = new QAction("&Pan", this);
	panMapAct->setStatusTip("pan map");
	connect(panMapAct, SIGNAL(triggered()), this, SLOT(panMap()));

	zoomInMapAct = new QAction("&ZoomIn", this);
	zoomInMapAct->setStatusTip("ZoomIn");
	connect(zoomInMapAct, SIGNAL(triggered()), this, SLOT(zoomInMap()));

}
void CMainWindow::createMenus() {
	viewMenu = menuBar()->addMenu(QString::fromUtf8(string("视图").c_str()) );
	viewMenu->addAction(panMapAct);
	viewMenu->addAction(zoomInMapAct);
}

void CMainWindow::zoomInMap() {
	CMapToolZoom *tool = new CMapToolZoom(view);
	view->setMapTool(tool);
	/*CMapToolSelect *tool = new CMapToolSelect(view);
	 view->setMapTool(tool);*/

}

void CMainWindow::panMap() {
	CMapToolPan *tool = new CMapToolPan(view);
	view->setMapTool(tool);

}

void CMainWindow::getClickLine(const QModelIndex & index) {
	string s1;
	QItemSelectionModel *selectionModel = lineList->lstLine->selectionModel();
	QModelIndexList indexes = selectionModel->selectedRows();
	QModelIndex i2 = *indexes.begin();
	//printf("%s\n", i2.data().toString().toStdString().c_str());
	trainQuery->txtTrainline->setText(i2.data().toString());
	getTrainLineInfo();
}

void CMainWindow::getTrainLineInfo() {
	string text = trainQuery->txtTrainline->text().toStdString();
	CTrainlineInfo info;
	QString startS, endS;
	info.getTrainLine(text);

	view->map->graphicsContainer->clear();
	vector<CCoordinate> feat;
	QStandardItemModel *model = new QStandardItemModel(0, 3, this);

	model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8(string("车站").c_str()));
	model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8(string("到点").c_str()));
	model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8(string("发点").c_str()));

	for (size_t i = 0; i < info.stopList.size(); i++) {
		QString s1 = QString::fromUtf8(info.stopList[i].station.c_str());
		QString s2 = QString::fromUtf8(info.stopList[i].arriveTime.c_str());
		QString s3 = QString::fromUtf8(info.stopList[i].departTime.c_str());

		if (i == 0)
			startS = s1;
		if (i == info.stopList.size() - 1)
			endS = s1;
		/* lstStation->addItem(s1 + " " + s2 + " " + s3);*/
		model->insertRow(model->rowCount());
		model->setData(model->index(model->rowCount() - 1, 0), s1);
		model->setData(model->index(model->rowCount() - 1, 1), s2);
		model->setData(model->index(model->rowCount() - 1, 2), s3);
		CFeatureCursor cursor;
		CQueryFilter *filter = new CQueryFilter();
		filter->WhereClause = " name = '" + info.stopList[i].station + "'";
		CFeature *pFeat = new CFeature(pFeatClass1);
		pFeatClass2->search(filter, cursor);
		CCoordinate coord;
		while (cursor.NextFeature(*pFeat)) {
			CGeometry *pg = pFeat->Shape->getGeometry();
			CPoint *pt = dynamic_cast<CPoint *> (pg);
			coord = pt->getCoordinate();

			// Text of the name of station
			{
				CTextElement *pTextElement = new CTextElement();
				pTextElement->setTextAlign(CTextElement::RIGHT_TOP);
				pTextElement->setText(info.stopList[i].station.c_str());
				pTextElement->setPos(coord);
				CTextSymbol *pTextSymbol = new CTextSymbol();
				pTextSymbol->setColor(Qt::black);
				pTextSymbol->setBackStyle(CTextSymbol::BACK_RECT);
				QColor color(Qt::white);
				color.setAlpha(100);
				pTextSymbol->setBackColor(color);
				pTextSymbol->setBackColor(color);
				QFont ff;
				ff.setBold(true);
				ff.setPointSize(12);
				pTextSymbol->setFont(ff);
				pTextElement->setTextSymbol(pTextSymbol);
				view->map->graphicsContainer->addElement(pTextElement);
			}

			// Text of the ID
			{
				CTextElement *pTextElement = new CTextElement();
				pTextElement->setTextAlign(CTextElement::LEFT_TOP);
				pTextElement->setText(Int2Str(i + 1) + " ");
				pTextElement->setPos(coord);
				CTextSymbol *pTextSymbol = new CTextSymbol();
				pTextSymbol->setColor(Qt::red);
				pTextSymbol->setBackStyle(CTextSymbol::BACK_CIRCLE);
				pTextSymbol->setBackColor(QColor("#EEDC82"));
				QFont ff;
				ff.setBold(true);
				ff.setPointSize(12);
				ff.setFamily("Tahoma");
				pTextSymbol->setFont(ff);
				pTextElement->setTextSymbol(pTextSymbol);
				view->map->graphicsContainer->addElement(pTextElement);
			}

			CMarkerElement *pElement = new CMarkerElement();
			CMarkerSymbol *pMarkerSymbol = new CMarkerSymbol();
			pMarkerSymbol->setMarkerStyle(CMarkerSymbol::MARKER_CIRCLE);
			pMarkerSymbol->setSize(6);
			pMarkerSymbol->setInColor(Qt::yellow);
			pMarkerSymbol->setOutColor(Qt::black);
			pMarkerSymbol->setWidth(0);
			pElement->setPos(coord.x, coord.y);
			pElement->setSymbol(pMarkerSymbol);
			view->map->graphicsContainer->addElement(pElement);
			break;
		}
		lineView->lbTitle->setText(QString::fromUtf8(string("车次: ").c_str()) + trainQuery->txtTrainline->text());
		lineView->lbFrom->setText(QString::fromUtf8(string("发站: ").c_str())  + startS);
		lineView->lbTo->setText(QString::fromUtf8(string("终到: ").c_str())  + endS);
		lineView->lstStation->setModel(model);
		lineView->lstStation->setColumnWidth(0, 70);
		lineView->lstStation->setColumnWidth(1, 50);
		lineView->lstStation->setColumnWidth(2, 50);

	}
	view->refresh();
}
