
#include <structure/Polygon.h>
#include <iostream>



//正規化
bool Polygon::normalize(){
	//第一頂点を原点とし、第二頂点を(1,0)方向へ回転させる
	return 0;
}

//面積算出
double Polygon::getArea()const{
	//ググって探す
	return 0;
}


//頂点追加
size_t Polygon::size()const{
	return this->v.size();
}

//頂点抽出
Point Polygon::getNode(int index)const{
	if(index < 0 || this->v.size() <= index){
		//範囲外であれば
		std::cout << "[Polygon.cpp] Index overran in Polygon::getPoint" << std::endl;
		return Point();
	}else{
		return this->v[index];
	}

}
//頂点追加
bool Polygon::addNode(const Point& p){
	this->v.push_back(p);
	return true;
}
bool Polygon::addNode(size_t index,const Point& p){
	this->v.insert(v.begin()+index,p);
	return true;
}
//頂点設定
bool Polygon::setNode(int index,const Point& pos){
	if(index < 0 || this->v.size() <= index){
		std::cout << "[Polygon.cpp] Index overran in Polygon::setPoint" << std::endl;
		return false;
	}else{
		this->v[index] = pos;
		return true;
	}
}
void Polygon::Print(std::ostream& ost)const{
	ost << "vertex:" << this->v.size() << std::endl;
	for(int i=0;i<this->v.size();i++){
		ost << i << "." << v[i] << std::endl;
	}
}



