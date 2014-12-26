/*
 * CFeatureCursor.cpp
 *
 *  Created on: 2011-1-7
 *      Author: pkkj
 */

#include "CFeatureCursor.h"
#include "CFeatureClass.h"
namespace DataSource {
long long CFeatureCursor::AutoCursorID = 0;

CFeatureCursor::CFeatureCursor() {
	QueueLimit = 1000;
	mFetched = 0;
}

void CFeatureCursor::SetCursorID() {
	CursorID = AutoCursorID++;
}

bool CFeatureCursor::NextFeature(CFeature &feat) {
	if (mFeatureQueue.empty()) {
		if (!mFeatClass->getFeature(this, QueueLimit))
			return false;
	}
	feat = mFeatureQueue.front();
	mFeatureQueue.pop();
	return true;
}
}
