/*
 * CPGCommon.h
 *
 *  Created on: 2010-12-27
 *      Author: pkkj
 */

#ifndef CPGCOMMON_H_
#define CPGCOMMON_H_
#include <libpq-fe.h>
namespace DataSource{


class CPostgreException {
public:
	CPostgreException(PGresult *res) :
		res(res) {
	}
	~CPostgreException() {
		if (res)
			PQclear(res);
	}

	void ShowMessage() {
		printf("ERROR %s\n", PQresultErrorMessage(res));
	}
private:
	PGresult *res;
};
}
#endif /* CPGCOMMON_H_ */
