
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

Problem ProblemMaker::MakeRandomProblem(){
	Problem prob;
	std::random_device rd;

	int frame_height = rd()%100 + 300;//枠の高さ
	int frame_width  = rd()%100 + 300;//枠の幅
	int round = 10;
	std::vector<Point> points;
	cv::Mat img = cv::Mat::zeros(500, 500, CV_8UC3);

	//枠の角を追加
	prob.frame.addNode(Point(0,0));
	prob.frame.addNode(Point(0,frame_height));
	prob.frame.addNode(Point(frame_width,0));
	prob.frame.addNode(Point(frame_width,frame_height));
	for(int i=0;i<4;i++){
		points.push_back(prob.frame.getNode(i));
	}

	//辺上の線をランダムに追加
	CWFor(dire){
		//4~6回等分
		int times = rd() % 5 + 4;
		std::cout << times << std::endl;
		for(int i=1;i<times;i++){
			int r_x = (rd() % round) - round/2.0;
			int r_y = (rd() % round) - round/2.0;

			int base_x = (frame_width  / static_cast<double>(times) * i + r_x) * (dire.y!=0) + frame_width  * (dire.x==-1);
			int base_y = (frame_height / static_cast<double>(times) * i + r_x) * (dire.x!=0) + frame_height * (dire.y==-1);
			points.push_back(Point(base_x,base_y));
		}
	}

	//領域内に適当に点を追加
	int private_radius = 50; //点同士の半径
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
			std::cout << "generating:" << i << "\r";
			tryal=0;
			points.push_back(rand_point);
		}
	}

	//組み合わせ生成
	int lines = 100;
	std::vector<std::pair<int,int> > pairs;
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
		line(img, cv::Point(points[p1].x,points[p1].y), cv::Point(points[p2].x,points[p2].y), cv::Scalar( 255, 255, 255 ));
	}



	for(Point p:points){
		img << p;
	}

	//ピース作成

	cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::imshow("drawing", img);
	cv::waitKey(0);

	return prob;
}

