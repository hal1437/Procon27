
#include <iostream>
#include <structure/ProblemMaker.h>
#include <search/LimitedSearch.h>
#include <search/InstantViewer.h>

int main(){
	
	LimitedSearch bs;
	InstantViewer viewer;

	//問題作成
	Problem prob = ProblemMaker::MakeTriangleProblem();

	for(int i=0;i<prob.pieces.size();i++){
		prob.pieces[i].normalize();
	}

	viewer.SetProblem(prob);
	viewer.SetSolver(&bs);

	viewer.Solve();
	viewer.View();

}
