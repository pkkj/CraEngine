/*
 * CTrainlineInfo.h
 *
 *  Created on: 2011-2-9
 *      Author: pkkj
 */

#ifndef CTRAINLINEINFO_H_
#define CTRAINLINEINFO_H_
#include <libpq-fe.h>
#include <string>
#include <vector>
using namespace std;
struct CTrainStop {
	string station;
	string arriveTime;
	string departTime;
	CTrainStop() {
	}
	CTrainStop(string station, string arriveTime, string departTime) :
		station(station), arriveTime(arriveTime), departTime(departTime) {
	}
};
class CTrainlineInfo {
public:
	vector<CTrainStop> stopList;
	void getTrainLine(string trainNum);
};

#endif /* CTRAINLINEINFO_H_ */
