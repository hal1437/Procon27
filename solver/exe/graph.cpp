
//グラフアルゴリズムテストコード
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <cmath>

int main(){
	std::cout << "---Graph Algorithm Test---" << std::endl;
	
	Point p1(10,20);
	Point p2(20,20);
	Point p3(20,10);
	Point p4(10,10);
	Polygon polygon;

	polygon.addNode(p1);
	polygon.addNode(p2);
	polygon.addNode(p3);
	polygon.addNode(p4);

	for(int i=0;i<4;i++){
		std::cout << polygon.getNode(i) << std::endl;
	}

}
