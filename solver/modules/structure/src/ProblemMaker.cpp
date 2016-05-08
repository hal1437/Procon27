
#include <structure/ProblemMaker.h>

#include <opencv2/opencv.hpp>
#include <structure/Drawer.h>

bool ProblemMaker::isCrossing(const Point& p11,const Point& p12,const Point& p21,const Point& p22){
	double ta = (p21.x - p22.x) * (p11.y - p21.y) + (p21.y - p22.y) * (p21.x - p11.x);
	double tb = (p21.x - p22.x) * (p12.y - p21.y) + (p21.y - p22.y) * (p21.x - p12.x);
	double tc = (p11.x - p12.x) * (p21.y - p11.y) + (p11.y - p12.y) * (p11.x - p21.x);
	double td = (p11.x - p12.x) * (p22.y - p11.y) + (p11.y - p12.y) * (p11.x - p22.x);

	return (tc * td < 0 && ta * tb < 0);
}

Problem ProblemMaker::MakeEqualAreaProblem(){
	Problem prob;
	return prob;
}

Problem ProblemMaker::MakeTriangleProblem(){
	Problem prob;
	std::random_device rd;

	const Range<Point_i> frame_range(Point_i(400,400),Point_i(300,300));  //フレーム生成範囲
	const Range<int>   edge_div_range(6,4);                               //辺上の頂点の生成数範囲
	const int edge_div_round = 10;                                        //辺上の頂点の揺らぎ
	const int density = 80;                                               //点の生成密度

	const int frame_width  = rd() % frame_range.diff().x  + frame_range.min.y;//枠の幅
	const int frame_height = rd() % frame_range.diff().y  + frame_range.min.x;//枠の高さ

	int frame_points;//フレームの数

	std::vector<Point> points;              //生成された頂点
	std::vector<std::pair<int,int> > pairs; //生成された枝
	cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3); //テストフレーム

	//枠の角を追加
	std::cout << "角の頂点を作成..." << std::flush;
	prob.frame.addNode(Point(0          ,0           ));
	prob.frame.addNode(Point(0          ,frame_height));
	prob.frame.addNode(Point(frame_width,frame_height));
	prob.frame.addNode(Point(frame_width,0           ));
	for(int i=0;i<4;i++){
		//pointsに登録
		points.push_back(prob.frame.getNode(i));
	}
	std::cout << "完了" << std::endl;

	//辺上の点を追加
	std::cout << "辺の頂点を作成..." << std::flush;
	int joint_cc=0;
	for(int v=0;v<4;v++){
		Point base = points[(v+1)%4] - points[v];
		//4~6回等分
		int times = rd() % edge_div_range.diff() + edge_div_range.min;
		for(int i=1;i<times;i++){
			int r = (rd() % edge_div_round) - edge_div_round/2.0;
			Point round_p = base.getNorm() * r;

			Point next = points[v] + (base * i / times)  + round_p;
			points.push_back(next);
			if(i!=1){
				pairs.push_back(std::make_pair(points.size()-2,points.size()-1));
			}else{
				pairs.push_back(std::make_pair(joint_cc,points.size()-1));
				joint_cc++;
			}
		}
		pairs.push_back(std::make_pair(points.size()-1,joint_cc%4));
	}
	frame_points = points.size();
	std::cout << "完了" << std::endl;

	//領域内に適当に点を追加
	std::cout << "構成頂点を作成..." << std::flush;
	int private_radius = density; //点同士の半径
	int retake = 100; //リセット回数
	int tryal = 0;    //生成失敗回数
	std::vector<Point> tmp = points;

	for(int i=0;;i++){
		Point rand_point(rd() % frame_width,rd() % frame_height);
		
		//お前はやりすぎた
		if(tryal > retake){
			i = 0;
			tryal = 0;
			break;
		}
		
		//tmpの中の点と比較しprivate_radius以内であれば
		if(std::any_of(points.begin(),points.end(),[&](const Point& rhs){
			return ((rand_point-rhs).size() <= private_radius);
		})){
			//再生成
			tryal++;
			continue;
		}else{
			tryal=0;
			points.push_back(rand_point);
		}
	}
	std::cout << "完了" << std::endl;

	//組み合わせ生成
	std::cout << "組み合わせ生成..." << std::flush;
	int lines = 1000;
	for(int i=0;i<lines;i++){

		//ランダムな点を抽出
		int p1 = rd() % (points.size()-frame_points) + frame_points;
		int p2=0;
		
		//最近点を抽出
		for(int j=0;j< points.size();j++){
			//同点でない、かつ最近点、かつ重複でないならば
			if(p1 != j && 
			   (points[p1]-points[j]).size() < (points[p1]-points[p2]).size() &&
			   std::none_of(pairs.begin(),pairs.end(),[&](const std::pair<int,int>& p){
			       return ((p.first==p1 && p.second==j)||(p.first==j && p.second==p1));
				})){
				p2 = j;
			}
		}
		if(p1!=p2)pairs.push_back(std::make_pair(p1,p2));
	}
	std::cout << "完了" << std::endl;
	//交差点を排除
	std::cout << "交差辺を削除..." << std::flush;
	for(int i=0;i<pairs.size();i++){
		for(int j=0;j<pairs.size();j++){
			if(i==j)continue;
			_Point<double> vec1 = points[pairs[i].second] - points[pairs[i].first];
			_Point<double> vec2 = points[pairs[j].second] - points[pairs[j].first];
			if(isCrossing(points[pairs[i].first],
			              points[pairs[i].second],
			              points[pairs[j].first],
			              points[pairs[j].second])){
				if(vec1.size() > vec2.size())pairs.erase(pairs.begin()+ i);
				else pairs.erase(pairs.begin()+ j);
				j=0;
			}
		}
	}
	std::cout << "完了" << std::endl;

	//pairsをキレイに
	for(std::pair<int,int>& pp:pairs){
		if(pp.first > pp.second) std::swap(pp.first,pp.second);
	}
	std::sort(pairs.begin(),pairs.end());
	pairs.erase(std::unique(pairs.begin(),pairs.end()),pairs.end());

	//頂点と辺配列からポリゴンに変換
	std::cout << "ポリゴン生成..." << std::flush;
	std::vector<std::tuple<int,int,int>> triangles;
	for(int i=0;i<pairs.size();i++){
		//一辺を取り出し
		for(int j=0;j<pairs.size();j++){
			bool pop = false;
			//共有点が存在する。
			if(pairs[i].first  == pairs[j].first  ||
			   pairs[i].first  == pairs[j].second ||
			   pairs[i].second == pairs[j].first  ||
			   pairs[i].second == pairs[j].second){
				//３つ目の辺を探す
				for(int k=0;k<pairs.size();k++){
					std::vector<int> joints;
					joints.push_back(pairs[i].first);
					joints.push_back(pairs[j].first);
					joints.push_back(pairs[k].first);
					joints.push_back(pairs[i].second);
					joints.push_back(pairs[j].second);
					joints.push_back(pairs[k].second);
					std::sort(joints.begin(),joints.end());
					joints.erase(std::unique(joints.begin(),joints.end()),joints.end());
					
					//三角形成立
					if((i != j) &&
					   (j != k) &&
					   (k != i) &&
					   joints.size()==3){
						auto tt  = std::make_tuple(joints[0],joints[1],joints[2]);
						if(std::find(triangles.begin(),triangles.end(),tt) == triangles.end()){
							triangles.push_back(tt);
							for(auto node: joints){
							}
						}
					}
				}
				
			}
		}
	}
	
	std::cout << "完了" << std::endl;
	std::cout << "生成完了:ピース数" << triangles.size() << std::endl;
/*
	//描画
	cv::Point offsets(40,40);
	Point offsets_p(offsets.x,offsets.y);
	for(auto l:pairs){
		line(img, cv::Point(points[l.first ].x,points[l.first ].y)+offsets,
		          cv::Point(points[l.second].x,points[l.second].y)+offsets,
		          cv::Scalar( 255, 255, 255 ));
	}
	for(auto node:triangles){
		auto img_c = img.clone();
		line(img_c, cv::Point(points[std::get<0>(node)].x,points[std::get<0>(node)].y)+offsets,
		            cv::Point(points[std::get<1>(node)].x,points[std::get<1>(node)].y)+offsets,
		            cv::Scalar( 255, 0, 0 ));
		line(img_c, cv::Point(points[std::get<1>(node)].x,points[std::get<1>(node)].y)+offsets,
		            cv::Point(points[std::get<2>(node)].x,points[std::get<2>(node)].y)+offsets,
		            cv::Scalar( 255, 0, 0 ));
		line(img_c, cv::Point(points[std::get<2>(node)].x,points[std::get<2>(node)].y)+offsets,
		            cv::Point(points[std::get<0>(node)].x,points[std::get<0>(node)].y)+offsets,
		            cv::Scalar( 255, 0, 0 ));
		cv::imshow("drawing", img_c);
		cv::waitKey(0);
	}
	for(Point p:points)img << p+offsets_p;
	cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::imshow("drawing", img);
	cv::imwrite("image.png",img);
	cv::waitKey(0);
*/
	for(auto node:triangles){
		Polygon poly;
		
		poly.addNode(points[std::get<0>(node)]);
		poly.addNode(points[std::get<1>(node)]);
		poly.addNode(points[std::get<2>(node)]);
		
		prob.pieces.push_back(poly);
	}

	return prob;
}

