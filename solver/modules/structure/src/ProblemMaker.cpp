
#include <structure/ProblemMaker.h>

#include <opencv2/opencv.hpp>
#include <structure/Drawer.h>

bool ProblemMaker::isCrossing(const Point& p11,const Point& p12,const Point& p21,const Point& p22){
	// var ta = (cx    - dx)    * (ay    - cy)    + (cy    - dy)    * (cx    - ax);
	// var tb = (cx    - dx)    * (by    - cy)    + (cy    - dy)    * (cx    - bx);
	// var tc = (ax    - bx)    * (cy    - ay)    + (ay    - by)    * (ax    - cx);
	// var td = (ax    - bx)    * (dy    - ay)    + (ay    - by)    * (ax    - dx);
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

Problem ProblemMaker::MakeRandomProblem(){
	Problem prob;
	std::random_device rd;

	const Range<_Point<int>> frame_range   (_Point<int>(400,400),_Point<int>(300,300));  //フレーム生成範囲
	const Range<int>   edge_div_range(6,4);                            //辺上の頂点の生成数範囲
	const int edge_div_round = 10;                                     //辺上の頂点の揺らぎ

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
	prob.frame.addNode(Point(frame_width,0           ));
	prob.frame.addNode(Point(frame_width,frame_height));
	for(int i=0;i<4;i++){
		//pointsに登録
		points.push_back(prob.frame.getNode(i));
	}
	std::cout << "完了" << std::endl;

	//辺上の点を追加
	std::cout << "辺の頂点を作成..." << std::flush;
	CWFor(dire){
		//4~6回等分
		int times = rd() % edge_div_range.diff() + edge_div_range.min;
		for(int i=1;i<times;i++){
			int r_x = (rd() % edge_div_round) - edge_div_round/2.0;
			int r_y = (rd() % edge_div_round) - edge_div_round/2.0;

			int base_x = (frame_width  / static_cast<double>(times) * i + r_x) * (dire.y!=0) + frame_width  * (dire.x==-1);
			int base_y = (frame_height / static_cast<double>(times) * i + r_x) * (dire.x!=0) + frame_height * (dire.y==-1);
			points.push_back(Point(base_x,base_y));
			if(i!=1){
				pairs.push_back(std::make_pair(points.size()-2,points.size()-1));
			}
		}
	}
	frame_points = points.size();
	std::cout << "完了" << std::endl;

	//領域内に適当に点を追加
	std::cout << "構成頂点を作成..." << std::flush;
	int private_radius = 60; //点同士の半径
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
		int p1 = rd()%points.size();
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
		pairs.push_back(std::make_pair(p1,p2));
	}
	std::cout << "完了" << std::endl;
	//交差点を排除
	std::cout << "交差辺を削除..." << std::flush;
	for(int i=0;i<pairs.size();i++){
		int j;
		for(j=0;j<pairs.size();j++){
			if(isCrossing(points[pairs[i].first],
			              points[pairs[i].second],
						  points[pairs[j].first],
						  points[pairs[j].second])){
				pairs.erase(pairs.begin()+ j );
			}
		}
	}
	std::cout << "完了" << std::endl;

	//頂点と辺配列からポリゴンに変換
	//ヒント：枠の構成辺以外の辺は、全て表と裏で二箇所含まれる。
	//　　　　よってポリゴンが全て三角形の場合の合計数は
	//　　　　枠の構成辺数 + その他の辺の数*2と予想される。
	std::cout << "ポリゴン生成..." << std::flush;
	std::vector<std::pair<int,int>> edges = pairs;//複製
	for(int i=0;i<edges.size();i++){
		
	}
	std::cout << "完了" << std::endl;


	//描画
	for(auto l:pairs){
		line(img, cv::Point(points[l.first].x,points[l.first].y), cv::Point(points[l.second].x,points[l.second].y), cv::Scalar( 255, 255, 255 ));
	}
	for(Point p:points)img << p;
	cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::imshow("drawing", img);
	cv::waitKey(0);

	return prob;
}

