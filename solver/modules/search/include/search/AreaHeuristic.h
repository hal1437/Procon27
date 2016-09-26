
#pragma once
#include <search/Heuristic.hpp>
#include <structure/Polygon.h>

//面積評価関数
class AreaHeuristic : public Heuristic<Polygon>{
public:

	virtual double operator()(const Polygon& obj)const;

};
