/*
 * maths.h
 *
 *  Created on: 2010-12-20
 *      Author: pkkj
 */

#ifndef MATHS_H_
#define MATHS_H_
#include <limits>
#include <cmath>
using namespace std;
#define DOUBLE_NAN numeric_limits<double>::quiet_NaN()
#define ISNAN(x) ( isnan(x) )

namespace General {

inline double sqr(double x) {
	return x * x;
}

inline int double_cmp(double x, double eps) {
	return x < -eps ? -1 : x > eps;
}
}

#endif /* MATHS_H_ */
