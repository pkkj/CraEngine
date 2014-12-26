/*
 * CFeatureCursor.h
 *
 *  Created on: 2011-1-7
 *      Author: pkkj
 */

#ifndef CFEATURECURSOR_H_
#define CFEATURECURSOR_H_
#include <string>
#include <vector>
#include <queue>
using namespace std;

#include "CFeature.h"

namespace DataSource {
class CFeatureClass;
class CFeatureCursor {
	friend class CPGFeatClass;
public:
	enum CURSOR_STATUS {
		OPEN, CLOSE
	};
public:
	static long long AutoCursorID;
public:
	string CursorName;
	CURSOR_STATUS Status;
	int CursorID;
	int QueueLimit;
public:
	CFeatureCursor();
	bool NextFeature(CFeature &feat);
private:
	CFeatureClass *mFeatClass;
	// Record the mapping, from the subfield in the cursor to the real ID in CField
	vector<int> mSubFieldMap;
	bool FetchGeometry;
	int mFetched;
	void SetCursorID();
	queue<CFeature> mFeatureQueue;



};
}
#endif /* CFEATURECURSOR_H_ */
