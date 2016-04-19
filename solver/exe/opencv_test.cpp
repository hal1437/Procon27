
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/Drawer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <random>


int main(){
	
	cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);

	std::random_device rd;

	Point p1(10,20);
	Point p2(rd()%300,rd()%300);
	Point p3(rd()%300,rd()%300);
	Point p4(rd()%300,rd()%300);
	Polygon polygon;

	polygon.addNode(p1);
	polygon.addNode(p2);
	polygon.addNode(p3);
	polygon.addNode(p4);


	std::cout << polygon << std::endl;
	img << polygon;

	cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::imshow("drawing", img);
	cv::waitKey(0);
}
