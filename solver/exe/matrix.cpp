
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Matrix.hpp>
#include <random>

int main(){
	std::random_device rd;
	vMat pos = vMat::ConvertMatrix(Point(1,0));
	Matrix<3,3> c_mat;
	
	Point v1(0, 1);
	Point v2(0,-1);

	std::cout << Point::getAngle2Vec(v1,v2) << std::endl;

}
