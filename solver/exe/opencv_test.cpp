
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/Drawer.h>
#include <opencv2/opencv.hpp>
#include <util/BinaryIO.hpp>
#include <random>


int main(){
	

	Point p[5];
	std::random_device rd;
// 	p[0] = Point(rd()%300,rd()%300);
	p[0] = Point(400,400);

	double cc = 0;
	while (1){
		cv::Mat img = cv::Mat::zeros(800, 800, CV_8UC3);
		Polygon polygon;

		p[1].x = 200*sin(cc) + p[0].x;
		p[1].y = 200*cos(cc) + p[0].y;
		p[2].x = 100*sin(cc*3) + p[1].x;
		p[2].y = 100*cos(cc*3) + p[1].y;
		p[3].x = 50 *sin(cc*5) + p[2].x;
		p[3].y = 50 *cos(cc*5) + p[2].y;
		p[4].x = 30 *sin(cc*10) + p[3].x;
		p[4].y = 30 *cos(cc*10) + p[3].y;
		
		for(int i=0;i<5;i++){
			polygon.addNode(p[i]);
		}	
		std::cout << polygon << std::endl;
		img << polygon;
		for(int i=0;i<5;i++){
			DrawPoint(img,p[i],5,cv::Scalar(0,0,255),3);
		}
		cc += 2*3.141592/200;


		cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("drawing", img);
		cv::waitKey(1);
	}
}
