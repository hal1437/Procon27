
#include <search/NarrowHeuristic.h>

double NarrowHeuristic::operator()(const Polygon& obj)const{
	double score = 0;
	for(int i=0;i<obj.size();i++){
		Point p1 = obj.getNode((i + 1)              % obj.size()) - obj.getNode(i);
		Point p2 = obj.getNode((i + obj.size() - 1) % obj.size()) - obj.getNode(i);

		double angle = Point::getAngle2Vec(p1,p2);
		if(angle < M_PI/2){
			score += (M_PI/2 - angle)*180/M_PI;
		}
	}
	return score;
}

