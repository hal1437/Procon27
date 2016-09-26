
#include <search/SequenceSearch.h>

SequenceSearch::Answer SequenceSearch::Search(const Problem& prob){
	SequenceSearch::Answer answer;  //回答
	Polygon frame = prob.frame; //フレーム
	std::random_device rd;      //乱数生成器

	int retry = 0;//再試行

	//全てのピースに対して
	for(int p = 0;p<prob.pieces.size();p++){

		int put_frame_index = rd() % frame.size(); //フレームの配置頂点

		//リストアップ実施
		std::vector<TransParam> list = Listup(frame,put_frame_index % frame.size(),prob.pieces[p]);
		
		//先頭の一つ目の変形を適用
		Polygon trans = prob.pieces[p];
		if(list.size() > 0){
			TransParam apply;
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

			answer.push_back(apply);
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
				answer.push_back(TransParam());
			}
		}
	}
	std::cout << "finished" << std::endl;
	return answer;
}

