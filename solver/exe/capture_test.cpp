
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>


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
	while(1)//無限ループ
	{
		cv::Mat frame;
		cap >> frame; // get a new frame from camera

		//
		//取得したフレーム画像に対して，クレースケール変換や2値化などの処理を書き込む．
		//

		cv::imshow("window", frame);//画像を表示．

		int key = cv::waitKey(1);
		if(key == 113)//qボタンが押されたとき
		{
			break;//whileループから抜ける．
		}
		else if(key == 115)//sが押されたとき
		{
			//フレーム画像を保存する．
			cv::imwrite("img.png", frame);
		}
	}
	cv::destroyAllWindows();
	return 0;
}
