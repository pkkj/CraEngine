/*
 * CSQLConstructor.cpp
 *
 *  Created on: 2011-1-8
 *      Author: pkkj
 */

#include <string>
#include <vector>
using namespace std;

#include "CSQLConstructor.h"
#include "Utils.h"
namespace SQLUtils {

string CSQLValueType::JudgeBool(string value) {
	if (value == "")
		return "";
	if (value[0] == 'T' || value[0] == 't')
		return "true";
	return "false";
}
CSQLInsertConstructor::CSQLInsertConstructor() {

}
CSQLInsertConstructor::CSQLInsertConstructor(string TableName) :
	TableName(TableName) {
}
CSQLInsertConstructor::~CSQLInsertConstructor() {

}

void CSQLInsertConstructor::InsertValue(string Field, string Value,
		CSQLValueType::SQL_VALUE_TYPE VType) {
	mValueTable[Field] = make_pair(Value, VType);
}
string CSQLInsertConstructor::Construct() {
	if (TableName == "")
		return "";
	return "INSERT INTO " + TableName + ConstructSub();
}

string CSQLInsertConstructor::ConstructSub() {
	string Ret = " (";
	map<string, pair<string, CSQLValueType::SQL_VALUE_TYPE> >::iterator it;
	for (it = mValueTable.begin(); it != mValueTable.end(); it++) {
		if (it != mValueTable.begin())
			Ret += " , ";
		Ret += it->first;
	}
	Ret += ") VALUES ( ";
	for (it = mValueTable.begin(); it != mValueTable.end(); it++) {
		if (it != mValueTable.begin())
			Ret += " , ";
		pair<string, CSQLValueType::SQL_VALUE_TYPE> item = it->second;
		if (item.second == CSQLValueType::SQL_BOOLEAN) {
			Ret += CSQLValueType::JudgeBool(item.first);
		} else if (item.second == CSQLValueType::SQL_STRING)
			Ret += "'" + item.first + "'";
		else
			Ret += item.first;
	}
	Ret += " )";
	return Ret;
}

CSQLSelectConstructor::CSQLSelectConstructor() {

}
CSQLSelectConstructor::CSQLSelectConstructor(string TableName) :
	TableName(TableName) {
	searchLimit = 0;

}
CSQLSelectConstructor::~CSQLSelectConstructor() {

}

string CSQLSelectConstructor::Construct() {
	string Ret = "SELECT ";
	if (SubField.size() == 0)
		Ret += "*";
	else {
		for (size_t i = 0; i < SubField.size(); i++) {
			if (i)
				Ret += ",";
			Ret += SubField[i];
		}
	}
	Ret += " FROM " + TableName;
	if(WhereClause != "")
		Ret += " WHERE " + WhereClause;
	if(searchLimit > 0)
		Ret += " LIMIT "+Int2Str(searchLimit);
	return Ret;
}

CSQLUpdateConstructor::CSQLUpdateConstructor(string TableName) :
	TableName(TableName) {

}
CSQLUpdateConstructor::~CSQLUpdateConstructor() {
}
string CSQLUpdateConstructor::Construct() {
	string Ret = "UPDATE " + TableName + " SET ";
	map<string, pair<string, CSQLValueType::SQL_VALUE_TYPE> >::iterator it;
	for (it = mValueTable.begin(); it != mValueTable.end(); it++) {
		if (it != mValueTable.begin())
			Ret += " , ";
		Ret += it->first + "=";
		pair<string, CSQLValueType::SQL_VALUE_TYPE> item = it->second;
		if (item.second == CSQLValueType::SQL_BOOLEAN) {
			Ret += CSQLValueType::JudgeBool(item.first);
		} else if (item.second == CSQLValueType::SQL_STRING)
			Ret += "'" + item.first + "'";
		else
			Ret += item.first;
	}
	return Ret;

}
void CSQLUpdateConstructor::InsertValue(string Field, string Value,
		CSQLValueType::SQL_VALUE_TYPE VType) {
	mValueTable[Field] = make_pair(Value, VType);
}

}
