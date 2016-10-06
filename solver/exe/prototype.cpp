
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <structure/Problem.h>
#include <util/Console.h>
#include <capture/MatIO.h>
#include <string>

bool CheckHitKey(int key,char c);
void cvPointToPoint(cv::Point &cvpoint, Point &point);


int main(){
	
	int device = 0;
	std::cout << "デバイス番号を入力>>";
	std::cin >> device;
	std::string image_file;
	cv::VideoCapture cap;
	Problem problem;
	cv::Point center_pos[2];
	center_pos[0].x = center_pos[0].x = 0;
	center_pos[0].y = center_pos[0].y = 0;

	cv::namedWindow("window", CV_WINDOW_AUTOSIZE);
	cv::setMouseCallback("window", my_mouse_callback, (void*)center_pos);

	//カメラデバイスが正常にオープンしたか確認．
	if(device == -1){
		std::cout << "ファイルオープンモード" << std::endl;
		std::cout << "ファイル名>";
		std::cin  >> image_file;
	}else{
		cap = cv::VideoCapture(device);//デバイスのオープン
		if(!cap.isOpened()){	
			std::cout << "カメラ起動失敗" << std::endl;
			return -1;
		}
	}

	int mode = 0;
	int value1 = 100;
	int value2 =80;
	int limit_range = 50;
	
	Console::ClearScreen(0);
	Console::SetCursorPos(0,0);
	std::cout << "==================================================\n"
				 "=                   PROTOTYPE                    =\n"
				 "==================================================\n"
				 "=  q:exit               [:value1 up              =\n"
				 "=  s:save               ]:value1 down            =\n"
				 "=  t:threshold          @:value2 up              =\n"
				 "=  p:pause              ::value2 down            =\n"
				 "=                       p:limit_range up         =\n"
				 "=                       ;:limit_range down       =\n"
				 "==================================================\n"
				 "=   Mode:               limit_range:             =\n"
				 "= value1:                                        =\n"
				 "= value2:                                        =\n"
				 "=    key:                                        =\n"
				 "=polygon:                                        =\n"
				 "==================================================\n"
				 "=LOG                                              \n"
				 "                                                  \n"
				 "                                                  \n"
				 "                                                  \n"
				 "                                                  \n"
				 "                                                  \n"
				 "==================================================\n";

	cv::Mat origin,frame,gray,thre1,thre2,thre0;
	bool nutoral = true;
	origin = cv::imread (image_file);
	if (device == -1 && origin.empty()) {
		std::cout << "file not found !" << std::endl;
		return -1;
	}

		while(1)//無限ループ
	{	
		//カメラ画像取得、サイズ変換
 		if(device != -1)cap >> origin;
		resize(origin,frame,cv::Point(), 1.0, 1.0);


        //グレースケール
		cvtColor(frame, gray, CV_BGR2GRAY);
		//二値化
		if (mode == 0) {
			cv::threshold(gray, thre1, value1, 255, cv::THRESH_BINARY);
			cv::threshold(gray, thre2, value2, 255, cv::THRESH_BINARY);
		}
		else if (mode == 1) {
			cv::threshold(gray, thre1, value1, 255, cv::THRESH_BINARY_INV);
			cv::threshold(gray, thre2, value2, 255, cv::THRESH_BINARY_INV);
		}

		cv::bitwise_xor(thre1,thre2,thre0);

		//表示
		cv::imshow("thre1",thre1);
		cv::imshow("thre2",thre2);
		cv::imshow("thre0",thre0);

		//色域でフィルターをかける
		cv::Mat d_filter(frame.rows, frame.cols, CV_8UC1);
		for(int i=0; i < d_filter.cols; i++){
			for(int j=0; j < d_filter.rows; j++){
				if(ColorDistance(GetPixcel(frame, center_pos[0].y, center_pos[0].x), GetPixcel(frame, j,i)) < limit_range){
					d_filter.at<unsigned char>(j, i) = 255;
				}else{
					d_filter.at<unsigned char>(j, i) = 0;					
				}
			}
		}
		cv::imshow("d_filter", d_filter);//画像を表示．

		//輪郭の座標リスト
		std::vector<std::vector<cv::Point>> contours;
		//輪郭の取得
		cv::findContours(thre0, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		//検出された輪郭線を緑で描画
		//cv::drawContours(frame, contours, -1, cv::Scalar(0, 255, 0));

		//直線近似
		std::vector<std::vector<cv::Point>> approxes;
		for(auto contour = contours.begin(); contour != contours.end(); contour++){
			std::vector<cv::Point> approx;

			//輪郭を直線近似する
			cv::approxPolyDP(cv::Mat(*contour), approx, 3.0, true);
			if(approx.size() >= 3){
				approxes.push_back(approx);
				//近似した輪郭線を青で描画
				cv::polylines(frame, approx, true, cv::Scalar(255, 0, 0));
			}
			
		}


		//キー取得
		int key = cv::waitKey(1);
		
		if(CheckHitKey(key,'q')){
			//whileループから抜ける．
			break;
		}
		else if(CheckHitKey(key,'s') && nutoral){

			//Problem型に変換
			std::string ans;
			Console::SetCursorPos(0,15);
			std::cout << "フレームあり?(Y/N)->";
			std::cin >> ans;
			if(ans == "y" || ans == "Y"){
				double max_area;
				auto max_area_contour = approxes.begin();
				for(int i = 0; i < 2; i++){
					max_area_contour = approxes.begin();
					max_area = contourArea(*max_area_contour);
					for(auto approx = approxes.begin() + 1; approx != approxes.end(); approx++){
						if(contourArea(*approx) > max_area){
							max_area = contourArea(*approx);
							max_area_contour = approx;
						}
					}
					if(i == 1){
						//Polygonに変換
						Polygon polygon;
						for(auto ite = (*max_area_contour).begin(); ite != (*max_area_contour).end(); ite++){
							Point v;
							cvPointToPoint(*ite, v);
							polygon.addNode(v);
						}
						problem.frame = polygon;
						cv::polylines(frame, *max_area_contour, true, cv::Scalar(0, 255, 0));
					}
					approxes.erase(max_area_contour);
				}
			}

			problem.pieces.erase(problem.pieces.begin(),problem.pieces.end());
			for(auto approx = approxes.begin(); approx != approxes.end(); approx++){
				//Polygonに変換
				Polygon polygon;
				for(auto ite = (*approx).begin(); ite != (*approx).end(); ite++){
					Point v;
					cvPointToPoint(*ite, v);
					polygon.addNode(v);
				}
				problem.pieces.push_back(polygon);
				
			}


			//ピースの頂点情報の出力.
			std::ofstream ofs("polygon_out.txt");
			for(int i=0;i<problem.pieces.size();i++){
				ofs << problem.pieces[i] << std::endl;
			}
			ofs.close();

			//フレーム画像を保存する.
			std::string filename;
			Console::SetCursorPos(0,16);
			std::cout << "ファイル名入力->";
			std::cin  >> filename;


			if(filename + ".png" != image_file){
				cv::imwrite(filename + ".png", frame);
				cv::imwrite(filename + "_origin.png", origin);
				std::cout << "セーブ完了[" << filename << ".png][" << filename << "_origin.png]" << std::endl;
			}else{
				std::cout << "上書きは勘弁して" << std::endl;
			}

			key = -1;
		}else if (CheckHitKey(key,'t')){
			//二値化
			mode++;
			mode %= 2;
		}else if(CheckHitKey(key,'[')){
			//増加
			value1+=1;
		}else if(CheckHitKey(key,']')){
			//減少
			value1-=1;
		}else if(CheckHitKey(key,'@')){
			//増加
			value2+=1;
		}else if(CheckHitKey(key,':')){
			//減少
			value2-=1;
		}else if(CheckHitKey(key, 'p')){
			limit_range++;
		}else if(CheckHitKey(key, ';')){
			limit_range--;
		}
		//キー解放
		if(key == -1){
			nutoral = true;
		}else{
			nutoral = false;
		}

		//描画
		Console::SetCursorPos(10,11);
		std::cout << mode << "   ";
		Console::SetCursorPos(10,12);
		std::cout << value1 << "   ";
		Console::SetCursorPos(10,13);
		std::cout << value2 << "   ";
		Console::SetCursorPos(10,14);
		std::cout << key << "      ";
		Console::SetCursorPos(10, 15);
		std::cout << problem.pieces.size() <<"   ";
		Console::SetCursorPos(37,11);
		std::cout << limit_range << "   ";
		Console::SetCursorPos(0,25);


		std::cout << std::flush;

		cv::imshow("window", frame);//画像を表示．

		//cv::waitKey(0);
	}
	cv::destroyAllWindows();
	return 0;
}


bool CheckHitKey(int key,char c){
	return key == (c-'a' + 97);
	//return key == (c-'a' + 1048673);
}

void cvPointToPoint(cv::Point &cvpoint, Point &point){
	point.x = cvpoint.x;
	point.y = cvpoint.y;
}

