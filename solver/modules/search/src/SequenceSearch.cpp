
#include <search/SequenceSearch.h>
#define LoopRenge(x,r) ((x+r)%r)
#define LR(x,r) (LoopRenge(x,r))

std::vector<SequenceSearch::Hand> SequenceSearch::Listup(const Polygon& frame,int frame_index, const Polygon& piece){
	//多角形の頂点を枠の頂点に一致させる。
	std::vector<SequenceSearch::Hand> answer;

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
			Point v1 = pol   .getNode(LR(i         -1,pol   .size())) - pol   .getNode(i);
			Point r1 = re_pol.getNode(LR(i         -1,re_pol.size())) - re_pol.getNode(i);
			Point f1 = frame .getNode(LR(frame_index-1,frame .size())) - frame .getNode(frame_index);
			Point v2 = pol   .getNode(LR(i         +1,pol   .size())) - pol   .getNode(i);
			Point r2 = re_pol.getNode(LR(i         +1,re_pol.size())) - re_pol.getNode(i);
			Point f2 = frame .getNode(LR(frame_index+1,frame .size())) - frame .getNode(frame_index);
			answer.push_back(Hand{i,frame.getNode(frame_index),false,Point::getAngle2Vec(v1,f1)});
			answer.push_back(Hand{i,frame.getNode(frame_index),true ,Point::getAngle2Vec(r1,f2)});
			
			//角度不一致(追加2種類)
			if(fitting==false){
				answer.push_back(Hand{i,frame.getNode(frame_index),false,Point::getAngle2Vec(v2,f2)});
				answer.push_back(Hand{i,frame.getNode(frame_index),true ,Point::getAngle2Vec(r2,f1)});
			}
		}
	}
	//範囲外のものは除く
	int old = answer.size();
	int index = 0;
	for(int i = 0;i<answer.size();i++){
		Polygon trans = Transform(piece,answer[i]);
		bool is_over = false;

		//変形後の全ての頂点がframeに内包されていれば
		for(int j=0;j<trans.size();j++){
			if(trans.getNode(j) == frame.getNode(frame_index))continue;
			if(frame.isComprehension(trans.getNode(j))==false){
				is_over = true;
				break;
			}
		}
		//交差しているのもダメ
		for(int j=0;j<frame.size();j++){
			for(int k=0;k<trans.size();k++){
				if(isCrossed(frame.getNode(j),frame.getNode((j+1)%frame.size()),
				             trans.getNode(k),trans.getNode((k+1)%piece.size()))){
					is_over = true;
// 					std::cout << "crossed"  << i << ":" << j << ":" << k << std::endl;
					break;
				}
			}
		}

		//消えてもらおう
		if(is_over == true){
			answer.erase(answer.begin()+i);
			i--;
		}else{
		}
	}
	return answer;
}
Polygon SequenceSearch::Merge(const Polygon& frame, const Polygon& poly){
	Polygon answer = frame;

	for(int i=0;i<frame.size();i++){
		for(int j=0;j<poly.size();j++){
			//一致点
			if(frame.getNode(i) == poly.getNode(j)){
				Point v1 = poly .getNode(LR(j-1,poly  .size())) - poly .getNode(j);
				Point v2 = poly .getNode(LR(j+1,poly  .size())) - poly .getNode(j);
				Point f1 = frame.getNode(LR(i-1,frame .size())) - frame.getNode(i);
				Point f2 = frame.getNode(LR(i+1,frame .size())) - frame.getNode(i);
				
				//v1とf1の傾きがほぼ等しい( |PI-x| > PI-eps )
				if(std::abs(M_PI - Point::getAngle2Vec(v1,f1)) > M_PI - SAME_ANGLE_EPS){
					//一致点の前に正順入れ
					for(int k=1;k<poly.size();k++){
						answer.addNode(i,poly.getNode(LR(j+k,poly.size())));
					}
				}else 
				//v1とf2の傾きがほぼ等しい
				if(std::abs(M_PI - Point::getAngle2Vec(v1,f2)) > M_PI - SAME_ANGLE_EPS){
					//一致点の前に逆順入れ
					for(int k=poly.size()-1;k!=0;k--){
						answer.addNode(i+1,poly.getNode(LR(j+k,poly.size())));
					}
				}else
				//v2とf1の傾きがほぼ等しい
				if(std::abs(M_PI - Point::getAngle2Vec(v2,f1)) > M_PI - SAME_ANGLE_EPS){
					//一致点の後ろにに逆順入れ
					for(int k=poly.size()-1;k!=0;k--){
						answer.addNode(i,poly.getNode(LR(j+k,poly.size())));
					}
				}else
				//v2とf2の傾きがほぼ等しい
				if(std::abs(M_PI - Point::getAngle2Vec(v2,f2)) > M_PI - SAME_ANGLE_EPS){
					//一致点の後ろに正順入れ
					for(int k=1;k<poly.size();k++){
						answer.addNode(i+1,poly.getNode(LR(j+k,poly.size())));
					}
				}else{
					std::cout << "== NO MATCHING EXCEPTION ==" << std::endl;
					std::cout << "v1:" << v1 << std::endl;
					std::cout << "v2:" << v2 << std::endl;
					std::cout << "f1:" << f1 << std::endl;
					std::cout << "f2:" << f2 << std::endl;
					std::cout << "v1,f1:" << Point::getAngle2Vec(v1,f1) << std::endl;
					std::cout << "v2,f1:" << Point::getAngle2Vec(v2,f1) << std::endl;
					std::cout << "v1,f2:" << Point::getAngle2Vec(v1,f2) << std::endl;
					std::cout << "v2,f2:" << Point::getAngle2Vec(v2,f2) << std::endl;
					std::cout << "===========================" << std::endl;
				}	
				
				return answer;
			}
		}
	}
	std::cout << "Can't merged..." << std::endl;
	return answer;
}


Polygon SequenceSearch::Transform(Polygon poly,Hand trans){
	if(trans.reverse == true)poly.reverse();         //反転
	Point p = poly.getNode(trans.sub_index);         //選択頂点
	poly *= cMat::MakeMoveMatrix(-p.x,-p.y);         //選択頂点を原点に
	poly *= cMat::MakeRotateMatrix(trans.angle);     //回転
	poly *= cMat::MakeMoveMatrix(trans.pos.x,trans.pos.y);//平行移動{
	return poly;
}

SequenceSearch::Answer SequenceSearch::Search(const Problem& prob){
	SequenceSearch::Answer answer;  //回答
	Polygon frame = prob.frame; //フレーム
	std::random_device rd;      //乱数生成器

	int retry = 0;//再試行

	//全てのピースに対して
	for(int p = 0;p<prob.pieces.size();p++){

		int put_frame_index = rd() % frame.size(); //フレームの配置頂点

		//フレームを描画
		cv::Mat frame_base = cv::Mat::zeros(600, 600, CV_8UC3);
		for(int i=0;i<frame.size();i++){
			Point p1 = frame.getNode(i)+Point(100,100);
			Point p2 = frame.getNode((i+1) % frame.size())+Point(100,100);
			cv::line(frame_base, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
		}

		//リストアップ実施
		std::vector<SequenceSearch::Hand> list = Listup(frame,put_frame_index % frame.size(),prob.pieces[p]);
		
		//ポリゴンを描画
		if(list.size() > 0){
			int i = 0;
			Polygon origin = prob.pieces[p];

			//フレームからクローンして
			cv::Mat img = frame_base.clone(); 

			//オリジナルを出力
			if(list[i].reverse == false)img << origin * cMat::MakeMoveMatrix(100,100);
			else                        img << origin.getReverse() * cMat::MakeMoveMatrix(100,100);
			//変形後を出力
			img << Transform(origin,list[i]) * cMat::MakeMoveMatrix(100,100);

			cv::namedWindow("B-Search", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
			cv::imshow("B-Search", img);
			cv::waitKey(1);
		}

		//先頭の一つ目の変形を適用
		Polygon trans = prob.pieces[p];
		if(list.size() > 0){
			frame = Merge(frame,Transform(trans,list[0]));
			retry = 0;
			std::cout << "Applay index:0" << std::endl;
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
				std::cout << "NOT FOUND" << std::endl;
				answer.push_back(cMat());
			}
		}



		//フレームを描画
		frame_base = cv::Mat::zeros(600, 600, CV_8UC3);
		for(int i=0;i<frame.size();i++){
			Point p1 = frame.getNode(i)+Point(100,100);
			Point p2 = frame.getNode((i+1) % frame.size())+Point(100,100);
			cv::line(frame_base, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
		}
		cv::namedWindow("B-Search", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
		cv::imshow("B-Search",frame_base);
		cv::waitKey(1);
	}
	std::cout << "finished" << std::endl;
	cv::waitKey(0);


	return answer;
}

