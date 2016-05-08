
#include <iostream>
#include <structure/Matrix.hpp>
#include <random>

int main(){
	std::random_device rd;
	Matrix<10,10> mat;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			mat(i,j) = rd();

	std::cout << mat;

}
