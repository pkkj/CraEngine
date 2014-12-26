/*
 * CQueryFilter.h
 *
 *  Created on: 2011-1-9
 *      Author: pkkj
 */

#ifndef CQUERYFILTER_H_
#define CQUERYFILTER_H_

#include <string>
#include <set>
#include <vector>
using namespace std;
namespace DataSource
{
class CQueryFilter
{
public:
	CQueryFilter();
	~CQueryFilter();

public:
	string WhereClause;
	int searchLimit;
	bool FetchGeometry;
public:
	void SetSubField(string SubField);
	void AddSubField(string SubField);
	vector<string> GetAllSubField();

	virtual string FilterType();
protected:
	set<string> mSubField;
};

}

#endif /* CQUERYFILTER_H_ */
