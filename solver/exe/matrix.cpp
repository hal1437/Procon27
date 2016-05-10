
#include <iostream>
#include <structure/Matrix.hpp>
#include <random>

int main(){
	std::random_device rd;
	vMat pos = vMat::ConvertMatrix(Point(1,0));
	Matrix<3,3> c_mat;
	
	c_mat = cMat::MakeRotateMatrix(3.141592/100);
	
	for(int i=0;i<100;i++){
		std::cout << "separator:" << i ;
		std::cout << ":mat =" << pos << std::endl;
		pos = pos * c_mat;
	}
}
