
#pragma once
#include <search/Heuristic.hpp>
#include <structure/Polygon.h>

//距離評価関数
class WeightComposite : public Heuristic<Polygon>{

	std::vector<std::pair<Heuristic<Polygon>* ,double>> hs;
public:
	
	void AddHeuristic(Heuristic<Polygon>* h,double rate);

	virtual double operator()(const Polygon& obj)const;

	~WeightComposite();
};
