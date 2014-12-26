/*
 * CFeature.h
 *
 *  Created on: 2011-1-7
 *      Author: pkkj
 */

#ifndef CFEATURE_H_
#define CFEATURE_H_
#include "CGlobal.h"
#include "CField.h"
#include "CFields.h"
#include "CGeometryExt.h"
#include <string>
#include <vector>
#include <cstdio>
#include <list>
#include <algorithm>
using namespace std;

namespace DataSource {
class CFeatureClass;
class CPGFeatClass;
class CFeature {
	friend class CPGFeatClass;
public:
	CFeature(CFeatureClass *pFeatClass);
	CFeature(const CFeature &feat);
	~CFeature();
public:
	void SetValue(string fname, string value);

	string GetValue(string fname);
	Core::COpenGISType::OPENGIS_TYPE getGeometryType();

	int GetFID();
	void SetFID(int fid);
	void Add();
	void Delete();
	void Store();
	CFeature *clone();

	size_t FieldCount();
	string GetFieldName(int idx);
	int FindField(string fname);

	void ShowInfo();
	CFeature & operator=(const CFeature & feat);

public:
	Geometry::CGeometryExt *Shape;

private:
	void SetValue(size_t idx, string value);
	string GetValue(size_t idx);
	string GetValueByInnerIdx(size_t idx);

	void AddSubField(string name);
private:
	CFeatureClass *mFeatClass;
	CFields *mFields;
	int FID;
	vector<string> mValue;

	vector<bool> HasValue;
	vector<int> HasValueField;
};


}
#endif /* CFEATURE_H_ */
