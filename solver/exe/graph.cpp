
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
	Polygon pp;
	pp.addNode(Point(0  , 0));
	pp.addNode(Point(50 , 0));
	pp.addNode(Point(100,50));
	pp.addNode(Point(150, 0));
	pp.addNode(Point(200, 0));
	pp.addNode(Point(200,100));
	pp.addNode(Point(0  ,100));
	std::cout << pp.isComprehension(Point(170,-1)) << std::endl;
	return 0;

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
