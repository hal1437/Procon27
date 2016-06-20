
#pragma once
#include <structure/Problem.h>
#include <structure/Range.h>
#include <util/ClockWiseFor.h>
#include <random>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <tuple>

class ProblemMaker{
private:
	static bool isCrossing(const Point& p11,const Point& p12,const Point& p21,const Point& p22);
public:
	//等面積問題作成
	static Problem MakeEqualAreaProblem();
	
	//三角問題作成
	static Problem MakeTriangleProblem();
};
