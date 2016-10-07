
#include <Deproyment.h>

double Deproyment::Length(const Polygon& p,int index,bool Rev){
	int index_p = (index+p.size()-1) % p.size();
	int index_n = (index+1) % p.size();
	if(Rev)return (p.getNode(index) - p.getNode(index_p)).size();
	else   return (p.getNode(index) - p.getNode(index_n)).size();

}
double Deproyment::Angle (const Polygon& p,int index,bool Rev){
	int j_p = (index+p.size()-1) % p.size();
	int j_n = (index+1         ) % p.size();
	if(Rev)return Point::getAngle2Vec(p.getNode(j_n)-p.getNode(index),p.getNode(j_p)-p.getNode(index));
	else   return Point::getAngle2Vec(p.getNode(j_p)-p.getNode(index),p.getNode(j_n)-p.getNode(index));
}

std::vector<Deproyment::result> Deproyment::Solver(std::vector<Polygon> list){
	std::vector<Deproyment::result>	 ans;
	//長さ角度が規定値以下

	//全て正規化
	for(Polygon& p:list) p.normalize();

	for(int k = 0;k<base.size();k++){
		double base_length = Length(base,k);
		double base_angle  = Angle (base,k);
		for(int i=0;i<list.size();i++){
			for(int j=0;j<list[i].size();j++){
				for(int rev =0;rev<2;rev++){
					Polygon p = list[i];
					if(rev)p = list[i].getReverse();
					double length      = Length(list[i],j,rev);
					double angle       = Angle (list[i],j,rev);
					
					//規定値以下
					if(std::abs(base_length - length) < LENGTH_EPS ||
					std::abs(base_angle + angle - M_PI * (1/2) ) < ANGLE_EPS ||
					std::abs(base_angle + angle - M_PI * (2/2) ) < ANGLE_EPS ||
					std::abs(base_angle + angle - M_PI * (3/2) ) < ANGLE_EPS ||
					std::abs(base_angle + angle - M_PI * (4/2) ) < ANGLE_EPS){
						Polygon p_re ;
						if(rev==1)p_re = list[i];
						else      p_re = list[i].getReverse();
						result res;
						TransParam param;
						param.sub_index = j;
						param.pos       = base.getNode(k);
						param.reverse   = !rev;
						if(rev){
							param.angle     = Point::getAngle2Vec(base.getNode((k            +1)%base.size())-base.getNode(k),
						                                          p_re.getNode((j+p_re.size()-1)%p_re.size())-p_re.getNode(j));
						}else{
							param.angle     = Point::getAngle2Vec(base.getNode((k+1)%base.size())-base.getNode(k),
							                                      p_re.getNode((j+1)%p_re.size())-p_re.getNode(j));
						}
						res.trans = param;
						res.length_diff = std::abs(length - base_length);
						res.angle_sum[0] = angle + base_angle;
						res.angle_sum[1] = 0;
						res.index = i;
						ans.push_back(res);
					}
				}
			}
		}
	}

	return ans;
}



void Deproyment::Run(std::vector<Polygon> list){

	//ベースを中心に展開、キーで候補入れ替え
	std::cout << "==================== DEPROYMENT ====================" << std::endl;
	std::vector<Deproyment::result> res = Solver(list);
	if(res.size() == 0){
		std::cout << "===================== NOTFOUND =========================" << std::endl;
		return;
	}
	int key=-1;
	int index=0;
	while(1){
		cv::Mat img = cv::Mat::zeros(600, 800, CV_8UC3);
		
		//ベースライン
		Point frame_offset(400,200);
		for(int i=0;i<base.size();i++){
			Point p1 = base.getNode(i)+frame_offset;
			Point p2 = base.getNode((i+1) % base.size())+frame_offset;
			cv::line(img, cv::Point(p1.x, p1.y), cv::Point(p2.x, p2.y), cv::Scalar(0,(i+1)*30,255), 1, CV_AA); 
		}

// 		img << base * cMat::MakeMoveMatrix(400,200);
		img << list[res[index].index] * cMat::MakeMoveMatrix(600,200);
		img << BasicSearch::Transform(list[res[index].index],res[index].trans)*cMat::MakeMoveMatrix(400,200);
		putText(img,std::string("Length:") + std::to_string(res[index].length_diff          ),cv::Point(0,20),cv::FONT_HERSHEY_SIMPLEX,0.6,cv::Scalar(255,255,255));
		putText(img,std::string("Angle0:") + std::to_string(res[index].angle_sum[0]*180/M_PI),cv::Point(0,40),cv::FONT_HERSHEY_SIMPLEX,0.6,cv::Scalar(255,255,255));
		putText(img,std::string("Angle1:") + std::to_string(res[index].angle_sum[1]*180/M_PI),cv::Point(0,60),cv::FONT_HERSHEY_SIMPLEX,0.6,cv::Scalar(255,255,255));
		putText(img,std::string("Index:") + std::to_string(res[index].index                ),cv::Point(0,80),cv::FONT_HERSHEY_SIMPLEX,0.6,cv::Scalar(255,255,255));

		cv::imshow("Deproyment", img);
		key = cv::waitKey(0);
		if(key == 63234)index--;  //左矢印キー
		if(key == 63235)index++;  //右矢印キー
		index = std::max(0         ,index);
		index = std::min(static_cast<int>(res.size())-1,index);
	}
	std::cout << "======================= END =========================" << std::endl;

}