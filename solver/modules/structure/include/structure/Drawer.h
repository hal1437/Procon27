

#pragma once 

#ifdef FIND_OPENCV

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <structure/Point.hpp>
#include <structure/Polygon.h>

//cv::Matに出力
bool DrawPolygon(cv::Mat& src,const Polygon& poly,int thickness, const cv::Scalar& color ,bool fill);
bool DrawPoint  (cv::Mat& src,const Point&    pos,int radius   , int thickness , const cv::Scalar& color ,bool fill);


//<<演算子出力
cv::Mat& operator<<(cv::Mat& src,const Polygon& poly);
cv::Mat& operator<<(cv::Mat& src,const Point& pos);

#endif
