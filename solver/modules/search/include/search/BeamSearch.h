
#pragma once 
#include <search/Searcher.h>
#include <structure/Matrix.hpp>
#include <structure/Problem.h>


//ビームサーチ
class BeamSearch:public Searcher<std::vector<cMat>,const Problem&>{
public:

	struct Hand{
		int index;
		Point pos;
		bool fixing;     //固定
		std::vector<double> angle; //回転角
	};

public:
	
	typedef Searcher<std::vector<cMat>,Problem> Searcher;
	typedef std::vector<Hand> Log;

private:
	const double SAME_ANGLE_EPS = 0.001;
	std::vector<Hand> Listup(const Problem& prob,const Log& log);
	
public:
	//探索
	virtual Answer Search(Argment arg);
	

};


