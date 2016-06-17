
#include <iostream>
#include <structure/ProblemMaker.h>
#include <search/BeamSearch.h>

int main(){
	
	BeamSearch bs;

	//問題作成
	Problem prob = ProblemMaker::MakeTriangleProblem();

	//
	bs.Search(prob);



}
