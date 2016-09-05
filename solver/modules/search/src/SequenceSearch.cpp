
#include <search/SequenceSearch.h>

SequenceSearch::Answer SequenceSearch::Search(const Problem& prob){
	SequenceSearch::Answer answer;  //回答
	Polygon frame = prob.frame; //フレーム
	std::random_device rd;      //乱数生成器

	int retry = 0;//再試行

	//全てのピースに対して
	for(int p = 0;p<prob.pieces.size();p++){

		int put_frame_index = rd() % frame.size(); //フレームの配置頂点

// 		//フレームを描画
// 		cv::Mat frame_base = cv::Mat::zeros(600, 600, CV_8UC3);
// 		for(int i=0;i<frame.size();i++){
// 			Point p1 = frame.getNode(i)+Point(50,50);
// 			Point p2 = frame.getNode((i+1) % frame.size())+Point(50,50);
// 			cv::line(frame_base, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
// 		}

		//リストアップ実施
		std::vector<SequenceSearch::Hand> list = Listup(frame,put_frame_index % frame.size(),prob.pieces[p]);
		
// 		//ポリゴンを描画
// 		if(list.size() > 0){
// 			int i = 0;
// 			Polygon origin = prob.pieces[p];
//
// 			//フレームからクローンして
// 			cv::Mat img = frame_base.clone(); 
//
// 			//オリジナルを出力
// 			if(list[i].reverse == false)img << origin * cMat::MakeMoveMatrix(100,500);
// 			else                        img << origin.getReverse() * cMat::MakeMoveMatrix(100,500);
// 			//変形後を出力
// 			img << Transform(origin,list[i]) * cMat::MakeMoveMatrix(50,50);
//
// 			cv::namedWindow("B-Search", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
// 			cv::imshow("B-Search", img);
// 			cv::waitKey(1);
// 		}

		//先頭の一つ目の変形を適用
		Polygon trans = prob.pieces[p];
		if(list.size() > 0){
			Hand apply;
			frame = Merge(frame,Transform(trans,list[0]));
			retry = 0;

			//出力
			apply = list[0];
			std::cout << std::left << std::fixed;
			std::cout << std::setw(2) << p 
			          << "|Rotate:" << std::setw(7) << std::setprecision(2) << apply.angle * 180 / M_PI << "[deg] | " 
					  << "Move:("   << std::setw(7) << std::setprecision(2) << apply.pos.x << ","
					                << std::setw(7) << std::setprecision(2) << apply.pos.y << ") "
					  << ((apply.reverse == true) ? "REVERSED" : "")
			          << std::endl;

			answer.push_back(cMat::MakeRotateMatrix(list[0].angle) * cMat::MakeMoveMatrix(list[0].pos.x,list[0].pos.y));
		}else{
			if(retry < 10){
				//再検索
				p--;
				retry++;
				continue;
			}
			else{
				retry = 0;
				std::cout << p << "|NOT FOUND" << std::endl;
				answer.push_back(cMat());
			}
		}


		/*
		//フレームのみを描画
		frame_base = cv::Mat::zeros(600, 600, CV_8UC3);
		for(int i=0;i<frame.size();i++){
			Point p1 = frame.getNode(i)+Point(50,50);
			Point p2 = frame.getNode((i+1) % frame.size())+Point(50,50);
			cv::line(frame_base, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
		}
		cv::namedWindow("B-Search", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("B-Search",frame_base);
		cv::waitKey(1);
		*/
	}
	std::cout << "finished" << std::endl;
// 	cv::waitKey(0);


	return answer;
}

