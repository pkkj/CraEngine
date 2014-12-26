/*
 * CQueryFilter.cpp
 *
 *  Created on: 2011-1-9
 *      Author: pkkj
 */

#include "CQueryFilter.h"
#include "Utils.h"
namespace DataSource {

CQueryFilter::CQueryFilter(){
	FetchGeometry = true;
	searchLimit = 0;
}
CQueryFilter::~CQueryFilter(){

}
void CQueryFilter::SetSubField(string SubField) {
	vector<string> fields = SplitString(SubField, ";");
	mSubField.clear();
	for (size_t i = 0; i < fields.size(); i++)
		mSubField.insert(fields[i]);
}
void CQueryFilter::AddSubField(string SubField) {
	vector<string> fields = SplitString(SubField, ";");
	for (size_t i = 0; i < fields.size(); i++)
		mSubField.insert(fields[i]);
}
vector<string> CQueryFilter::GetAllSubField() {
	vector<string> Ret;
	for (set<string>::iterator it = mSubField.begin(); it != mSubField.end(); it++)
		Ret.push_back(*it);
	return Ret;

}

string CQueryFilter::FilterType()
{
	return "CQueryFilter";
}
}
