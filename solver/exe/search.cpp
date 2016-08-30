
#include <iostream>
#include <structure/ProblemMaker.h>
#include <search/SequenceSearch.h>

int main(){
	
	SequenceSearch bs;

	//問題作成
	Problem prob = ProblemMaker::MakeTriangleProblem();

	for(int i=0;i<prob.pieces.size();i++){
		prob.pieces[i].normalize();
	}

	//
	bs.Search(prob);



}
