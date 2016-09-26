
#pragma once

#include <structure/Matrix.hpp>
#include <vector>

//検索クラス
template<class Ans,class Arg>
class Searcher{
public:
	typedef Arg Argment;
	typedef Ans Answer;
public:
	virtual Ans Search(Arg arg) = 0;
};

