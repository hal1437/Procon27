
#include <capture/CaptureIO.h>
#include <search/Deproyment.h>
#include <search/LimitedSearch.h>
#include <search/InstantViewer.h>
#include <search/LengthHeuristic.h>
#include <search/AreaHeuristic.h>
#include <search/WeightComposite.h>

void Search(Problem prob);
void Deproy(Problem prob,int index);

int main(int argc,char* argv[]){

	int device = 0;
	std::cout << "デバイス番号を入力>>";
	std::cin >> device;
	
	CaptureIO cap(device);
	cap.SetSeacher(Search);
	cap.SetDeproymenter(Deproy);
	cap.SetExpansion(0.5);
	
	cap.Run();
}

void Search(Problem prob){

	LimitedSearch bs;
	InstantViewer viewer;
	WeightComposite* h = new WeightComposite();
	
	//評価関数登録
	h->AddHeuristic(new AreaHeuristic()  ,1.0);
	h->AddHeuristic(new LengthHeuristic(),0.7);
	bs.AddHeuristic(h);

	//正規化
	prob.frame.ConfirmNumbers();
	prob.frame.normalize();
	for(int i=0;i<prob.pieces.size();i++){
		prob.frame.ConfirmNumbers();
		prob.pieces[i].normalize();
	}

	viewer.SetProblem(prob);
	viewer.SetSolver(&bs);

	viewer.Solve();
	viewer.View();
	delete h;
}
void Deproy(Problem prob,int index){
	for(Polygon& p :prob.pieces)p.normalize();
	Deproyment().Run(prob,index);
}
