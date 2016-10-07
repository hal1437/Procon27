#pragma once
#include <structure/Drawer.h>

cv::Vec3b GetPixcel(cv::Mat img,int x, int y);
cv::Vec3b GetPixcel(cv::Mat img,cv::Point p);

void SetPixcel(cv::Mat img,int x, int y, int r, int g, int b);
void SetPixcel(cv::Mat img,int x, int y, int w);

double ColorDistance(cv::Vec3b p1, cv::Vec3b p2);
