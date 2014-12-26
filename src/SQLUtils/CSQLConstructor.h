/*
 * CSQLConstructor.h
 *
 *  Created on: 2011-1-8
 *      Author: pkkj
 */

#ifndef CSQLCONSTRUCTOR_H_
#define CSQLCONSTRUCTOR_H_
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace SQLUtils {
class CSQLValueType {
public:
	enum SQL_VALUE_TYPE {
		SQL_STRING, SQL_NUMERIAL, SQL_BOOLEAN
	};
	static string JudgeBool(string value);
};


class CSQLInsertConstructor {
public:
	CSQLInsertConstructor();
	CSQLInsertConstructor(string TableName);
	~CSQLInsertConstructor();
	void InsertValue(string Field, string Value, CSQLValueType::SQL_VALUE_TYPE VType);
	string Construct();
	string ConstructSub();
	string TableName;
private:
	map<string, pair<string, CSQLValueType::SQL_VALUE_TYPE> > mValueTable;

};



class CSQLSelectConstructor {
public:
	CSQLSelectConstructor();
	CSQLSelectConstructor(string TableName);
	~CSQLSelectConstructor();

	string Construct();

public:
	string WhereClause;
	string TableName;
	int searchLimit;
	vector<string> SubField;
};

class CSQLUpdateConstructor {
public:
	CSQLUpdateConstructor(string TableName);
	~CSQLUpdateConstructor();
	string Construct();
	void InsertValue(string Field, string Value, CSQLValueType::SQL_VALUE_TYPE VType);
	string TableName;

private:
	map<string, pair<string, CSQLValueType::SQL_VALUE_TYPE> > mValueTable;

};
}

#endif /* CSQLCONSTRUCTOR_H_ */
