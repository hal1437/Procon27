
#include <iostream>
#include <structure/Matrix.hpp>
#include <random>

int main(){
	std::random_device rd;
	Matrix<10,10> mat1;
	Matrix<10,10> mat2;
	
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			mat1(i,j) = rd()%10;
			mat2(j,i) = rd()%10;
		}
	}

	
	std::cout << "mat1 = \n" << mat1 << std::endl;
	std::cout << "mat2 = \n" << mat2 << std::endl;
	std::cout << "mat1 + mat2 = \n" << mat1+mat2 << std::endl;
	std::cout << "mat1 - mat2 = \n" << mat1-mat2 << std::endl;
	std::cout << "mat1 * mat2 = \n" << mat1*mat2 << std::endl;

}
