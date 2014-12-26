/*
 * Utils.cpp
 *
 *  Created on: 2010-12-28
 *      Author: pkkj
 */

#include "Utils.h"
#include <cstdio>
#include <cstring>
using namespace std;
string Int2Str(int x) {
	char s[100];
	sprintf(s, "%d", x);
	return string(s);
}
string Double2Str(double x) {
	char s[100];
	sprintf(s, "%.4lf", x);
	return string(s);
}
vector<string> SplitString(string str, string token) {
	vector<string> res;
	string tmp = "";
	if (token.length() == 0 || str.length() == 0)
		return res;
	str += token[0];
	for (size_t i = 0, n = str.length(); i < n; i++) {
		char ch = str[i];
		bool match = false;
		for (size_t j = 0, m = token.length(); j < m && !match; j++) {
			if (ch == token[j])
				match = true;
		}
		if (match) {
			res.push_back(tmp);
			tmp = "";
		} else {
			tmp += ch;
		}
	}
	return res;
}

string StrToLower(string str) {
	string res = str;
	for(size_t i = 0;i < res.size();i++){
		if('A' <= res[i] && res[i] <= 'Z')
			res[i] += 'a' - 'A';
	}
	return res;
}
