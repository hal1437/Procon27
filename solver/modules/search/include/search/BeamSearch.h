
#pragma once 
#include <search/Searcher.h>
#include <structure/Matrix.hpp>
#include <structure/Problem.h>
#include <structure/Drawer.h>
#include <opencv2/opencv.hpp>

//ビームサーチ
class BeamSearch:public Searcher<std::vector<cMat>,const Problem&>{
public:

	struct Hand{
		int sub_index;//ピース頂点番号
		Point pos;    //平行移動量
		bool reverse; //反転
		double angle; //回転移動角
	};

public:
	
	typedef Searcher<std::vector<cMat>,Problem> Searcher;
	typedef std::vector<Hand> Log;

private:
	const double SAME_ANGLE_EPS = 0.001;

	std::vector<Hand> Listup(const Polygon& frame, const Polygon& piece);
	
	//合        致
	Polygon Merge(const Polygon& frame, const Polygon& poly);
	
	//変形
	Polygon Transform(Polygon poly,Hand trans);
public:
	//探索
	virtual Answer Search(const Problem& prob);
	

};


