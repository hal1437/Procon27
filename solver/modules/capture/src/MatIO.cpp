#include <capture/MatIO.h>
#include <cmath>

cv::Vec3b GetPixcel(cv::Mat img, int x, int y){
	return img.at<cv::Vec3b>(y, x);
}
cv::Vec3b GetPixcel(cv::Mat img,cv::Point p){
	return img.at<cv::Vec3b>(p.y, p.x);
}

void SetPixcel(cv::Mat img,int x, int y, int r, int g, int b){
	img.at<cv::Vec3b>(y, x)[0] = b; //Blue
	img.at<cv::Vec3b>(y, x)[1] = g; //Green
	img.at<cv::Vec3b>(y, x)[2] = r; //Red
}
void SetPixcel(cv::Mat img,int x, int y, int w){
	img.at<unsigned char>(y, x) = w;
}

double ColorDistance(cv::Vec3b p1, cv::Vec3b p2){
	return sqrt(pow(p2[0]-p1[0], 2) + pow(p2[1]-p1[1], 2) + pow(p2[2]-p1[2], 2));
}

