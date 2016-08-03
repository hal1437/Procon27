
#include <search/BeamSearch.h>
#define LoopRenge(x,r) ((x+r)%r)
#define LR(x,r) (LoopRenge(x,r))

std::vector<BeamSearch::Hand> BeamSearch::Listup(const Problem& prob,const Log& log){
	//多角形の頂点を枠の頂点に一致させる。
	std::vector<BeamSearch::Hand> answer;

	//3重ループ
	//i:フレームの頂点数
	//j:残りピース数
	//k:ピースの頂点数


	for(int i=0;i<prob.frame.size();i++){
		for(int j=0;j<prob.pieces.size();j++){
			//j番目がすでにLOGに入ってなければ
			if(std::find_if(log.begin(),log.end(),[&](const Hand& hand){
				return (j == hand.index);
			}) != log.end())continue;
			
			//ピースの頂点数に対して
			for(int k=0;k<prob.pieces[j].size();k++){
				
				//ピース角度が小さければ
				if(prob.frame.getAngle(i) > prob.pieces[j].getAngle(k)){
					bool fitting;
					//角度差が極限まで小さければ
					if(std::abs(prob.frame.getAngle(i) - prob.pieces[j].getAngle(k)) < SAME_ANGLE_EPS){
						//等角設置
						fitting=true;
					}else {
						//非等角設置
						fitting=false;
					}
					//変換を記録
					const Polygon& frame  = prob.frame;
					const Polygon& pol    = prob.pieces[j];
					const Polygon  re_pol = prob.pieces[j].getReverse();
// 					re_pol.ConfirmNumbers();

					//角度一致(2種類)
					Point v1 = pol   .getNode(LR(k-1,pol   .size())) - pol   .getNode(k);
					Point r1 = re_pol.getNode(LR(k-1,re_pol.size())) - re_pol.getNode(k);
					Point f1 = frame .getNode(LR(i-1,frame .size())) - frame .getNode(i);
					Point v2 = pol   .getNode(LR(k+1,pol   .size())) - pol   .getNode(k);
					Point r2 = re_pol.getNode(LR(k+1,re_pol.size())) - re_pol.getNode(k);
					Point f2 = frame .getNode(LR(i+1,frame .size())) - frame  .getNode(i);
					answer.push_back(Hand{j,k,prob.frame.getNode(i),false,Point::getAngle2Vec(v1,f1)});
					answer.push_back(Hand{j,k,prob.frame.getNode(i),true ,Point::getAngle2Vec(r1,f2)});
					
					//角度不一致(追加2種類)
					if(fitting==false){
						answer.push_back(Hand{j,k,prob.frame.getNode(i),false,Point::getAngle2Vec(v2,f2)});
						answer.push_back(Hand{j,k,prob.frame.getNode(i),true ,Point::getAngle2Vec(r2,f1)});
					}
				}
			}
			
			
		}
	}
	return answer;
}

BeamSearch::Answer BeamSearch::Search(const Problem& prob){
	BeamSearch::Answer answer;
	std::vector<BeamSearch::Hand> list = Listup(prob,Log());
	cv::Mat frame_base = cv::Mat::zeros(600, 600, CV_8UC3);


	//フレームを描画
	for(int i=0;i<prob.frame.size();i++){
		Point p1 = prob.frame.getNode(i)+Point(100,100);
		Point p2 = prob.frame.getNode((i+1) % prob.frame.size())+Point(100,100);
		cv::line(frame_base, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,0,200), 1, CV_AA); 
	}

	for(int i=0;i<list.size();i++){
		std::cout << "#" << i << std::endl;
		std::cout << "  index   = " << list[i].index     << std::endl;
		std::cout << "  s_index = " << list[i].sub_index << std::endl;
		std::cout << "  pos     = " << list[i].pos       << std::endl;
		std::cout << "  reverse = " << list[i].reverse   << std::endl;
		std::cout << "  angle   = " << list[i].angle*180/M_PI   << std::endl;

		Polygon trans = prob.pieces[list[i].index];
		cv::Mat img = frame_base.clone();

		//変形
		if(list[i].reverse == true)trans.reverse();         //反転
		Point p = trans.getNode(list[i].sub_index);         //選択頂点
		trans *= cMat::MakeMoveMatrix(-p.x,-p.y);           //選択頂点を原点に
		trans *= cMat::MakeRotateMatrix(list[i].angle);     //回転
		trans *= cMat::MakeMoveMatrix(list[i].pos.x,list[i].pos.y);//平行移動

		//出力
		if(list[i].reverse == false){
			img << prob.pieces[list[i].index] * cMat::MakeMoveMatrix(100,100);
		}else{
			img << prob.pieces[list[i].index].getReverse() * cMat::MakeMoveMatrix(100,100);
		}
		img << trans * cMat::MakeMoveMatrix(100,100);

		cv::namedWindow("B-Search", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("B-Search", img);
		cv::waitKey(0);
	}

	return answer;
}

