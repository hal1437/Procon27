
#pragma once 
#include <structure/Matrix.hpp>
#include <structure/Problem.h>
#include <structure/Drawer.h>
#include <structure/Algorithm.h>
#include <opencv2/opencv.hpp>
#include <random>


//展開クラス
class Deproyment{
public:
	struct result{
		TransParam trans;
		double length_diff;   //線形誤差
		double angle_sum[2]; //角度和
	};
private:
	Polygon base;//ベース

	std::vector<result> Solver();

public:

	//実行
	void Run(std::vector<Polygon> list);
};
