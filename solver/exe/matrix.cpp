
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Matrix.hpp>
#include <structure/Algorithm.h>
#include <random>

int main(){
	std::random_device rd;
	vMat pos = vMat::ConvertMatrix(Point(1,0));
	Matrix<3,3> c_mat;
	
	Point v1(1, 1);
	Point v2(-1, -1);
	Point v3( 1,-1);
	Point v4( 0,0);
	
	std::cout << isCrossed(v1,v2,v3,v4) << std::endl;

	std::cout << Point::getAngle2Vec(v1,v2) << std::endl;

}
