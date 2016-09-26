

#include <structure/Algorithm.h>

bool isCrossed(Point p1,Point p2,Point p3,Point p4){
	bool ans = false;
	if(((p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x)) *
	   ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0){
		if(((p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x)) *
		   ((p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x)) < 0){
			ans = true;
		}
	}
	return ans;
}


