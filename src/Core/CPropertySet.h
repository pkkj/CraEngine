/*
 * CPropertySet.h
 *
 *  Created on: 2011-1-28
 *      Author: pkkj
 */

#ifndef CPROPERTYSET_H_
#define CPROPERTYSET_H_

#include <string>
#include <map>
using namespace std;
namespace Core {
class CPropertySet {
public:
	CPropertySet();
	~CPropertySet();
	void setProperty(string name, string value);
	void remoreProperty(string name);
	string getValue(string name);
	void clear();
private:
	map<string, string> mProMap;
};

}

#endif /* CPROPERTYSET_H_ */
