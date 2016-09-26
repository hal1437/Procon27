
#pragma once 
#include <search/BasicSearch.h>

//シーケンスサーチ
class SequenceSearch:public BasicSearch{
public:
	//探索
	virtual Answer Search(const Problem& prob);

};


