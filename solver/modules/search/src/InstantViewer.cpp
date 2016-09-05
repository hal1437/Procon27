
#include <search/InstantViewer.h>


void InstantViewer::SetSolver(BasicSearch* solver){
	this->solver = solver;
}
void InstantViewer::SetProblem(const Problem& problem){
	this->problem = problem;
}


//問題解決
bool InstantViewer::Solve(){
	ans = this->solver->Search(this->problem);
}
//再生開始
void InstantViewer::View(){
	

	int current=0;
	while (1){
		cv::Mat screen = cv::Mat::zeros(600, 600, CV_8UC3);
		
		Polygon current_frame = problem.frame;

		//現在のフレームを計算
		for(int i=0;i<std::min(current,static_cast<int>(ans.size()));i++){

		}



		//フレームを描画
		for(int i=0;i<current_frame.size();i++){
			Point p1 = current_frame.getNode(i)+Point(50,50);
			Point p2 = current_frame.getNode((i+1) % current_frame.size())+Point(50,50);
			cv::line(screen, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
		}


		//表示
		cv::namedWindow("InstantViewer", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("InstantViewer", screen);


		//コントロール
		int key = cv::waitKey(0);
		if(key == 63234)current--;  //左矢印キー
		if(key == 63235)current++;  //右矢印キー
		if(key == 27   )break;      //Escキー
		if(current  < 0                    )current = 0;
		if(current >= problem.pieces.size())current = problem.pieces.size()-1;
		
		std::cout << current << std::endl;

	}

}

InstantViewer::InstantViewer(){
	this->solver = nullptr;
}

