
#ifdef FIND_OPENCV
#include "Drawer.h"

//cv::Matに出力
bool DrawPolygon(cv::Mat& src,const Polygon& poly,int thickness , const cv::Scalar& color,bool fill){

	cv::Point* pos = new cv::Point[poly.size()];
	cv::Point** poss = &pos;
	for(int i=0; i<poly.size(); i++){
		pos[i] = cv::Point(poly.getNode(i).x,poly.getNode(i).y);
	}
	
	cv::fillConvexPoly(src,pos,poly.size(),color);
	delete[] pos;
	return true;
}
bool DrawPoint  (cv::Mat& src,const Point& pos,int radius , int thickness, const cv::Scalar& color,bool fill){
	cv::circle(src,cv::Point(pos.x, pos.y), radius,color , thickness, 8, 0);
	return true;
}


//<<演算子出力
cv::Mat& operator<<(cv::Mat& src,const Polygon& poly){
	DrawPolygon(src,poly,1,cv::Scalar(255,255,255),true);
	return src;
}
cv::Mat& operator<<(cv::Mat& src,const Point& pos){
	DrawPoint(src,pos,3,1,cv::Scalar(255,255,255),true);
	return src;
}

#endif
