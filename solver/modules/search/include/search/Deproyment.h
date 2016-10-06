
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
	constexpr int LENGTH_EPS = 1.0e1;
	constexpr int ANGLE_EPS  = 1.0e1;
	Polygon base;//ベース

	double Length(const Polygon& p,int index);
	double Angle (const Polygon& p,int index,bool Rev=false);

	std::vector<result> Solver(std::vector<Polygon> list);

public:

	//実行
	void Run(std::vector<Polygon> list);
};
