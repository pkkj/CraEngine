/*
 * Utils.h
 *
 *  Created on: 2010-12-28
 *      Author: pkkj
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <vector>
#include <string>
using namespace std;
string Int2Str(int x);
string Double2Str(double x);
vector<string> SplitString(string str, string token);
string StrToLower(string str);
#endif /* UTILS_H_ */
