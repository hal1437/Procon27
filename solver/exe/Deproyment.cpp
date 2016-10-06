
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/Matrix.hpp>
#include <structure/ProblemMaker.h>
#include <structure/Drawer.h>
#include <cmath>
#include <opencv2/opencv.hpp>

void current_mouse_callback(int event,int x,int y,int flag,void* param){
	cv::Point* pos = static_cast<cv::Point*>(param);

	if(event == cv::EVENT_LBUTTONDOWN){
		pos->x = x;
		pos->y = y;
	}
}

//ピース番号,ノード番号,長さ
std::vector<std::tuple<int,int,double>> LengthDeproyment(const std::vector<Polygon>& pieces,Point pp){
	int hand_pol = -1;
	int hand_pos = -1;
	
	//探索
	for(int i=0;i<pieces.size();i++){
		for(int j=0;j<pieces[i].size();j++){
			if(pieces[i].getNode(j) == pp){
				hand_pol = i;
				hand_pos = j;
			}
		}
	}

	//未発見
	if(hand_pol == -1)return std::vector<std::tuple<int,int,double>>();
	
	
	std::vector<std::tuple<int,int,double>> ll;
	for(int i=0;i<pieces.size();i++){
		for(int j=0;j<pieces[i].size();j++){
			double d = (pieces[i].getNode(j)-pieces[i].getNode((j+1)%pieces[i].size())).size();
			ll.push_back(std::make_tuple(i,j,d));
		}
	}
	
	double d_origin = (pieces[hand_pol].getNode(hand_pos) - pieces[hand_pol].getNode((hand_pos+1)%pieces[hand_pol].size())).size();
	std::sort(ll.begin(),ll.end(),[&](std::tuple<int,int,double>& lhs ,std::tuple<int,int,double>& rhs){
		return std::abs(std::get<2>(lhs) - d_origin) < std::abs(std::get<2>(rhs) - d_origin);
	});
	return ll;
}
bool AngleDeproyment(){
	
}
Point getOffset(int index){
	const int SHOW_COLS = 10;
	return Point((index%SHOW_COLS)*100,(index/SHOW_COLS)*100);
}

int main(int argc,char* argv[]){
	
	cv::Point pos(0,0);

	cv::namedWindow("Deproyment", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    cv::setMouseCallback("Deproyment", current_mouse_callback, (void *)&pos);
	Problem prob = ProblemMaker::MakeTriangleProblem();
	
	while(1){
		cv::Mat img = cv::Mat::zeros(600, 800, CV_8UC3);
	
		//ポリゴンの表示
		for(int i=0;i<prob.pieces.size();i++){
			prob.pieces[i].normalize();
			img << prob.pieces[i] * cMat::MakeMoveMatrix(getOffset(i).x,getOffset(i).y);
		}
		//最近点表示
		if(pos != cv::Point(0,0)){
			double length = 1.0e10;
			int index = -1;
			int sub_index = -1;
			for(int i=0;i<prob.pieces.size();i++){
				for(int j=0;j<prob.pieces[i].size();j++){
					double l = (Point(pos.x,pos.y) - prob.pieces[i].getNode(j) - getOffset(i)).size();
					if(l < length){
						length    = l;
						index     = i;
						sub_index = j;
					}
				}
			}
			Point first  = prob.pieces[index].getNode(sub_index) * cMat::MakeMoveMatrix(getOffset(index).x,getOffset(index).y);
			Point second = prob.pieces[index].getNode((sub_index+1)%prob.pieces[index].size()) * cMat::MakeMoveMatrix(getOffset(index).x,getOffset(index).y);
			cv::circle(img,cv::Point(first.x,first.y),5,cv::Scalar(0,0,255),2);
			cv::line  (img,cv::Point(first.x,first.y),cv::Point(second.x,second.y),cv::Scalar(255,0,0),2);
			auto p = LengthDeproyment(problem.pieces(),prob.pieces[index].getNode(sub_index));
			for(int i)
		}


		cv::imshow("Deproyment", img);
		cv::waitKey(1);
	}

}
