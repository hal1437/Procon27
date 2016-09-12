
#pragma once
#include <search/Heuristic.hpp>
#include <structure/Polygon.h>

//距離評価関数
class LengthHeuristic : public Heuristic<Polygon>{
public:

	virtual double operator()(const Polygon& obj)const;

};
