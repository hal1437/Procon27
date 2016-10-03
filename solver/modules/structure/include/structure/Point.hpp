
#pragma once
#include <structure/Point.h>

template <class Type>
_Point<Type>::_Point():x(0),y(0){
}
template <class Type>
_Point<Type>::_Point(const Type& init):x(init),y(init){
}
template <class Type>
_Point<Type>::_Point(const Type& _x,const Type& _y):x(_x),y(_y){
}

//演算子のオーバーロード
template <class Type>
_Point<Type> _Point<Type>::operator+(const _Point<Type>& rhs)const{
	return _Point(this->x + rhs.x, this->y + rhs.y);
}
template <class Type>
_Point<Type> _Point<Type>::operator-(const _Point<Type>& rhs)const{
	return _Point(this->x - rhs.x, this->y - rhs.y);
}
template <class Type>
_Point<Type> _Point<Type>::operator+(const Type& rhs)const{
	return _Point(this->x + rhs, this->y + rhs);
}
template <class Type>
_Point<Type> _Point<Type>::operator-(const Type& rhs)const{
	return _Point(this->x - rhs, this->y - rhs);
}
template <class Type>
_Point<Type> _Point<Type>::operator*(const Type& rhs)const{
	return _Point(this->x * rhs, this->y * rhs);
}
template <class Type>
_Point<Type> _Point<Type>::operator/(const Type& rhs)const{
	return _Point(this->x / rhs, this->y / rhs);
}

template <class Type>
_Point<Type>& _Point<Type>::operator+=(const _Point<Type>& rhs)const{
	this->x += rhs.x;
	this->y += rhs.y;
	return (*this);
}
template <class Type>
_Point<Type>& _Point<Type>::operator-=(const _Point<Type>& rhs)const{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return (*this);
}
template <class Type>
_Point<Type>& _Point<Type>::operator+=(const Type& rhs)const{
	this->x += rhs;
	this->y += rhs;
	return (*this);
}
template <class Type>
_Point<Type>& _Point<Type>::operator-=(const Type& rhs)const{
	this->x -= rhs;
	this->y -= rhs;
	return (*this);
}
template <class Type>
_Point<Type>& _Point<Type>::operator*=(const Type& rhs)const{
	this->x *= rhs;
	this->y *= rhs;
	return (*this);
}
template <class Type>
_Point<Type>& _Point<Type>::operator/=(const Type& rhs)const{
	this->x /= rhs;
	this->y /= rhs;
	return (*this);
}
template <class Type>
bool _Point<Type>::operator< (const _Point<Type>& rhs)const{
	if(this->x == rhs.x)return (this->y < rhs.y);
	else return (this->x == rhs.x);
}
template <class Type>
bool _Point<Type>::operator==(const _Point<Type>& rhs)const{
	return (this->x == rhs.x && this->y == rhs.y);
}


template <class Type>
bool _Point<Type>::Norm(){
	if(this->x == 0 && this->y ==0)return false;
	else{
		this->x = this->x / this->size();
		this->y = this->y / this->size();
		return true;
	}
}
template <class Type>
_Point<Type> _Point<Type>::getNorm()const{
	_Point<Type> answer(*this);
	answer.Norm();
	return answer;
}
template <class Type>
bool _Point<Type>::Rotate(double angle){
	Type x_n =  std::cos(angle) * this->x - std::sin(angle) * this->y;
	Type y_n =  std::sin(angle) * this->x + std::cos(angle) * this->y;
	this->x = x_n;
	this->y = y_n;
	return true;
}
template <class Type>
_Point<Type> _Point<Type>::getRotate(double angle)const{
	_Point<Type> answer(*this);
	answer.Rotate(angle);
	return answer;
}

template <class Type>
double _Point<Type>::size()const{
	return std::sqrt(std::pow(this->x,2) + std::pow(this->y,2));
}
template <class Type>
double _Point<Type>::innerProduct(const _Point<Type>& rhs)const{
	return this->x * rhs.x + this->y * rhs.y;
}
template <class Type>
double _Point<Type>::angle(const _Point<Type>& rhs)const{
	double answer = std::acos(this->innerProduct(rhs)/(this->size()*rhs.size()));
	return answer;
}

template <class Type>
void _Point<Type>::Print(std::ostream& ost)const{
	ost << "(" << x << "," << y << ")";
}


template <class Type>
double _Point<Type>::getAngle2Vec(const _Point<Type>& v1,const _Point<Type>& v2){
	if(v1==_Point<Type>() || v2==_Point<Type>())return 0;
	//極座標変換
	double delta = 0;
	double sita1 = (v1.y>0 ? std::acos(v1.x/v1.size()) : -std::acos(v1.x/v1.size())); //(-PI < θ_1 < PI)
	double sita2 = (v2.y>0 ? std::acos(v2.x/v2.size()) : -std::acos(v2.x/v2.size())); //(-PI < θ_2 < PI)
	if(sita1 > sita2)delta = sita1 - sita2;
	if(sita1 < sita2)delta = sita1 - sita2 + 2*M_PI;
	return delta;
}

