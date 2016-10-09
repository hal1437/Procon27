
#include <capture/CaptureIO.h>
#include <search/Deproyment.h>
#include <search/LimitedSearch.h>
#include <search/InstantViewer.h>
#include <search/LengthHeuristic.h>
#include <search/AreaHeuristic.h>
#include <search/WeightComposite.h>

void Search(Problem prob);
void Deproy(Problem prob,int index);
void ShowProblem(Problem prob);

int main(int argc,char* argv[]){

 	int device = 0;
 	std::cout << "デバイス番号を入力>>";
 	std::cin >> device;

 	CaptureIO cap(device);
//	CaptureIO cap("../solver/resource/sample/Test1_origin.png");
	cap.SetSeacher(Search);
	cap.SetDeproymenter(Deproy);
	cap.SetExpansion(1.5);
	
	cap.Run();
}

void Search(Problem prob){
	ShowProblem(prob);

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
	ShowProblem(prob);
	for(Polygon& p :prob.pieces)p.normalize();
	Deproyment().Run(prob,index);
}
void ShowProblem(Problem prob){
	cv::Mat img = cv::Mat::zeros(600, 800, CV_8UC3);
	for(int i=0;i < prob.pieces.size();i++){
		Point center;
		//フレーム描画
		for(int j=0;j<prob.pieces[i].size();j++){
			Point p1 = prob.pieces[i].getNode(j)                            ;
			Point p2 = prob.pieces[i].getNode((j+1) % prob.pieces[i].size());
			center.x += p1.x;
			center.y += p1.y;
			cv::line(img, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
		}
		center.x /= prob.pieces[i].size();
		center.y /= prob.pieces[i].size();
		cv::putText(img, std::to_string(i), cv::Point(center.x,center.y), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255), 1, CV_AA);
	}
	cv::imshow("Problem", img);
	cv::waitKey(0);
}
