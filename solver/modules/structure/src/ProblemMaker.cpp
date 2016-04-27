
#include <structure/ProblemMaker.h>

#include <opencv2/opencv.hpp>
#include <structure/Drawer.h>
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


	for(Point p:points){
		img << p;
	}

	//ピース作成

	cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::imshow("drawing", img);
	cv::waitKey(0);

	return prob;
}

