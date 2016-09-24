
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <structure/Problem.h>
#include <util/Console.h>
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
	
	Console::ClearScreen(0);
	Console::SetCursorPos(0,0);
	std::cout << "==================================================\n"
				 "=                   PROTOTYPE                    =\n"
				 "==================================================\n"
				 "=  q:exit               [:value1 up              =\n"
				 "=  s:save               ]:value1 down            =\n"
				 "=  t:threshold          @:value2 up              =\n"
				 "=  p:pause              ::value2 down            =\n"
				 "==================================================\n"
				 "=   Mode:                                        =\n"
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
	bool pause = false;
	origin = cv::imread (image_file);
	if (device == -1 && origin.empty()) {
		std::cout << "file not found !" << std::endl;
		return -1;
	}

		while(1)//無限ループ
	{	
		//カメラ画像取得、サイズ変換
 		if(device != -1 && !pause)cap >> origin;
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

		//輪郭の座標リスト
		std::vector<std::vector<cv::Point>> contours;
		//輪郭の取得
		cv::findContours(thre0, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		//検出された輪郭線を緑で描画
		//cv::drawContours(frame, contours, -1, cv::Scalar(0, 255, 0));

		//直線近似
		problem.pieces.erase(problem.pieces.begin(),problem.pieces.end());
		for(auto contour = contours.begin(); contour != contours.end(); contour++){
			std::vector<cv::Point> approx;
			Polygon polygon;

			//輪郭を直線近似する
			cv::approxPolyDP(cv::Mat(*contour), approx, 3.0, true);
			for(auto ite = approx.begin(); ite != approx.end(); ite++){
				Point v;
				cvPointToPoint(*ite, v);
				polygon.addNode(v);
			}
			if(polygon.size()>=3){
				problem.pieces.push_back(polygon);
				//近似した輪郭線を青で描画
				cv::polylines(frame, approx, true, cv::Scalar(255, 0, 0));
			}
			
		}


		//キー取得
		int key = cv::waitKey(1);
		
		if(CheckHitKey(key,'q')){
			//whileループから抜ける．
			break;
		}else if(CheckHitKey(key, 'p')){
			pause = !pause;
		}
		else if(CheckHitKey(key,'s') && nutoral){
			//ピースの頂点情報の出力.
			std::ofstream ofs("polygon_out.txt");
			for(int i=0;i<problem.pieces.size();i++){
				ofs << problem.pieces[i] << std::endl;
			}
			ofs.close();

			//フレーム画像を保存する.
			std::string filename;
			Console::SetCursorPos(0,15);
			std::cout << "ファイル名入力";
			std::cin  >> filename;


			if(filename + ".png" != image_file){
				cv::imwrite(filename + ".png", frame);
				std::cout << "セーブ完了[" << filename << ".png]" << std::endl;
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
		}
		//キー解放
		if(key == -1){
			nutoral = true;
		}else{
			nutoral = false;
		}

		//描画
		Console::SetCursorPos(10,9);
		std::cout << mode << "   ";
		Console::SetCursorPos(10,10);
		std::cout << value1 << "   ";
		Console::SetCursorPos(10,11);
		std::cout << value2 << "   ";
		Console::SetCursorPos(10,12);
		std::cout << key << "      ";
		Console::SetCursorPos(10, 13);
		std::cout << problem.pieces.size() <<"   ";
		Console::SetCursorPos(0,23);


		std::cout << std::flush;

		cv::imshow("window", frame);//画像を表示．

		//cv::waitKey(0);
	}
	cv::destroyAllWindows();
	return 0;
}


bool CheckHitKey(int key,char c){
	//return key == (c-'a' + 97);
	return key == (c-'a' + 1048673);
}

void cvPointToPoint(cv::Point &cvpoint, Point &point){
	point.x = cvpoint.x;
	point.y = cvpoint.y;
}

