
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
	//+フレーム生成範囲
	//+辺上の頂点の生成数範囲
	//+辺上の頂点の揺らぎ
	//+点の生成密度
	//+枠の幅
	//+枠の高さ
	static Problem MakeTriangleProblem(const Range<int> edge_div_range = Range<int>(6,4),
									   const int        edge_div_round = 10,
									   const int        density        = 80,
									   const int        frame_width    = 400,
									   const int        frame_height   = 400);
};
