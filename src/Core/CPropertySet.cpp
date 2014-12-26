/*
 * CPropertySet.cpp
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#include "CPropertySet.h"

namespace Core {

CPropertySet::CPropertySet() {
}
CPropertySet::~CPropertySet() {
}
void CPropertySet::setProperty(string name, string value) {
	mProMap[name] = value;
}
void CPropertySet::remoreProperty(string name) {
	map<string, string>::iterator it = mProMap.find(name);
	if (it != mProMap.end()) {
		mProMap.erase(it);
	}
}
string CPropertySet::getValue(string name) {
	map<string, string>::iterator it = mProMap.find(name);
	if (it != mProMap.end()) {
		return it->second;
	}
	return "";
}
void CPropertySet::clear() {
	mProMap.clear();
}
}
