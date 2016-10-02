
#pragma once
#include <search/Heuristic.hpp>
#include <structure/Polygon.h>

//角度評価関数
class NarrowHeuristic : public Heuristic<Polygon>{
public:

	virtual double operator()(const Polygon& obj)const;

};
