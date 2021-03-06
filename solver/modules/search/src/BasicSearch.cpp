
#include <search/BasicSearch.h>
#define LoopRenge(x,r) ((x+r)%r)
#define LR(x,r) (LoopRenge(x,r))


double BasicSearch::Length(const Point& lhs,const Point& rhs){
	return std::sqrt(std::pow(lhs.x - rhs.x,2) + std::pow(lhs.y - rhs.y,2));
}

std::vector<TransParam> BasicSearch::Listup(const Polygon& frame,int frame_index, const Polygon& piece){
	//多角形の頂点を枠の頂点に一致させる。
	std::vector<TransParam> answer;

	const Polygon& pol    = piece;
	const Polygon  re_pol = piece.getReverse();

	//ピースの頂点数に対して
	for(int i=0;i<piece.size();i++){
		
		//ピース角度が小さければ
		if(frame.getAngle(frame_index) > piece.getAngle(i)){
			bool fitting;
			//角度差が極限まで小さければ
			if(std::abs(frame.getAngle(frame_index) - piece.getAngle(i)) < SAME_ANGLE_EPS){
				//等角設置
				fitting=true;
			}else {
				//非等角設置
				fitting=false;
			}
			//変換を記録
			//角度一致(2種類)
			Point v1 = pol   .getNode(LR(i          -1,pol   .size())) - pol   .getNode(i);
			Point v2 = pol   .getNode(LR(i          +1,pol   .size())) - pol   .getNode(i);
			Point r1 = re_pol.getNode(LR(i          -1,re_pol.size())) - re_pol.getNode(i);
			Point r2 = re_pol.getNode(LR(i          +1,re_pol.size())) - re_pol.getNode(i);
			Point f1 = frame .getNode(LR(frame_index-1,frame .size())) - frame .getNode(frame_index);
			Point f2 = frame .getNode(LR(frame_index+1,frame .size())) - frame .getNode(frame_index);
			answer.push_back(TransParam{i,frame.getNode(frame_index),false,Point::getAngle2Vec(f1,v2)});
			answer.push_back(TransParam{i,frame.getNode(frame_index),true ,Point::getAngle2Vec(f1,r1)});
			
			//角度不一致(追加2種類)
			if(fitting==false){
				answer.push_back(TransParam{i,frame.getNode(frame_index),false,Point::getAngle2Vec(f2,v1)});
				answer.push_back(TransParam{i,frame.getNode(frame_index),true ,Point::getAngle2Vec(f2,r2)});
			}
		}
	}
	//範囲外のものは除く
	for(int i = 0;i<answer.size();i++){
// 		cv::Mat screen = cv::Mat::zeros(600, 900, CV_8UC3);
		Polygon trans = BasicSearch::Transform(piece,answer[i]);
		bool is_over = false;

		//変形後の全ての頂点がframeに内包されていれば
		for(int j=0;j<trans.size();j++){
 			//近似点が存在する
			bool isSame = false;
			for(int k=0;k<frame.size();k++){
				if(Length(trans.getNode(j), frame.getNode(k)) < SAME_POINT_EPS){
					isSame = true;
					break;
				}
			}
			if(!isSame){
				if(frame.isComprehension(trans.getNode(j))==false){
// 					std::cout << "isNotComprehension:" << j << std::endl;
					is_over = true;
					break;
				}
			}
		}
		//交差しているのもダメ
		for(int j=0;j<frame.size();j++){
			for(int k=0;k<trans.size();k++){
				//点が近すぎる場合は免除
				if(Length(frame.getNode(j)                 ,trans.getNode(k)                 ) > SAME_POINT_EPS &&
				   Length(frame.getNode((j+1)%frame.size()),trans.getNode(k)                 ) > SAME_POINT_EPS && 
				   Length(frame.getNode(j)                 ,trans.getNode((k+1)%trans.size())) > SAME_POINT_EPS &&
				   Length(frame.getNode((j+1)%frame.size()),trans.getNode((k+1)%trans.size())) > SAME_POINT_EPS ){
					//交差していれば
					if(isCrossed(frame.getNode(j),frame.getNode((j+1)%frame.size()),
								trans.getNode(k),trans.getNode((k+1)%trans.size()))){
						is_over = true;
// 						std::cout << "crossed"  << i << ":" << j << ":" << k << std::endl;
						break;
					}
				}
			}
		}
// 		std::cout << (is_over? "('A`)":"（　＾ω＾）") << std::endl;
// // 		フレームを描画
// 		cv::Mat screen = cv::Mat::zeros(600, 900, CV_8UC3);
// 		Point frame_offset(50,50);
// 		for(int i=0;i<frame.size();i++){
// 			Point p1 = frame.getNode(i)+frame_offset;
// 			Point p2 = frame.getNode((i+1) % frame.size())+frame_offset;
// 			cv::line(screen, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
// 		}
// 		//現在のピースを描画
// 		screen << trans * cMat::MakeMoveMatrix(50,50);
//
// // 		表示
// 		cv::namedWindow("InstantViewer", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
// 		cv::imshow("InstantViewer", screen);
// 		cv::waitKey(1);


		//消えてもらおう
		if(is_over == true){
			answer.erase(answer.begin()+i);
			i--;
		}
	}
	return answer;
}
Polygon BasicSearch::Merge(const Polygon& frame, const Polygon& poly){
// 	std::cout << "MERGE PROCCESS" << std::endl;
	Polygon answer = frame;
	bool isMerged = false;

	for(int i=0;i<frame.size();i++){
		for(int j=0;j<poly.size();j++){
			//一致点
			if(Length(frame.getNode(i) , poly.getNode(j)) < SAME_POINT_EPS){
				//まだマージされていなければ
				if(!isMerged){
					Point v1 = poly .getNode(LR(j-1,poly  .size())) - poly .getNode(j);
					Point v2 = poly .getNode(LR(j+1,poly  .size())) - poly .getNode(j);
					Point f1 = frame.getNode(LR(i-1,frame .size())) - frame.getNode(i);
					Point f2 = frame.getNode(LR(i+1,frame .size())) - frame.getNode(i);
					const double SAME_POINT_EPS = 1.0e-12;
					bool fitting = false;
					bool reverse_insert = false;
					bool back_index = false;

					
					//フィッティング
					if(std::abs(M_PI - Point::getAngle2Vec(f1,v1)) > M_PI - SAME_ANGLE_EPS &&
					   std::abs(M_PI - Point::getAngle2Vec(f2,v2)) > M_PI - SAME_ANGLE_EPS){
						reverse_insert = false;
						fitting = true;
// 						std::cout << "fit1" << std::endl;
					}else
					if(std::abs(M_PI - Point::getAngle2Vec(f1,v2)) > M_PI - SAME_ANGLE_EPS &&
					   std::abs(M_PI - Point::getAngle2Vec(f2,v1)) > M_PI - SAME_ANGLE_EPS){
						reverse_insert = true;
						fitting = true;
// 						std::cout << "fit2" << std::endl;
					}
					else if(std::abs(M_PI - Point::getAngle2Vec(f1,v1)) > M_PI - SAME_ANGLE_EPS)reverse_insert = false,back_index = false;//,std::cout << "Merge1" << std::endl;
					else if(std::abs(M_PI - Point::getAngle2Vec(f1,v2)) > M_PI - SAME_ANGLE_EPS)reverse_insert = true ,back_index = false;//,std::cout << "Merge2" << std::endl;
					else if(std::abs(M_PI - Point::getAngle2Vec(f2,v1)) > M_PI - SAME_ANGLE_EPS)reverse_insert = true ,back_index = true ;//,std::cout << "Merge3" << std::endl;
					else if(std::abs(M_PI - Point::getAngle2Vec(f2,v2)) > M_PI - SAME_ANGLE_EPS)reverse_insert = false,back_index = true ;//,std::cout << "Merge4" << std::endl;
					else{
						std::cout << "== NO MATCHING EXCEPTION ==" << std::endl;
						std::cout << "v1:" << v1 << std::endl;
						std::cout << "v2:" << v2 << std::endl;
						std::cout << "f1:" << f1 << std::endl;
						std::cout << "f2:" << f2 << std::endl;
						std::cout << "v1,f1:" << Point::getAngle2Vec(f1,v1) << std::endl;
						std::cout << "v2,f1:" << Point::getAngle2Vec(f2,v1) << std::endl;
						std::cout << "v1,f2:" << Point::getAngle2Vec(f1,v2) << std::endl;
						std::cout << "v2,f2:" << Point::getAngle2Vec(f2,v2) << std::endl;
						std::cout << "===========================" << std::endl;
						return answer;
					}


					//実際に追加
					Point add_p;
					int add_index;
					if(reverse_insert){
						//逆順追加
						for(int k=poly.size()-1;k!=0;k--){
							if(fitting && k==1)answer.setNode(i,poly.getNode(LR(j+k,poly.size())));
							else{
								Point add = poly.getNode(LR(j+k,poly.size()));
								add_index = i + (back_index ? 1 : 0);
								answer.addNode(add_index,add);
							}
						}
					}else{
						//正順追加
						for(int k=1;k<poly.size();k++){
							if(fitting && k==1)answer.setNode(i,poly.getNode(LR(j+k,poly.size())));
							else    {
								Point add = poly.getNode(LR(j+k,poly.size()));
								add_index = i + (back_index ? 1 : 0);
								answer.addNode(add_index,add);
							}
						}
					}
// 					std::cout << "======= INFOMATION =======" << std::endl;
// 					std::cout << "v1:" << v1 << std::endl;
// 					std::cout << "v2:" << v2 << std::endl;
// 					std::cout << "f1:" << f1 << std::endl;
// 					std::cout << "f2:" << f2 << std::endl;
// 					std::cout << "v1,f1:" << Point::getAngle2Vec(v1,f1) << std::endl;
// 					std::cout << "v2,f1:" << Point::getAngle2Vec(v2,f1) << std::endl;
// 					std::cout << "v1,f2:" << Point::getAngle2Vec(v1,f2) << std::endl;
// 					std::cout << "v2,f2:" << Point::getAngle2Vec(v2,f2) << std::endl;
// 					std::cout << "===========================" << std::endl;
					isMerged = true;
				}
			}
		}
	}
	//近似点削除
	for(int i=0;i<answer.size();i++){
		if(Length(answer.getNode(LR(i-1,answer.size())),
		          answer.getNode(LR(i+1,answer.size()))) < 1.0 ||
		   Length(answer.getNode(LR(i  ,answer.size())),
		          answer.getNode(LR(i+1,answer.size()))) < 1.0){
			answer.removeNode(i);
			i=0;
		}
	}

// 	std::cout << answer.size() << std::endl;
	if(!isMerged)std::cout << "Can't merged..." << std::endl;
	return answer;
}


Polygon BasicSearch::Transform(Polygon poly,TransParam trans){
	if(trans.reverse == true)poly.reverse();         //反転
	Point p = poly.getNode(trans.sub_index);         //選択頂点
	poly *= cMat::MakeMoveMatrix(-p.x,-p.y);         //選択頂点を原点に
	poly *= cMat::MakeRotateMatrix(trans.angle);     //回転
	poly *= cMat::MakeMoveMatrix(trans.pos.x,trans.pos.y);//平行移動{
	return poly;
}

bool operator==(const TransParam& lhs, const TransParam& rhs){
	return std::tie(lhs.sub_index,lhs.pos,lhs.reverse,lhs.angle) == std::tie(rhs.sub_index,rhs.pos,rhs.reverse,rhs.angle);
}



