
#pragma once 

#include <vector>
#include <list>
#include <limits>
#include <deque>
#include <search/BasicSearch.h>
#include <search/Heuristic.hpp>

//サスペンド
class SuspendSearch:public BasicSearch{
private:
	//だいたいリミテッドのパクリ
	const int WIDTH_LIMIT = 1;//探索幅
	const int RECORD_LIMIT = 1000;

	std::vector<Heuristic<Polygon>*> heuristic;

private:
	double GetHeuristic(const Polygon& poly)const;

public:

	//評価関数追加
	void AddHeuristic(Heuristic<Polygon>* h);

	//探索
	virtual Answer Search(const Problem& prob);

};


