#pragma once
#include <structure/Drawer.h>

cv::Vec3b GetPixcel(cv::Mat img,int x, int y);
void SetPixcel(cv::Mat img,int x, int y, int r, int g, int b);

double ColorDistance(cv::Vec3b p1, cv::Vec3b p2);