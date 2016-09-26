
#include <search/WeightComposite.h>


void WeightComposite::AddHeuristic(Heuristic<Polygon>* h,double rate){
	hs.push_back(std::make_pair(h,rate));
}

double WeightComposite::operator()(const Polygon& obj)const{
	double score=0;
	for(std::pair<Heuristic<Polygon>*,double> h:hs){
		score += (*h.first)(obj) * h.second;
	}
	return score;
}

WeightComposite::~WeightComposite(){
	for(std::pair<Heuristic<Polygon>*,double> h:hs){
		delete h.first;
	}
}
