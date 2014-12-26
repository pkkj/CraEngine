/*
 * CField.h
 *
 *  Created on: 2010-12-27
 *      Author: pkkj
 */

#ifndef CFIELD_H_
#define CFIELD_H_

#include <string>
using namespace std;
namespace DataSource {
enum FIELD_TYPE {
	FTYPE_SMALLINT,
	FTYPE_INTEGER,
	FTYPE_BIGINT,
	FTYPE_REAL,
	FTYPE_DOUBLE,
	FTYPE_NUMERIC,
	FTYPE_VARCHAR,
	FTYPE_BINARY,
	FTYPE_BOOLEAN,
	FTYPE_DATATIME,
	FTYPE_GEOMETRY,
	FTYPE_UNKNOWN
};
class CField {

public:

	static string getTypeName(FIELD_TYPE type);
public:
	CField();

public:
	string Name;
	FIELD_TYPE Type;
	int Precision;
	int Length;
	int Num;
	string Comment;
	bool NotNull;
	string DefaultValue;
	bool AutoInc;

public:
	void ShowInfo();
	void SetDefualt(string value);
	bool CheckHasDefault();
	string GetDefault();
private:

};

}

#endif /* CFIELDS_H_ */
