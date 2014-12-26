/*
 * MainWindow1.cpp
 *
 *  Created on: 2011-1-30
 *      Author: pkkj
 */
#include <Qt>
#include "MainWindow1.h"
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
#include "Utils.h"
using namespace Geometry;
MainWindow1::MainWindow1() {
	view = new CMapControl();
	setCentralWidget(view);
	resize(QSize(200, 200));

	CPostgresqlDataSrcFactory factory;
	CPropertySet info;
	info.setProperty("HOST", "localhost");
	info.setProperty("PORT", "5432");
	info.setProperty("DBNAME", "ctest");
	info.setProperty("USER", "postgres");
	info.setProperty("PASSWORD", "198811");

	CDataSrc *pDataSrc = factory.open(info);
	CDataClass *pDataClass1 = pDataSrc->getDataClass("ptest1");
	CDataClass *pDataClass2 = pDataSrc->getDataClass("city3");
	CDataClass *pDataClass3 = pDataSrc->getDataClass("china");
	delete pDataSrc;
	CFeatureClass *pFeatClass1 = dynamic_cast<CFeatureClass *> (pDataClass1);
	CFeatureClass *pFeatClass2 = dynamic_cast<CFeatureClass *> (pDataClass2);
	CFeatureClass *pFeatClass3 = dynamic_cast<CFeatureClass *> (pDataClass3);

	/*CLineSymbol *pSymbol1 = new CLineSymbol();
	 pSymbol1->setColor(Qt::darkRed);

	 CLineSymbol *pSymbol2 = new CLineSymbol();
	 pSymbol2->setColor(Qt::blue);

	 CSimpleRenderer *pRenderer1 = new CSimpleRenderer();
	 pRenderer1->setSymbol(pSymbol1);
	 CSimpleRenderer *pRenderer2 = new CSimpleRenderer();
	 pRenderer2->setSymbol(pSymbol2);*/
	CMarkerSymbol *pSymbol3 = new CMarkerSymbol();
	//pSymbol3->setMarkerStyle(CMarkerSymbol::MARKER_DIAMOND);
	pSymbol3->setMarkerStyle(CMarkerSymbol::MARKER_CIRCLE);
	pSymbol3->setSize(3);
	pSymbol3->setInColor(Qt::yellow);

	CFillSymbol *pSymbol1 = new CFillSymbol();
	pSymbol1->setColor(Qt::darkBlue);
	pSymbol1->setStyle(Qt::SolidPattern);

	CLineSymbol *pSymbol2 = new CLineSymbol();
	pSymbol2->setColor(Qt::blue);
	pSymbol1->setOutline(*pSymbol2);

	CSimpleRenderer *pRenderer1 = new CSimpleRenderer();
	pRenderer1->setSymbol(pSymbol1);
/*

	CFeatureLayer *pFeatLayer1 = new CFeatureLayer();
	pFeatLayer1->setFeatureClass(pFeatClass1);
	pFeatLayer1->setRenderer(pRenderer1);
	view->map->addLayer(pFeatLayer1);
*/
/*

	CFeatureLayer *pFeatLayer2 = new CFeatureLayer();
	CSimpleRenderer *pRenderer2 = new CSimpleRenderer();
	pRenderer2->setSymbol(pSymbol3);
	pFeatLayer2->setRenderer(pRenderer2);
	pFeatLayer2->setFeatureClass(pFeatClass2);
	pFeatLayer2->labelEngine->setEnable(true);
	pFeatLayer2->labelEngine->setLabelField("name");
	view->map->addLayer(pFeatLayer2);
*/

	CFeatureLayer *pFeatLayer3 = new CFeatureLayer();
	pFeatLayer3->setFeatureClass(pFeatClass3);
	view->map->addLayer(pFeatLayer3);

	createActions();
	createMenus();

	/*CFeatureCursor cursor;
	 CQueryFilter *filter = new CQueryFilter();
	 CFeature *pFeat = new CFeature(pFeatClass1);
	 pFeatClass1->search(filter, cursor);
	 while (cursor.NextFeature(*pFeat)) {
	 CGeometry *pg = pFeat->Shape->getGeometry();
	 CMultiPolygon *pmp = dynamic_cast<CMultiPolygon *> (pg);
	 CPolygon *poly = (CPolygon *) pmp->getGeometryAt(0);
	 CLineString *linestring = poly->getShell();

	 if (poly->getNumHoles() > 0) {
	 CFillSymbol *pSymbol1 = new CFillSymbol();
	 pSymbol1->setColor(Qt::blue);
	 pSymbol1->setStyle(Qt::SolidPattern);

	 CPolygonElement *pPolyElement = new CPolygonElement();
	 pPolyElement->setSymbol(pSymbol1);
	 pPolyElement->setGeometry(poly);
	 view->map->graphicsContainer->addElement(pPolyElement);

	 for (size_t i = 0; i < linestring->getNumPoints(); i++) {
	 CCoordinate co(linestring->getCoordinateAt(i));
	 CMarkerElement *pMarkElement = new CMarkerElement();
	 CMarkerSymbol *pSymbol  = new CMarkerSymbol();
	 pSymbol->setSize(2);
	 pSymbol->setInColor(Qt::green);
	 pSymbol->setOutColor(QColor());
	 pMarkElement->setPos(co.x, co.y);
	 pMarkElement->setSymbol(pSymbol);

	 view->map->graphicsContainer->addElement(pMarkElement);
	 }
	 }
	 }
	 delete pFeat;*/
}

void MainWindow1::createActions() {
	panMapAct = new QAction("&Pan", this);
	panMapAct->setStatusTip("pan map");
	connect(panMapAct, SIGNAL(triggered()), this, SLOT(panMap()));

	zoomInMapAct = new QAction("&ZoomIn", this);
	zoomInMapAct->setStatusTip("ZoomIn");
	connect(zoomInMapAct, SIGNAL(triggered()), this, SLOT(zoomInMap()));

}
void MainWindow1::createMenus() {
	viewMenu = menuBar()->addMenu("&View");
	viewMenu->addAction(panMapAct);
	viewMenu->addAction(zoomInMapAct);
}

void MainWindow1::zoomInMap() {
	CMapToolZoom *tool = new CMapToolZoom(view);
	 view->setMapTool(tool);
/*	CMapToolSelect *tool = new CMapToolSelect(view);
	view->setMapTool(tool);*/

}

void MainWindow1::panMap() {
	CMapToolPan *tool = new CMapToolPan(view);
	view->setMapTool(tool);

}
