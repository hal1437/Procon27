
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
void _Point<Type>::Print(std::ostream& ost)const{
	ost << "(" << x << "," << y << ")";
}

