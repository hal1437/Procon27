#include <CaptureIO.h>

void CaptureIO::Setup(){
	for(int i = 0; i < 3; i++){
		center_pos[i] = cv::Point(0,0);
	}

	seacher = [](Problem){return;};
	deproymenter = [](Problem, int){return;};

	cv::namedWindow("window", CV_WINDOW_AUTOSIZE);
}
CaptureIO::CaptureIO(int device){
	Setup();
	this->device = device;
	this->resource_mode = false;
	
}
CaptureIO::CaptureIO(std::string resource){
	Setup();
	this->resource = resource;
	this->resource_mode = true;
}

bool CaptureIO::CheckHitKey(int key,char c){
	return key == (c-'a' + 97);
}

void CaptureIO::SetExpansion(double expansion){
	this->expansion = expansion;	
}

cv::Mat CaptureIO::Threshold(cv::Mat origin){
	cv::Mat gray, thre0, thre1, thre2 ;
	//グレースケール
	cvtColor(origin, gray, CV_BGR2GRAY);
	//二値化
	cv::threshold(gray, thre1, value1, 255, cv::THRESH_BINARY);
	cv::threshold(gray, thre2, value2, 255, cv::THRESH_BINARY);
	
	cv::bitwise_xor(thre1,thre2,thre0);
	
	//表示
	//cv::imshow("thre1",thre1);
	//cv::imshow("thre2",thre2);
	//cv::imshow("thre0",thre0);
	return thre0;
}

cv::Mat CaptureIO::ColorGamut(cv::Mat origin){
	//色域でフィルターをかける
	cv::Mat d_filter(origin.rows, origin.cols, CV_8UC1);
	for(int i=0; i < d_filter.rows; i++){
		for(int j=0; j < d_filter.cols; j++){
			if(ColorDistance(GetPixcel(frame, center_pos[0]), GetPixcel(frame, j,i)) < limit_range || 
			   ColorDistance(GetPixcel(frame, center_pos[1]), GetPixcel(frame, j,i)) < limit_range || 
			   ColorDistance(GetPixcel(frame, center_pos[2]), GetPixcel(frame, j,i)) < limit_range)
			{
				SetPixcel(d_filter, j, i, 255);
			}else{
				SetPixcel(d_filter, j, i, 0);
			}
		}
	}
	//表示
	//cv::imshow("d_filter", d_filter);
	return d_filter;
}

std::vector<std::vector<cv::Point>> CaptureIO::ContourApprox(cv::Mat origin){
	//輪郭の取得
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(origin, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	//直線近似
	std::vector<std::vector<cv::Point>> approxes;
	for(auto contour = contours.begin(); contour != contours.end(); contour++){
		std::vector<cv::Point> approx;

		//輪郭を直線近似する
		cv::approxPolyDP(cv::Mat(*contour), approx, accuracy, true);
		if(approx.size() >= 3){
			approxes.push_back(approx);
			//近似した輪郭線を青で描画
			cv::polylines(frame, approx, true, cv::Scalar(255, 0, 0));
		}
		
	}

	return approxes;
}

Problem CaptureIO::toProbrem(std::vector<std::vector<cv::Point>> approxes){
	//Problem型に変換
	Problem problem;
	std::string ans;
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

	return problem;
}

void CaptureIO::cvPointToPoint(cv::Point &cvpoint, Point &point){
	point.x = cvpoint.x;
	point.y = cvpoint.y;
}

void my_mouse_callback(int event, int x, int y, int flags, void* param){
	cv::Point *point = static_cast<cv::Point*>(param);

	if(event == cv::EVENT_LBUTTONDOWN){
		if(point[2] == cv::Point(0,0)){
			point[2] = point[1] = point[0] = cv::Point(x, y);
		}else{
			point[2] = point[1];
   			point[1] = point[0];
   			point[0] = cv::Point(x, y);
		}
   		
	}
}

void CaptureIO::Run(){

	cv::setMouseCallback("window", my_mouse_callback, (void*)center_pos);
	
	Console::ClearScreen(0);
	Console::SetCursorPos(0,0);
	std::cout << "==================================================\n"
				 "=                   PROTOTYPE                    =\n"
				 "==================================================\n"
				 "=  q:exit               [:value1 up              =\n"
				 "=  s:save               ]:value1 down            =\n"
				 "=  m:mode change        @:value2 up              =\n"
				 "=                       ::value2 down            =\n"
				 "=  o:accuracy_up        p:limit_range up         =\n"
				 "=  l:accuracy_down      ;:limit_range down       =\n"
				 "==================================================\n"
				 "=   Mode:               limit_range:             =\n"
				 "= value1:               accuracy                 =\n"
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

	if(resource_mode){
		origin = cv::imread (resource);
		if (origin.empty()) {
			std::cout << "file not found !" << std::endl;
			return;
		}
	}else{
		//カメラデバイスが正常にオープンしたか確認．
		cap = cv::VideoCapture(device);//デバイスのオープン
		if(!cap.isOpened()){	
			std::cout << "カメラ起動失敗" << std::endl;
			return;
		}

	}

		while(1)//無限ループ
	{	
		//カメラ画像取得、サイズ変換
 		if(!resource_mode)cap >> origin;
		resize(origin,frame,cv::Point(), expansion, expansion);

		//輪郭の座標リスト
		std::vector<std::vector<cv::Point>> contours;
		if(mode == 0){
			cv::Mat d_filter = this->ColorGamut(frame); //色域でフィルタ
			contours = this->ContourApprox(d_filter);
		}else if(mode == 1){
			cv::Mat thre = this->Threshold(frame); //二値化する
			contours = this->ContourApprox(thre);
		}


		//キー取得
		int key = cv::waitKey(1);
		
		if(CheckHitKey(key,'q')){
			//whileループから抜ける．
			break;
		}
		else if(CheckHitKey(key,'s')){

			Problem problem = toProbrem(contours);
			seacher(problem);
/*
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


			if(filename + ".png" != resource){
				cv::imwrite(filename + ".png", frame);
				cv::imwrite(filename + "_origin.png", origin);
				std::cout << "セーブ完了[" << filename << ".png][" << filename << "_origin.png]" << std::endl;
			}else{
				std::cout << "上書きは勘弁して" << std::endl;
			}
*/
		}else if (CheckHitKey(key,'m')){
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
		}else if(CheckHitKey(key, 'o')){
			accuracy+=0.1;
		}else if(CheckHitKey(key, 'l')){
			accuracy-=0.1;
		}else if(CheckHitKey(key, 'd')){
			int index;
			std::cout << "ピース番号->";
			std::cin >> index;
			Problem problem = toProbrem(contours);
			//deproymenter(problem, index); 
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
		std::cout << contours.size() <<"   ";
		Console::SetCursorPos(37,11);
		std::cout << limit_range << "   ";
		Console::SetCursorPos(37,12);
		std::cout << accuracy << "   ";
		Console::SetCursorPos(0,25);


		std::cout << std::flush;

		cv::imshow("window", frame);//画像を表示．
		cv::imshow("window", frame);//画像を表示．
		cv::imshow("window", frame);//画像を表示．

		//cv::waitKey(0);
	}
	cv::destroyAllWindows();
	return;
}

void CaptureIO::SetSeacher(std::function<void(Problem)> seacher){
	this->seacher = seacher;
}

void CaptureIO::SetDeproymenter(std::function<void(Problem, int)> deproymenter){
	this->deproymenter = deproymenter;
}
