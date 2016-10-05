
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/Drawer.h>
#include <opencv2/opencv.hpp>
#include <util/BinaryIO.hpp>
#include <random>
#include <capture/MatIO.h>


int main(){
	
	Point p[5];
	std::random_device rd;
// 	p[0] = Point(rd()%300,rd()%300);
	p[0] = Point(400,400);

	double cc = 0;
	while (1){
		cv::Mat img = cv::Mat::zeros(800, 800, CV_8UC3);
		cv::Vec3b pixcel;
		
		for(int i=0; i<400; i++){
			for(int j=0; j<400; j++){
				SetPixcel(img, j, i, 0, 0, 255);
			}
		}

		pixcel = GetPixcel(img, 100, 100);
		
		std::cout << (int)pixcel[0] << ", " << (int)pixcel[1] << ", " << (int)pixcel[2] << std::endl;
		std::cout << ColorDistance(GetPixcel(img, 10, 10), GetPixcel(img, 700, 700)) << std::endl;


		cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("drawing", img);
		cv::waitKey(1);
	}
}
