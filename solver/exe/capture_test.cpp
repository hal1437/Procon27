
#include <iostream>
#include <opencv2/opencv.hpp>
#include <util/Console.h>
#include <string>


bool CheckHitKey(int key,char c);


int main(){
	
	int device = 0;
	std::cout << "デバイス番号を入力>>";
	std::cin >> device;
	std::string image_file;
	cv::VideoCapture cap;

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
	int value = 100;
	
	Console::ClearScreen(0);
	Console::SetCursorPos(0,0);
	std::cout << "==================================================\n"
				 "=                 CAPTURE_TEST                   =\n"
				 "==================================================\n"
				 "=  q:exit               [:value up               =\n"
				 "=  s:save               ]:value down             =\n"
				 "=  t:threshold                                   =\n"
				 "==================================================\n"
				 "=   Mode:                                        =\n"
				 "=  value:                                        =\n"
				 "=    key:                                        =\n"
				 "==================================================\n"
				 "=LOG                                              \n"
				 "                                                  \n"
				 "                                                  \n"
				 "                                                  \n"
				 "                                                  \n"
				 "                                                  \n"
				 "==================================================\n";

	cv::Mat origin,frame,gray,thre;
	bool nutoral = true;
	origin = cv::imread (image_file);
	while(1)//無限ループ
	{

		//カメラ画像取得、サイズ変換
 		if(device != -1)cap >> origin;
		resize(origin,frame,cv::Point(), 0.5, 0.5);


		//二値化
		if(mode == 1){
			cvtColor(frame , gray , CV_BGR2GRAY);
			cv::threshold(gray, thre, value, 255, cv::THRESH_BINARY);
			cv::imshow("Thereshold",thre);
			cv::destroyWindow("Gray Scale");
		}else if(mode == 2){
			cvtColor(frame , gray , CV_BGR2GRAY);
			cv::imshow("Gray Scale",gray);
			cv::destroyWindow("Thereshold");
		}else{
			cv::destroyWindow("Thereshold");
			cv::destroyWindow("Gray Scale");
		}


		//キー取得
		int key = cv::waitKey(1);
		
		if(CheckHitKey(key,'q'))
		{
			//whileループから抜ける．
			break;
		}
		else if(CheckHitKey(key,'s') && nutoral)
		{
			//フレーム画像を保存する．
			std::string filename;

			Console::SetCursorPos(0,15);
			std::cout << "ファイル名入力";
			std::cin  >> filename;


			if(filename + ".png" != image_file){
				cv::Mat out;
				if     (mode == 1)out = thre;
				else if(mode == 2)out = gray;
				else              out = frame;
				cv::imwrite(filename + ".png", out);
				std::cout << "セーブ完了[" << filename << ".png]" << std::endl;
			}else{
				std::cout << "上書きは勘弁して" << std::endl;
			}

			key = -1;
		}else if (CheckHitKey(key,'t')){
			//二値化
			mode++;
			mode %= 3;
		}else if(CheckHitKey(key,'[')){
			//増加
			value+=5;
		}else if(CheckHitKey(key,']')){
			//減少
			value-=5;
		}
		//キー解放
		if(key == -1){
			nutoral = true;
		}else{
			nutoral = false;
		}

		//描画
		Console::SetCursorPos(10,8);
		std::cout << mode << "   ";
		Console::SetCursorPos(10,9);
		std::cout << value << "   ";
		Console::SetCursorPos(10,10);
		std::cout << key << "      ";
		Console::SetCursorPos(0,20);

		std::cout << std::flush;

		cv::imshow("window", frame);//画像を表示．
	}
	cv::destroyAllWindows();
	return 0;
}


bool CheckHitKey(int key,char c){
	return key == (c-'a' + 1048673);
}
