
#pragma once 
#define _USE_MATH_DEFINES
#include <cmath>

#define NEARY_EQUAL(x,y,eps) (std::abs(x-y) < eps)
#define NE(x,y) NEARY_EQUAL(x,y,0.000000001)

