
#pragma once 
#include <search/BasicSearch.h>
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
		int index;
		TransParam trans;
		double length_diff;   //線形誤差
		double angle_sum[2]; //角度和
	};
private:
	constexpr static double LENGTH_EPS = 1.0;
	constexpr static double ANGLE_EPS  = 0;

	double Length(const Polygon& p,int index,bool Rev=false);
	double Angle (const Polygon& p,int index,bool Rev=false);
	double Angle2(const Polygon& p,int index,bool Rev=false);

	std::vector<result> Solver(std::vector<Polygon> list);

public:
	Polygon base;//ベース

	//実行
	void Run(Problem prob,int index);
	void Run(std::vector<Polygon> list);
};
