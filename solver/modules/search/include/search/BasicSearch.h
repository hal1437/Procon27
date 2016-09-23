
#pragma once 
#include <search/Searcher.h>
#include <structure/Matrix.hpp>
#include <structure/Problem.h>
#include <structure/Drawer.h>
#include <structure/Algorithm.h>
#include <opencv2/opencv.hpp>
#include <random>

//ピースの変換
struct TransParam{
	int sub_index;//ピース頂点番号
	Point pos;    //平行移動量
	bool reverse; //反転
	double angle; //回転移動角
};


//基本関数を含んだ探索クラス
class BasicSearch:public Searcher<std::vector<TransParam>,const Problem&>{
public:


public:
	
	typedef Searcher<std::vector<cMat>,Problem> Searcher;
	typedef std::vector<TransParam> Log;

public:
	constexpr static double SAME_ANGLE_EPS = 1.0e-2;
	constexpr static double SAME_POINT_EPS = 1.0e-3;

	//点間距離
	static double Length(const Point& lhs,const Point& rhs);

	//頂点に対する変形のリストを取得
	static std::vector<TransParam> Listup(const Polygon& frame,int frame_index, const Polygon& piece);
	
	//合致
	static Polygon Merge(const Polygon& frame, const Polygon& poly);
	
	//変形
	static Polygon Transform(Polygon poly,TransParam trans);
public:
	//探索
	virtual Answer Search(const Problem& prob) = 0;
	

};

bool operator==(const TransParam& lhs, const TransParam& rhs);


