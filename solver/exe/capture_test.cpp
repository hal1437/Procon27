
#include <iostream>
#include <opencv2/opencv.hpp>


int main(){
	
	int device = 0;
	std::cout << "デバイス番号を入力>>";
	std::cin >> device;
	cv::VideoCapture cap(device);//デバイスのオープン
	//cap.open(0);//こっちでも良い．

	if(!cap.isOpened())//カメラデバイスが正常にオープンしたか確認．
	{
		//読み込みに失敗したときの処理
		std::cout << "カメラ起動失敗" << std::endl;
		return -1;
	}



	int mode = 0;
	int thre_mode = 0;
	int value = 100;
	while(1)//無限ループ
	{
		cv::Mat origin,frame,gray,thre;

		cap >> origin; // get a new frame from camera
		resize(origin,frame,cv::Point(), 0.3, 0.3);

		//
		//取得したフレーム画像に対して，クレースケール変換や2値化などの処理を書き込む．
		//

		if(thre_mode){
			
			cvtColor(frame , gray , CV_BGR2GRAY);
			cv::threshold(gray, thre, value, 255, cv::THRESH_BINARY);
			cv::imshow("Thereshold",thre);
		}
		cv::imshow("window", frame);//画像を表示．
		int key = cv::waitKey(1);
		if(key == 'q'-'a' + 97)//qボタンが押されたとき
		{
			break;//whileループから抜ける．
		}
		else if(key == 's'-'a' + 97)//sが押されたとき
		{
			//フレーム画像を保存する．
			cv::imwrite("img.png", frame);
		}else if (key == 'm'-'a' + 97){
			//二値化
			thre_mode = 1;
		}else if(key == 'w'-'a' + 97){
			//増加
			value+=5;
			std::cout << "value:" << value << std::endl;
		}else if(key == 'e'-'a' + 97){
			//減少
			value-=5;
			std::cout << "value:" << value << std::endl;
		}

	}
	cv::destroyAllWindows();
	return 0;
}
