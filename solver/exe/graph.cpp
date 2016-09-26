
//グラフアルゴリズムテストコード
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/Matrix.hpp>
#include <structure/ProblemMaker.h>
#include <structure/Drawer.h>
#include <cmath>
#include <opencv2/opencv.hpp>


int main(){

	std::cout << "---Graph Algorithm Test---" << std::endl;
	

	Problem problem = ProblemMaker::MakeTriangleProblem(Range<int>(1,1),10,200);
	double area = 0;
	for(int i=0;i<problem.pieces.size();i++){
		area += problem.pieces[i].getArea();
	}
	std::cout << area << std::endl;

	std::cout << "三角問題" << std::endl;
	cv::Mat img = cv::Mat::zeros(600, 600, CV_8UC3);
	for(Polygon p :problem.pieces){

		std::cout << p;
		img << p /** cMat::MakeRotateMatrix(M_PI/4) */* cMat::MakeMoveMatrix(100,100);

		cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("drawing", img);
		cv::waitKey(0);

	}

}
