/*
 * CLineList.cpp
 *
 *  Created on: 2011-2-22
 *      Author: pkkj
 */

#include "CLineList.h"
#include <string>
#include <libpq-fe.h>
using namespace std;

CLineList::CLineList() {
	QGridLayout *layout = new QGridLayout;
	lstLine = new QTableView();
	btSearch = new QPushButton(QString::fromUtf8(string("搜索: ").c_str()) );
	btRefresh = new QPushButton(QString::fromUtf8(string("刷新: ").c_str()) );
	layout->addWidget(lstLine, 0, 0, 1, 2);
/*	layout->addWidget(btSearch, 1, 0, 1, 1);
	layout->addWidget(btRefresh, 1, 1, 1, 1);*/
	setLayout(layout);
	QFont font;
	font.setFamily("Tahoma");
	setFont(font);
	refreshData();

}

void CLineList::refreshData() {
	string pghost = "localhost";
	string pgport = "5432";
	string dbname = "railway";
	string pguser = "postgres";
	string pgpasswd = "198811";

	PGconn *conn;

	conn = PQsetdbLogin(pghost.c_str(), pgport.c_str(), NULL, NULL, dbname.c_str(), pguser.c_str(),
			pgpasswd.c_str());

	if (PQstatus(conn) == CONNECTION_BAD) {
		printf("Connection to database ��%s�� failed.\n", dbname.c_str());
		printf("Message %s", PQerrorMessage(conn));

		PQfinish(conn);
	}
	printf("Success connected!\n");

	string query =
			"SELECT trainline_num, A.station_name ,B.station_name FROM trainline, station A, station B "
				"WHERE train_start = A.station_id and train_end = B.station_id";
	QStandardItemModel *model = new QStandardItemModel(0, 3, this);

	model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8(string("车次").c_str()) );
	model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8(string("发站").c_str()) );
	model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8(string("终到").c_str()) );

	PGresult *res = PQexec(conn, query.c_str());
	for (int i = 0; i < PQntuples(res); i++) {
		QString s1 = QString::fromUtf8(PQgetvalue(res, i, 0));
		QString s2 = QString::fromUtf8(PQgetvalue(res, i, 1));
		QString s3 = QString::fromUtf8(PQgetvalue(res, i, 2));
		model->insertRow(model->rowCount());
		model->setData(model->index(model->rowCount() - 1, 0), s1);
		model->setData(model->index(model->rowCount() - 1, 1), s2);
		model->setData(model->index(model->rowCount() - 1, 2), s3);
	}
	PQclear(res);
	PQfinish(conn);
	lstLine->setModel(model);
	lstLine->setSelectionBehavior(QAbstractItemView::SelectRows);
	lstLine->setEditTriggers(QAbstractItemView::NoEditTriggers);
	lstLine->setSelectionMode(QAbstractItemView::SingleSelection);

	lstLine->setColumnWidth(0, 80);
	lstLine->setColumnWidth(1, 60);
	lstLine->setColumnWidth(2, 60);
}



