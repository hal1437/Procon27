
#include <search/AreaHeuristic.h>

double AreaHeuristic::operator()(const Polygon& obj)const{
	double score=0;
	//全ての点間距離の総和
	for(int i=0;i<obj.size();i++){
		int i_ = (i+1) % obj.size();
		score = (obj.getNode(i).x - obj.getNode(i_).x) * 
		        (obj.getNode(i).y + obj.getNode(i_).y);
	}
	return score/2.0;
}
