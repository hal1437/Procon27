
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
	return true;
}
//再生開始
void InstantViewer::View(){

	int current=0;
	bool used;
	bool frame_view = false;
	bool all_view = false;
	while (1){
		cv::Mat screen = cv::Mat::zeros(600, 900, CV_8UC3);

		double fill_rate = 0;
		double use_area  = 0;
		for(int i=0;i<std::min(static_cast<int>(ans.size()),current+1);i++){
			if(!(ans[i] == TransParam())){
				use_area += BasicSearch::Transform(problem.pieces[i],ans[i]).getArea();
			}
		}
		fill_rate = (use_area / problem.frame.getArea())*100;

		//ピースを使用するかどうか
		if(!(ans[current]==TransParam()))used = true;
		else                             used = false;

		//文字の描画
		std::stringstream ss;
		cv::putText(screen,std::string("Frame")                ,cv::Point( 50,  49),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,std::string("Paramators")           ,cv::Point(600,  50),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,std::string("Index")       +ss.str(),cv::Point(610,  65),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,std::string("SubIndex")    +ss.str(),cv::Point(610,  80),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,std::string("Move ")       +ss.str(),cv::Point(610,  95),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,std::string("Angle")       +ss.str(),cv::Point(610, 110),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,std::string("Reverse")     +ss.str(),cv::Point(610, 125),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,std::string("FillingRate") +ss.str(),cv::Point(610, 140),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		ss << std::setw(2) << current+1 << "/" << problem.pieces.size();
		cv::putText(screen,std::string(":") + ss.str(),cv::Point(690, 65),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		for(int i=0;i<4;i++){
			cv::putText(screen,std::string(":"),cv::Point(690, 80+i*15),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		}
		if(used){
			ss.str("");
			ss << ans[current].sub_index;
			cv::putText(screen,ss.str(),cv::Point(695, 80),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
			ss.str("");
			ss << ans[current].pos;
			cv::putText(screen,ss.str(),cv::Point(695, 95),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
			ss.str("");
			ss << ans[current].angle * 180/M_PI;
			cv::putText(screen,ss.str(),cv::Point(695, 110),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
			ss.str("");
			ss << (ans[current].reverse == true ? "TRUE" : "FALSE");
			cv::putText(screen,ss.str(),cv::Point(695, 125),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		}else{
			cv::putText(screen,"Unused",cv::Point(720, 102),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		}
		ss.str("");
		ss << fill_rate << "%";
		cv::putText(screen,ss.str(),cv::Point(695, 140),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,std::string("Original") ,cv::Point(600,200),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);
		cv::putText(screen,"Right or Left : change current index.   Esc:exit.  E:all_view  F:frame_view"    ,cv::Point( 50, 590),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255), 1, CV_AA);

		

		if(all_view){
			
			for(int i=0;i<=std::min(current,static_cast<int>(ans.size()));i++){
				if(ans[i] == TransParam())continue;
				Polygon poly = BasicSearch::Transform(problem.pieces[i],ans[i]) * cMat::MakeMoveMatrix(50,50);

				//多角形を描画
				cv::Point center;
				screen << poly;
				for(int j=0;j<poly.size();j++){
					Point p1 = poly.getNode(j);
					Point p2 = poly.getNode((j+1) % poly.size());
					cv::line(screen, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,0,255), 1, CV_AA); 
					center.x += p1.x;
					center.y += p1.y;
				}
				center.x /= poly.size();
				center.y /= poly.size();

				//文字配置
				std::stringstream index_ss;
				index_ss << i;
				cv::putText(screen,index_ss.str(),center,cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,0,0), 1, CV_AA);


			}
			//フレームを描画
			for(int i=0;i<problem.frame.size();i++){
				Point p1 = problem.frame.getNode(i) + Point(50,50);
				Point p2 = problem.frame.getNode((i+1) % problem.frame.size()) + Point(50,50);
				cv::line(screen, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,255,255), 1, CV_AA); 
			}
// 			screen << problem.frame * cMat::MakeMoveMatrix(50,50);

		}else{
			Polygon current_frame = problem.frame;
			//現在のフレームを計算
			for(int i=0;i<=std::min(current,static_cast<int>(ans.size()));i++){
				if(ans[i] == TransParam())continue;
				Polygon poly = BasicSearch::Transform(problem.pieces[i],ans[i]);
				current_frame = BasicSearch::Merge(current_frame,poly);
			}

			//フレームを描画
			Point frame_offset(50,50);
			for(int i=0;i<current_frame.size();i++){
				Point p1 = current_frame.getNode(i)+frame_offset;
				Point p2 = current_frame.getNode((i+1) % current_frame.size())+frame_offset;
				cv::line(screen, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
			}
		}
		//現在のピースを描画
		screen << problem.pieces[current] * cMat::MakeMoveMatrix(620,220);
		if(used && !frame_view && !all_view){
			screen << BasicSearch::Transform(problem.pieces[current],ans[current]) * cMat::MakeMoveMatrix(50,50);
		}

		//表示
		cv::namedWindow("InstantViewer", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("InstantViewer", screen);


		//コントロール
		int key = cv::waitKey(0);
		if(key == 102  )frame_view = !frame_view;//Fキー
		if(key == 101  )all_view   = !all_view;//Eキー
		if(key == 63234 || key == 65361)current--;  //左矢印キー
		if(key == 63235 || key == 65363)current++;  //右矢印キー
		if(key == 27   )break;      //Escキー
		if((key == 'q' -'a' + 97) break;
		if(current  < 0                    )current = 0;
		if(current >= problem.pieces.size())current = problem.pieces.size()-1;
		
	}

}

InstantViewer::InstantViewer(){
	this->solver = nullptr;
}

