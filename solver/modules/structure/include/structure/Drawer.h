
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include "Point.hpp"
#include "Polygon.h"

//cv::Matに出力
bool DrawPolygon(cv::Mat& src,const Polygon& poly,int thickness = 1 , const cv::Scalar& color = cv::Scalar(255,255,255),bool fill = true){

	cv::Point* pos = new cv::Point[poly.size()];
	cv::Point** poss = &pos;
	for(int i=0; i<poly.size(); i++){
		pos[i] = cv::Point(poly.getNode(i).x,poly.getNode(i).y);
		std::cout << pos[i].x << "," << pos[i].y << std::endl;
	}
	
	cv::fillConvexPoly(src,pos,poly.size(),color);
	delete[] pos;
	return true;
}
bool DrawPoint(cv::Mat& src,const Point& pos,int radius = 3 , const cv::Scalar& color = cv::Scalar(255,255,255),int thickness = 1 ,bool fill = true){
	cv::circle(src,cv::Point(pos.x, pos.y), radius,color , thickness, 8, 0);
	return true;
}


//<<演算子出力
cv::Mat& operator<<(cv::Mat& src,const Polygon& poly){
	DrawPolygon(src,poly);
	return src;
}
cv::Mat& operator<<(cv::Mat& src,const Point& pos){
	DrawPoint(src,pos);
	return src;
}

