
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

int main(){
	
	cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);

	// Red，太さ3，4近傍連結
	cv::line(img, cv::Point(100, 100), cv::Point(400, 105), cv::Scalar(0,0,200), 3, 4);  
	// Green，太さ5，8近傍連結
	cv::line(img, cv::Point(100, 200), cv::Point(400, 205), cv::Scalar(0,200,0), 5, 8);
	// Blue，太さ10，アンチエイリアス
	cv::line(img, cv::Point(100, 300), cv::Point(400, 305), cv::Scalar(200,0,0), 10, CV_AA);

	cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::imshow("drawing", img);
	cv::waitKey(0);
}
