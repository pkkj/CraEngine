/*
 * CFeatureClass.cpp
 *
 *  Created on: 2011-1-7
 *      Author: pkkj
 */

#include "CFeatureClass.h"

namespace DataSource {

CFeatureClass::CFeatureClass() {

}

CFeatureClass::~CFeatureClass() {

}
string CFeatureClass::SQLInsertString(string str) {
	return "'" + str + "'";
}

int CFeatureClass::FieldCount() {
	return Fields.FieldCount();
}

bool CFeatureClass::deleteFeature(vector<int> featID) {
	for (size_t i = 0; i < featID.size(); i++)
		if (!deleteFeature(featID[i]))
			return false;
	return true;
}
bool CFeatureClass::updateFeature(vector<CFeature *> featID) {
	for (size_t i = 0; i < featID.size(); i++)
		if (!updateFeature(featID[i]))
			return false;
	return true;
}

bool CFeatureClass::deleteField(string name) {
	int idx = Fields.FindField(name);
	if (idx == -1)
		return false;
	return deleteField(idx);
}

Core::COpenGISType::OPENGIS_TYPE CFeatureClass::GetShapeType() {
	return GeometryType;
}
bool CFeatureClass::GetHasM() {
	return HasM;
}
bool CFeatureClass::GetHasZ() {
	return HasZ;
}
}
