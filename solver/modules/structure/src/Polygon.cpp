
#include <structure/Polygon.h>
#include <iostream>
#include <util/NearlyEqual.h>
#include <algorithm>

//正規化
bool Polygon::normalize(){
	//第一頂点を原点とし、第二頂点を(1,0)方向へ回転させ、第三頂点を下側へ
	
	//平行移動変換
	Point origin = this->getNode(0);
	for(int i=0;i<this->size();i++){
		this->setNode(i,this->getNode(i) - origin);
	}

	//回転変換
	double angle = Point::getAngle2Vec(Point(-1,0),this->getNode(1));
	for(int i=0;i<this->size();i++){
		this->setNode(i,this->getNode(i).getRotate(angle));
	}

	//反転変換
	if(this->getNode(1).x<0){
		for(int i=0;i<this->size();i++){
			this->setNode(i,Point(-this->getNode(i).x,this->getNode(i).y));
		}
	}
	if(this->getNode(2).y<0){
		for(int i=0;i<this->size();i++){
			this->setNode(i,Point(this->getNode(i).x,-this->getNode(i).y));
		}
	}
	return 0;
}

Polygon Polygon::getNormalize()const{
	Polygon p = (*this);
	p.normalize();
	return p;
}

//反転
bool Polygon::reverse(){
	
	//0から1へのベクトルをPoint(1,0)方向に変換
	Point base = this->getNode(0);
	double base_angle = Point::getAngle2Vec(Point(1,0),this->getNode(1)-base);

	//全ての頂点に対して回転移動しのY軸を反転
	for(int i=0;i<this->size();i++){
		this->setNode(i,this->getNode(i) - base);
		this->setNode(i,this->getNode(i).getRotate(base_angle));
		this->setNode(i,Point(this->getNode(i).x,-this->getNode(i).y));
		this->setNode(i,this->getNode(i).getRotate(-base_angle));
		this->setNode(i,this->getNode(i) + base);
	}
	return true;
}

Polygon Polygon::getReverse()const{
	Polygon p = (*this);
	p.reverse();
	return p;
}



//面積算出
double Polygon::getArea()const{
	double score=0;
	//全ての点間距離の総和
	for(int i=0;i<this->size();i++){
		int i_ = (i+1) % this->size();
		score += (this->getNode(i).x - this->getNode(i_).x) * 
		         (this->getNode(i).y + this->getNode(i_).y);
	}
	return score/2.0;
}
//角度算出
double Polygon::getAngle(int index)const{
	if(index < 0 || this->v.size() <= index){
		//範囲外であれば
		std::cout << "[Polygon.cpp] Index overran in Polygon::getAngle" << std::endl;
		return 0;
	}else{
		Point v1 = this->getNode((index + this->size() + 1)%this->size()) - this->getNode(index);
		Point v2 = this->getNode((index + this->size() - 1)%this->size()) - this->getNode(index);
		return Point::getAngle2Vec(v1,v2);
	}
}


//番号調整
bool Polygon::ConfirmNumbers(){
	double sum=0;
	for(int i=0;i<this->size();i++){
		sum += this->getAngle(i);
	}
	//多角形の角の総和が(n+2)*PIに等しくければ
	if(NE(sum , (this->size()+2) * M_PI)){
		//全て外角を示しているので番号を逆順にする。
		std::reverse(v.begin(),v.end());
	}
	//外角の総和に等しくないとなると
	else if(!NE(sum , (this->size()-2) * M_PI)){
		//さすがにきついっす
		std::cout << "[Polygon.cpp] error! This Polygon can't confirm!" << std::endl; 
		return false;
	}
	return true;
}

//内包
bool Polygon::isComprehension(const Point& p)const{
	if(std::find(v.begin(),v.end(),p) !=v.end())return true;

	double sum = 0;
	for(int i=0;i<this->size();i++){
		double angle = Point::getAngle2Vec(v[i]-p,v[(i+1)%this->size()]-p);
		if(angle > M_PI)angle = angle - 2*M_PI;
		sum += angle;
// 		std::cout << angle*180/M_PI << "[deg]" << std::endl;
	}
// 	std::cout << sum*180/M_PI << "[deg]" << std::endl;
	return (std::abs(sum*180/M_PI-360) < 0.01f);
}


//頂点追加
size_t Polygon::size()const{
	return this->v.size();
}

//頂点抽出
Point Polygon::getNode(int index)const{
	if(index < 0 || this->v.size() <= index){
		//範囲外であれば
		std::cout << "[Polygon.cpp] index = \"" << index << "\" overran in Polygon::getNode" << std::endl;
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
		std::cout << "[Polygon.cpp] index = \"" << index << "\" overran in Polygon::setNode" << std::endl;
		return false;
	}else{
		this->v[index] = pos;
		return true;
	}
}
bool Polygon::removeNode(int index){
	if(index < 0 || this->v.size() <= index){
		std::cout << "[Polygon.cpp] index = \"" << index << "\" overran in Polygon::removeNode" << std::endl;
		return false;
	}else{
		this->v.erase(v.begin()+index);
		return true;
	}
}
void Polygon::Print(std::ostream& ost)const{
	ost << "vertex:" << this->v.size() << std::endl;
	for(int i=0;i<this->v.size();i++){
		ost << i << "." << v[i] << std::endl;
	}
}



