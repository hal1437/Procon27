
#pragma once

//二次元座標クラス
template <class Type>
class _Point{
public:
	Type x;
	Type y;

	_Point();
	_Point(const Type& init);
	_Point(const Type& _x,const Type& _y);

	//演算子のオーバーロード
	_Point operator+(const _Point<Type>& rhs)const;
	_Point operator-(const _Point<Type>& rhs)const;
	_Point operator+(const Type& rhs)const;
	_Point operator-(const Type& rhs)const;
	_Point operator*(const Type& rhs)const;
	_Point operator/(const Type& rhs)const;

	_Point& operator+=(const _Point<Type>& rhs)const;
	_Point& operator-=(const _Point<Type>& rhs)const;
	_Point& operator+=(const Type& rhs)const;
	_Point& operator-=(const Type& rhs)const;
	_Point& operator*=(const Type& rhs)const;
	_Point& operator/=(const Type& rhs)const;


};

//エイリアス定義
typedef _Point<double> Point;

