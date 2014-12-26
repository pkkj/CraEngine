/*
 * CFields.h
 *
 *  Created on: 2010-12-27
 *      Author: pkkj
 */

#ifndef CFIELDS_H_
#define CFIELDS_H_

#include <map>
#include <string>
#include <vector>
using namespace std;
#include "CField.h"

namespace DataSource {

class CFields {
public:
	friend class CPGFeatClass;

	int FindField(string FName);
	size_t FieldCount();
	CField& GetField(int idx);
	bool hasGeometry;
private:
	map<string, size_t> mMapFieldID;
	vector<CField> mFields;
	CField mGeoField;
	CField mPriField;

	// we can get the actually position where a normal field locates in mFields
	vector<int> normalFID;

};
}

#endif /* CFIELDS_H_ */
