#include "MatIO.h"

cv::Vec3b GetPixcel(cv::Mat img, int x, int y){
	return img.at<cv::Vec3b>(x, y);
}

void SetPixcel(cv::Mat img,int x, int y, int r, int g, int b){
	img.at<cv::Vec3b>(x, y)[0] = b; //Blue
	img.at<cv::Vec3b>(x, y)[1] = g; //Green
	img.at<cv::Vec3b>(x, y)[2] = r; //Red
}
