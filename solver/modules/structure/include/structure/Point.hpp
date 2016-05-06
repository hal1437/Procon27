
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
bool _Point<Type>::Norm(){
	if(this->x == 0 && this->y ==0)return false;
	else{
		this->x = this->x / this->size();
		this->y = this->y / this->size();
		return true;
	}
}
template <class Type>
_Point<Type> _Point<Type>::getNorm(){
	_Point<Type> answer(*this);
	answer.Norm();
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

