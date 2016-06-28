
#pragma once
#define _USE_MATH_DEFINES
#include <util/Printable.h>
#include <cmath>

//二次元座標クラス
template <class Type>
class _Point : public Printable{
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
	
	
	bool operator< (const _Point<Type>& rhs)const;
	bool operator==(const _Point<Type>& rhs)const;

	//v1からv2へ反時計周りの角度を取得する。
	static double getAngle2Vec(const _Point& v1,const _Point& v2);

	//正規化
	bool Norm();
	_Point getNorm()const;
	
	//一次変換
	bool Rotate(double angle);
	_Point getRotate(double angle)const;

	//大きさの取得
	double size()const;
	//内積
	double innerProduct(const _Point<Type>& rhs)const;
	//角度
	double angle(const _Point<Type>& rhs)const;

	virtual void Print(std::ostream& ost)const;

};

//エイリアス定義
typedef _Point<double> Point;
typedef _Point<int> Point_i;

