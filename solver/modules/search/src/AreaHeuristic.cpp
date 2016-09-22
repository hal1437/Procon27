
#include <search/AreaHeuristic.h>

double AreaHeuristic::operator()(const Polygon& obj)const{
	return obj.getArea();
}
