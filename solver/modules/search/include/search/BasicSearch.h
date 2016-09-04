
#pragma once 
#include <search/Searcher.h>
#include <structure/Matrix.hpp>
#include <structure/Problem.h>
#include <structure/Drawer.h>
#include <structure/Algorithm.h>
#include <opencv2/opencv.hpp>
#include <random>

//基本関数を含んだ探索クラス
class BasicSearch:public Searcher<std::vector<cMat>,const Problem&>{
public:

	//ピースの変換
	struct Hand{
		int sub_index;//ピース頂点番号
		Point pos;    //平行移動量
		bool reverse; //反転
		double angle; //回転移動角
	};

public:
	
	typedef Searcher<std::vector<cMat>,Problem> Searcher;
	typedef std::vector<Hand> Log;

protected:
	const double SAME_ANGLE_EPS = 0.001;

	//頂点に対する変形のリストを取得
	std::vector<Hand> Listup(const Polygon& frame,int frame_index, const Polygon& piece);
	
	//合致
	Polygon Merge(const Polygon& frame, const Polygon& poly);
	
	//変形
	Polygon Transform(Polygon poly,Hand trans);
public:
	//探索
	virtual Answer Search(const Problem& prob) = 0;
	

};


