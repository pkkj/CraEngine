/*
 * CFeature.cpp
 *
 *  Created on: 2011-1-7
 *      Author: pkkj
 */

#include "CFeature.h"
#include "CFeatureClass.h"
#include "CPoint.h"
#include "CLineString.h"
#include "CPolygon.h"
#include "CMultiPoint.h"
#include "CMultiLineString.h"
#include "CMultiPolygon.h"
#include "CLine.h"
#include "Utils.h"
namespace DataSource {

CFeature::CFeature(CFeatureClass *mFeatClass) :
	mFeatClass(mFeatClass), mFields(&(mFeatClass->Fields)) {
	mValue.resize(mFields->FieldCount());
	HasValue = vector<bool> (mFields->FieldCount(), false);
	Shape = NULL;
}

CFeature::CFeature(const CFeature &feat) {
	mFeatClass = feat.mFeatClass;
	mValue = feat.mValue;
	FID = feat.FID;
	mFields = feat.mFields;
	HasValue = feat.HasValue;
	HasValueField = feat.HasValueField;
	if (feat.Shape)
		Shape = feat.Shape->clone();
	else
		Shape = NULL;
}

CFeature::~CFeature() {
	delete Shape;
}

void CFeature::Add() {
	mFeatClass->addFeature(this);
}
void CFeature::Delete() {
	mFeatClass->deleteFeature(FID);
}
void CFeature::Store() {
	mFeatClass->updateFeature(this);
}

int CFeature::FindField(string fname) {
	return mFields->FindField(fname);
}

void CFeature::SetValue(string fname, string value) {
	int idx = FindField(fname);
	if (idx == -1)
		return;
	SetValue(idx, value);
}
void CFeature::SetValue(size_t idx, string value) {
	if (!HasValue[idx]) {
		HasValue[idx] = true;
		HasValueField.push_back(idx);
	}
	mValue[idx] = value;
}

string CFeature::GetValue(string fname) {
	if(StrToLower(fname) == "fid")
		return Int2Str(FID);
	int idx = FindField(fname);
	if (idx == -1)
		return "";
	return GetValue(idx);
}
string CFeature::GetValue(size_t idx) {
	return mValue[idx];
}

CFeature *CFeature::clone() {
	return new CFeature(*this);
}

void CFeature::ShowInfo() {
	sort(HasValueField.begin(), HasValueField.end());
	printf("=======================\n");
	printf("Feature ID %d\n", FID);
	for (size_t i = 0; i < HasValueField.size(); i++) {
		printf("Field: %s  Value: %s\n", mFields->GetField(HasValueField[i]).Name.c_str(),
				mValue[HasValueField[i]].c_str());
	}
	printf("FINISH --------------\n");
}

size_t CFeature::FieldCount() {
	return mFields->FieldCount();
}
string CFeature::GetFieldName(int idx) {
	return mFields->GetField(idx).Name;
}

int CFeature::GetFID() {
	return FID;

}
void CFeature::SetFID(int fid) {
	FID = fid;

}
string CFeature::GetValueByInnerIdx(size_t idx) {
	return mValue[HasValueField[idx]];
}

CFeature &CFeature::operator=(const CFeature & feat) {
	mFeatClass = feat.mFeatClass;
	mValue = feat.mValue;
	FID = feat.FID;
	mFields = feat.mFields;
	HasValue = feat.HasValue;
	HasValueField = feat.HasValueField;
	if (feat.Shape)
		Shape = feat.Shape->clone();
	else
		Shape = NULL;
	return *this;
}

Core::COpenGISType::OPENGIS_TYPE CFeature::getGeometryType() {
	if (Shape->getGeometryPtr() != NULL) {
		return Shape->getGeometryPtr()->getOGISType();
	}
	if (Shape->getEwkbStr() != NULL) {
		const unsigned char *buf = Shape->getEwkbStr();
		buf++;
		byte geotype = *(byte *)buf;
		WkbGeometryType wkbtype =(WkbGeometryType)geotype;
		return COpenGISType::GetTypeByWkbType(wkbtype);
	}
	return COpenGISType::OGIS_UNKNOWN;
}
}
