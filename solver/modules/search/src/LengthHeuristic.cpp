
#include <search/LengthHeuristic.h>

double LengthHeuristic::operator()(const Polygon& obj)const{
	double score=0;
	//全ての点間距離の総和
	for(int i=0;i<obj.size();i++){
		int i_ = (i+1) % obj.size();
		score = std::sqrt(std::pow(obj.getNode(i).x - obj.getNode(i_).x,2) + 
		                  std::pow(obj.getNode(i).y - obj.getNode(i_).y,2));
	}
	return score;
}
