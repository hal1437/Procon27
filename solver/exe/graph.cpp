
//グラフアルゴリズムテストコード
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/ProblemMaker.h>
#include <structure/Drawer.h>
#include <cmath>
#include <opencv2/opencv.hpp>


int main(){

	std::cout << "---Graph Algorithm Test---" << std::endl;
	

	Problem problem = ProblemMaker::MakeTriangleProblem();
	Polygon polygon;

	std::cout << "三角問題" << std::endl;
	for(Polygon p :problem.pieces){

		cv::Mat img = cv::Mat::zeros(800, 800, CV_8UC3);

		std::cout << p;
		img << p;

		cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("drawing", img);
		cv::waitKey(0);

	}

}
