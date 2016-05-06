
//グラフアルゴリズムテストコード
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/ProblemMaker.h>
#include <cmath>

int main(){

	std::cout << "---Graph Algorithm Test---" << std::endl;
	

	Problem problem = ProblemMaker::MakeTriangleProblem();
	Polygon polygon;

	std::cout << "三角問題" << std::endl;
	for(Polygon p :problem.pieces){
		std::cout << p;
	}
	

}
