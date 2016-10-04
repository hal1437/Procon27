
//グラフアルゴリズムテストコード
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/Matrix.hpp>
#include <structure/ProblemMaker.h>
#include <structure/Drawer.h>
#include <cmath>
#include <opencv2/opencv.hpp>

//index, edge
std::pair<int,int> getNearEdge(std::vector<Polygon>& prob ,int index,int pos){
	struct Node{
		int index;
		int edge;
		double delta;//
	};
	double length = (prob[index].getNode(pos) - prob[index].getNode((pos+1) % prob[index].size())).size();

	std::vector<Node> nodes;
	for(int i=0;i<prob.size();i++){
		if(i==index) continue;
		for(int j=0;j<prob[i].size();j++){
			double l = (prob[i].getNode((j+1) % prob[i].size()) - prob[i].getNode(j)).size();
			nodes.push_back(Node{i,j,std::abs(length-l)});
		}
	}
	std::sort(nodes.begin(),nodes.end(),[&](Node& lhs,Node& rhs){
		return lhs.delta < rhs.delta;
	});
	return std::make_pair(nodes[0].index,nodes[0].edge);
}

void DrawEdge(cv::Mat img,const Polygon& poly,int index,cv::Scalar color){
	cv::line(img,cv::Point(poly.getNode(index).x,
	                       poly.getNode(index).y),
	             cv::Point(poly.getNode((index+1)%poly.size()).x,
	                       poly.getNode((index+1)%poly.size()).y),color,2,CV_AA);
}

// コールバック関数
void callback(int event, int x, int y, int flags, void* param){
	Point* mouse_pos = static_cast<Point*>(param);

    switch (event){
		case cv::EVENT_LBUTTONDOWN:
			mouse_pos->x = x;
			mouse_pos->y = y;
			std::cout << "mouse_event:" << *mouse_pos << std::endl;
			break;
	}
}

int main(){

	Point mouse_pos;
	std::cout << "---Graph Algorithm Test---" << std::endl;
	cv::namedWindow("logical", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::setMouseCallback("logical", callback, static_cast<void*>(&mouse_pos));

	Problem problem = ProblemMaker::MakeTriangleProblem(Range<int>(1,1),10,200);

	for(Polygon& p :problem.pieces){
		p.normalize();
	}

	std::cout << "三角問題" << std::endl;
	while(1){
		cv::Mat img = cv::Mat::zeros(600, 1200, CV_8UC3);
		for(int i=0;i<problem.pieces.size();i++){
			Point offset((i%6)*300+20,(i/6)*300+20);

			img << problem.pieces[i] * cMat::MakeMoveMatrix(offset.x,offset.y);

			for(int j=0;j<problem.pieces[i].size();j++){
				//範囲が一定以内
				if((problem.pieces[i].getNode(j) + offset - mouse_pos).size() < 7){
					Polygon offseted = problem.pieces[i] * cMat::MakeMoveMatrix(offset.x,offset.y);

					DrawPoint(img,offseted.getNode(j)                      ,5,1,cv::Scalar(0,0,255),false);
					DrawPoint(img,offseted.getNode((j+1) % offseted.size()),5,1,cv::Scalar(0,0,255),false);
					DrawEdge (img,offseted,j,cv::Scalar(0,0,255));
					//
					std::pair<int,int> near = getNearEdge(problem.pieces,i,j);

					Point offset((near.first%6)*300+20,(near.first/6)*300+20);
					Polygon offseted_ = problem.pieces[near.first] * cMat::MakeMoveMatrix(offset.x,offset.y);
					DrawEdge (img,offseted_,near.second,cv::Scalar(0,150,0));



				}
			}
		}
		cv::imshow("logical", img);
		cv::waitKey(1);
	}

}

