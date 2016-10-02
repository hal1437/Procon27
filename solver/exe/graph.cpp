
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

    af::info();
	std::cout << "---Graph Algorithm Test---" << std::endl;
	

	Problem problem = ProblemMaker::MakeTriangleProblem();

	std::cout << "三角問題" << std::endl;
	for(Polygon p :problem.pieces){
		cv::Mat img = cv::Mat::zeros(600, 600, CV_8UC3);

		std::cout << p;
		img << p * /*cMat::MakeRotateMatrix(M_PI/4) **/ cMat::MakeMoveMatrix(100,200);
		p.normalize();
		std::cout << p;
		img << p * /*cMat::MakeRotateMatrix(M_PI/4) **/ cMat::MakeMoveMatrix(200,100);

		cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("drawing", img);
		cv::waitKey(0);

	}

}
