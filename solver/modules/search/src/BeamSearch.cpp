
#include <search/BeamSearch.h>
#define LoopRenge(x,r) ((x+r)%r)
#define LR(x,r) (LoopRenge(x,r))

std::vector<BeamSearch::Hand> BeamSearch::Listup(const Polygon& frame, const Polygon& piece){
	//多角形の頂点を枠の頂点に一致させる。
	std::vector<BeamSearch::Hand> answer;

	//2重ループ
	//i:フレームの頂点数
	//j:ピースの頂点数
	const Polygon& pol    = piece;
	const Polygon  re_pol = piece.getReverse();


	for(int i=0;i<frame.size();i++){
			
		//ピースの頂点数に対して
		for(int j=0;j<piece.size();j++){
			
			//ピース角度が小さければ
			if(frame.getAngle(i) > piece.getAngle(j)){
				bool fitting;
				//角度差が極限まで小さければ
				if(std::abs(frame.getAngle(i) - piece.getAngle(j)) < SAME_ANGLE_EPS){
					//等角設置
					fitting=true;
				}else {
					//非等角設置
					fitting=false;
				}
				//変換を記録
				//角度一致(2種類)
				Point v1 = pol   .getNode(LR(j-1,pol   .size())) - pol   .getNode(j);
				Point r1 = re_pol.getNode(LR(j-1,re_pol.size())) - re_pol.getNode(j);
				Point f1 = frame .getNode(LR(i-1,frame .size())) - frame .getNode(i);
				Point v2 = pol   .getNode(LR(j+1,pol   .size())) - pol   .getNode(j);
				Point r2 = re_pol.getNode(LR(j+1,re_pol.size())) - re_pol.getNode(j);
				Point f2 = frame .getNode(LR(i+1,frame .size())) - frame .getNode(i);
				answer.push_back(Hand{j,frame.getNode(i),false,Point::getAngle2Vec(v1,f1)});
				answer.push_back(Hand{j,frame.getNode(i),true ,Point::getAngle2Vec(r1,f2)});
				
				//角度不一致(追加2種類)
				if(fitting==false){
					answer.push_back(Hand{j,frame.getNode(i),false,Point::getAngle2Vec(v2,f2)});
					answer.push_back(Hand{j,frame.getNode(i),true ,Point::getAngle2Vec(r2,f1)});
				}
			}
		}
	}
	return answer;
}
Polygon BeamSearch::Merge(const Polygon& frame, const Polygon& poly){
	Polygon answer = frame;

	for(int i=0;i<frame.size();i++){
		for(int j=0;j<poly.size();j++){
			//一致点
			if(frame.getNode(i) == poly.getNode(j)){
				Point v1 = poly .getNode(LR(i-1,poly  .size())) - poly .getNode(i);
				Point v2 = poly .getNode(LR(i+1,poly  .size())) - poly .getNode(i);
				Point f1 = frame.getNode(LR(j-1,frame .size())) - frame.getNode(j);
				Point f2 = frame.getNode(LR(j+1,frame .size())) - frame.getNode(j);
				
				//v1とf1の傾きがほぼ等しい
				if(std::abs(v1.y / v1.x - f1.y / f1.x) < SAME_ANGLE_EPS){
					//一致点の前に逆順入れ
					for(int k=1;k<poly.size();k++){
						answer.addNode(0,poly.getNode(LR(j+k,poly.size())));
						std::cout << "i:" << i << std::endl;
						std::cout << "j:" << j << std::endl;
						std::cout << "k:" << k << std::endl;
					}
				}
				//v1とf2の傾きがほぼ等しい
				if(std::abs(v1.y / v1.x - f2.y / f2.x) < SAME_ANGLE_EPS){
					//一致点の前に逆順入れ
					for(int k=0;k<poly.size();k++)answer.addNode(i+k+1,poly.getNode(LR(j+k,poly.size())));
				}
				//v2とf1の傾きがほぼ等しい
				if(std::abs(v2.y / v2.x - f1.y / f1.x) < SAME_ANGLE_EPS){
					//一致点の前に逆順入れ
					for(int k=poly.size();k!=0;k--)answer.addNode(i+k,poly.getNode(LR(j+k,poly.size())));
				}
				//v2とf2の傾きがほぼ等しい
				if(std::abs(v2.y / v2.x - f2.y / f2.x) < SAME_ANGLE_EPS){
					//一致点の前に逆順入れ
					for(int k=poly.size();k!=0;k--)answer.addNode(i+k+1,poly.getNode(LR(j+k,poly.size())));
				}

				
				return answer;
			}
		}
	}
	std::cout << "Can't merged..." << std::endl;
	return answer;
}


Polygon BeamSearch::Transform(Polygon poly,Hand trans){
	if(trans.reverse == true)poly.reverse();         //反転
	Point p = poly.getNode(trans.sub_index);         //選択頂点
	poly *= cMat::MakeMoveMatrix(-p.x,-p.y);           //選択頂点を原点に
	poly *= cMat::MakeRotateMatrix(trans.angle);     //回転
	poly *= cMat::MakeMoveMatrix(trans.pos.x,trans.pos.y);//平行移動{
	return poly;
}

BeamSearch::Answer BeamSearch::Search(const Problem& prob){
	BeamSearch::Answer answer;
	Polygon frame = prob.frame;

	while(1){
		cv::Mat frame_base = cv::Mat::zeros(600, 600, CV_8UC3);
		std::vector<BeamSearch::Hand> list = Listup(frame,prob.pieces[0]);
		
		//フレームを描画
		for(int i=0;i<frame.size();i++){
			Point p1 = frame.getNode(i)+Point(100,100);
			Point p2 = frame.getNode((i+1) % frame.size())+Point(100,100);
			cv::line(frame_base, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
			std::cout << p1 << p2 << std::endl;
		}

		//ポリゴンを描画
		for(int i=0;i<list.size();i++){
// 			std::cout << "#" << i << std::endl;
// 			std::cout << "  index   = " << 0     << std::endl;
// 			std::cout << "  s_index = " << list[i].sub_index << std::endl;
// 			std::cout << "  pos     = " << list[i].pos       << std::endl;
// 			std::cout << "  reverse = " << list[i].reverse   << std::endl;
// 			std::cout << "  angle   = " << list[i].angle*180/M_PI   << std::endl;

			Polygon trans = prob.pieces[0];
			cv::Mat img = frame_base.clone();

			//変形
			trans = Transform(trans,list[i]);

			//出力
			if(list[i].reverse == false){
				img << prob.pieces[0] * cMat::MakeMoveMatrix(100,100);
			}else{
				img << prob.pieces[0].getReverse() * cMat::MakeMoveMatrix(100,100);
			}
			img << trans * cMat::MakeMoveMatrix(100,100);

			cv::namedWindow("B-Search", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
			cv::imshow("B-Search", img);
			cv::waitKey(0);
		}

		//先頭の一つ目の変形を適用
		Polygon trans = prob.pieces[0];
		trans = Transform(trans,list[0]);

		frame = Merge(frame,trans);
		cv::waitKey(0);
	}
	return answer;
}

