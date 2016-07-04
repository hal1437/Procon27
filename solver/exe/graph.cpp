
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
	

	Problem problem = ProblemMaker::MakeTriangleProblem();
	Polygon polygon;

	std::cout << "三角問題" << std::endl;
		cv::Mat img = cv::Mat::zeros(600, 600, CV_8UC3);
	for(Polygon p :problem.pieces){


		std::cout << p;
		img << p * cMat::MakeRotateMatrix(M_PI/4) * cMat::MakeMoveMatrix(0,0);

		cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("drawing", img);
		cv::waitKey(0);

	}

}
