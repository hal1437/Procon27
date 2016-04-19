
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include "Point.hpp"
#include "Polygon.h"

//cv::Matに出力
bool DrawPolygon(cv::Mat& src,const Polygon& poly,int thickness = 1 , const cv::Scalar& color = cv::Scalar(255,255,255),bool fill = true){

	for(int i=0; i<poly.size(); i++){
		int j = (i+1)%poly.size();
		cv::Point pos1(poly.getNode(i).x,poly.getNode(i).y);
		cv::Point pos2(poly.getNode(j).x,poly.getNode(j).y);
		cv::line(src,pos1,pos2,color,thickness);
	}
	return true;
}
bool DrawPoint(cv::Mat& src,const Point& pos,int radius = 5 , const cv::Scalar& color = cv::Scalar(255,255,255),bool fill = true){
	circle(src,cv::Point(pos.x, pos.y), 1,color , 1, 8, 0);
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


