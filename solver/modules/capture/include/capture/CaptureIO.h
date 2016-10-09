#pragma once

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <structure/Problem.h>
#include <util/Console.h>
#include <capture/MatIO.h>
#include <string>
#include <functional>

class CaptureIO{
private:
	int device = 0;
	int mode = 0;
	int value1 = 100;
	int value2 =80;
	int limit_range = 50;
	double accuracy = 3.0;
	double area = 100.0;
	bool resource_mode;
	double expansion = 1.0;

	cv::VideoCapture cap;
	cv::Mat origin, frame;
	std::string resource;
	//Problem problem;

	std::function<void(Problem)> seacher;
	std::function<void(Problem, int)> deproymenter;

public:
	cv::Vec3b center_color[3];

	void Run();
	
	CaptureIO(int device);
	CaptureIO(std::string resource);

	void Setup();
	bool CheckHitKey(int key,char c);
	void SetExpansion(double expansion);

	cv::Mat Threshold(cv::Mat origin);
	cv::Mat ColorGamut(cv::Mat origin);
	std::vector<std::vector<cv::Point>> ContourApprox(cv::Mat origin);

	void toProbrem(Problem &problem, std::vector<std::vector<cv::Point>> approxes, bool isframe);
	void cvPointToPoint(cv::Point &cvpoint, Point &point);

	void SetSeacher(std::function<void(Problem)> seacher);
	void SetDeproymenter(std::function<void(Problem, int)> deproymenter);

	cv::Mat GetFrame();
};
