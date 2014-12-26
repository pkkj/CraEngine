/*
 * CField.cpp
 *
 *  Created on: 2010-12-27
 *      Author: pkkj
 */

#include "CField.h"
#include <cstdio>
namespace DataSource {
string CField::getTypeName(FIELD_TYPE type) {
	switch (type) {
	case FTYPE_SMALLINT:
		return "FTYPE_SMALLINT";
	case FTYPE_INTEGER:
		return "FTYPE_INTEGER";
	case FTYPE_BIGINT:
		return "FTYPE_BIGINT";
	case FTYPE_REAL:
		return "FTYPE_REAL";
	case FTYPE_DOUBLE:
		return "FTYPE_DOUBLE";
	case FTYPE_VARCHAR:
		return "FTYPE_VARCHAR";
	case FTYPE_BINARY:
		return "FTYPE_BINARY";
	case FTYPE_BOOLEAN:
		return "FTYPE_BOOLEAN";
	case FTYPE_DATATIME:
		return "FTYPE_DATATIME";
	case FTYPE_GEOMETRY:
		return "FTYPE_GEOMETRY";
	case FTYPE_NUMERIC:
		return "FTYPE_NUMERIC";
	default:
		return "Unknown";
	}
	return "Unknown";
}
CField::CField() {
	NotNull = false;
	AutoInc = false;
	DefaultValue = "";
	Precision = 0;
}

void CField::ShowInfo() {

	printf("name %s\n", Name.c_str());
	printf("Num %d\n", Num);
	printf("type %s\n", getTypeName(Type).c_str());
	printf("Length %d Precision %d\n", Length, Precision);
	printf("NotNull %d AutoInc %d\n", NotNull, AutoInc);
	printf("DEFUALT VALUE: %s\n", DefaultValue.c_str());
	printf("-----\n");

}

}
