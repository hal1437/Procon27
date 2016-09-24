
#include <iostream>
#include <structure/ProblemMaker.h>
#include <search/LimitedSearch.h>
#include <search/InstantViewer.h>
#include <search/LengthHeuristic.h>
#include <search/AreaHeuristic.h>
#include <search/WeightComposite.h>


int main(){
	
	LimitedSearch bs;
	InstantViewer viewer;
	WeightComposite* h = new WeightComposite();
	

	//評価関数登録
	h->AddHeuristic(new AreaHeuristic()  ,1.0);
	h->AddHeuristic(new LengthHeuristic(),0.7);
	bs.AddHeuristic(h);

	//問題作成
	Problem prob = ProblemMaker::MakeTriangleProblem(Range<int>(3,2),10,100,300,400);
	std::cout << std::endl;

	for(int i=0;i<prob.pieces.size();i++){
		prob.pieces[i].normalize();
	}

	viewer.SetProblem(prob);
	viewer.SetSolver(&bs);

	viewer.Solve();
	viewer.View();
	delete h;
}
