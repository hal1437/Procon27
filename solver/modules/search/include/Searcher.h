
#pragma once

#include <structure/Matrix.hpp>
#include <vector>


//検索クラス
template<class Ans,class... Arg>
class Searcher{
public:
	virtual Ans Search(const Arg& arg) = 0;
};

