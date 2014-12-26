/*
 * CTrainlineInfo.cpp
 *
 *  Created on: 2011-2-9
 *      Author: pkkj
 */

#include "CTrainlineInfo.h"
string quostr(string s) {
	return "'" + s + "'";
}
void CTrainlineInfo::getTrainLine(string trainNum) {
	string pghost, pgport, pgoptions, pgtty, dbname, pguser, pgpasswd;
	pghost = "localhost";
	pgport = "5432";
	dbname = "railway";
	pguser = "postgres";
	pgpasswd = "198811";

	PGconn *conn;

	conn = PQsetdbLogin(pghost.c_str(), pgport.c_str(), pgoptions.c_str(), pgtty.c_str(),
			dbname.c_str(), pguser.c_str(), pgpasswd.c_str());

	if (PQstatus(conn) == CONNECTION_BAD) {
		printf("Connection to database %s failed.\n", dbname.c_str());
		printf("Message %s", PQerrorMessage(conn));

		PQfinish(conn);
	}
	printf("Success connected!\n");

	string
			query =
					"select station_name, arrive_time, depart_time from station, trainline, routine "
						"where trainline_num = " + quostr(trainNum)
							+ " and trainline_id = routine_train_id and routine_station_id = station_id order by routine_order asc";
	PGresult *res = PQexec(conn, query.c_str());
	for (int i = 0; i < PQntuples(res); i++) {
		string s1 = string(PQgetvalue(res, i, 0));
		string s2 = string(PQgetvalue(res, i, 1));
		string s3 = string(PQgetvalue(res, i, 2));
		stopList.push_back(CTrainStop(s1, s2, s3));
	}
	PQclear(res);
	PQfinish(conn);
}
