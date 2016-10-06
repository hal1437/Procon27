#include <capture/MatIO.h>
#include <cmath>

cv::Vec3b GetPixcel(cv::Mat img, int x, int y){
	return img.at<cv::Vec3b>(x, y);
}

void SetPixcel(cv::Mat img,int x, int y, int r, int g, int b){
	img.at<cv::Vec3b>(x, y)[0] = b; //Blue
	img.at<cv::Vec3b>(x, y)[1] = g; //Green
	img.at<cv::Vec3b>(x, y)[2] = r; //Red
}

double ColorDistance(cv::Vec3b p1, cv::Vec3b p2){
	return sqrt(pow(p2[0]-p1[0], 2) + pow(p2[1]-p1[1], 2) + pow(p2[2]-p1[2], 2));
}

void my_mouse_callback(int event, int x, int y, int flags, void* param){
   cv::Point *point = static_cast<cv::Point*>(param);

   if(event == cv::EVENT_LBUTTONDOWN){
   		point->x=x;
		point->y=y;
   	}
        
     
    
}