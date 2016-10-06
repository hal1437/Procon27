
#include <Deproyment.h>

double Deproyment::Length(const Polygon& p,int index){
	int index_n = (index+1) % p.size();
	return (p.getNode(index) - p.getNode(index_n)).size();
}
double Deproyment::Angle (const Polygon& p,int index,bool Rev){
	int j_p = (index+p.size()-1) % p.size();
	int j_n = (index+1         ) % p.size();
	if(Rev)return Point::getAngle2Vec(p.getNode(j_p),p.getNode(j_n));
	else   return Point::getAngle2Vec(p.getNode(j_n),p.getNode(j_p));
}

std::vector<result> Deproyment::Solver(std::vector<Polygon> list){
	std::vector<result>	 ans;
	//長さ角度が規定値以下

	//全て正規化
	for(Polygon& p:list) p.normalize();

	for(int k = 0;k<base.size();k++){
		double base_length = Length(base,k);
		double base_angle  = Angle (base,k,true);

		for(int i=0;i<list.size();i++){
			for(int j=0;j<list[i].size();j++){
				double length = Length(list[i],j);
				double angle  = Angle (list[i],j);
				
				//規定値以下
				if(std::abs(base_length - length) < LENGTH_DIFF ||
				   std::abs(base_angle + angle - M_PI * (1/2) ) < ANGLE_EPS ||
				   std::abs(base_angle + angle - M_PI * (2/2) ) < ANGLE_EPS ||
				   std::abs(base_angle + angle - M_PI * (3/2) ) < ANGLE_EPS ||
				   std::abs(base_angle + angle - M_PI * (4/2) ) < ANGLE_EPS){
					TransParam param;
					param.sub_index = j;
					param.pos       = base.getNode(k);
					param.reverse   = false;
					param.angle     = Point::getAngle2Vec(base    .getNode((k+1)%base    .size())-base.getNode(k),
					                                      frame[i].getNode((j+1)%frame[i].size())-frame[i].getNode(j));
				}
			}
		}
	}

	return ans;
}



void Deproyment::Run(std::vector<Polygon> list){

	//ベースを中心に展開、キーで候補入れ替え
	std::cout << "==================== DEPROYMENT ====================" << std::endl;
	std::vector<result> res = Solver(list);
	while(1){

		
		
		
	}
	std::cout << "======================= END =========================" << std::endl;

}
