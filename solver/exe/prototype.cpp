
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <structure/Problem.h>
#include <util/Console.h>
#include <capture/MatIO.h>
#include <capture/CaptureIO.h>
#include <string>


int main(){
	
	//int device = 0;
	//std::cout << "デバイス番号を入力>>";
	//std::cin >> device;
	//CaptureIO cap(device);
	CaptureIO cap("../solver/resource/sample/Test1_origin.png");
	cap.SetExpansion(1.5);
	cap.Run();

	return 0;
}
