
#pragma once 
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <util/Printable.h>
#ifdef USE_ArrayFire
#include <arrayfire.h>
#endif
#include <cmath>


//数学的行列
template<size_t W,size_t H = W>
class Matrix:public Printable{
public:
	typedef Matrix<W,H> current;   //通常
	typedef Matrix<H,W> transpose; //転置
	typedef double       Value;
	
public:
#ifdef USE_ArrayFire
	af::array _m;//行列
#else
	Value _v[W][H]; //成分
#endif

public:

	Matrix();//コンストラクタ
#ifdef USE_ArrayFire
	Matrix(af::array arg);//コンストラクタ
#endif

	static Matrix<3,1> ConvertMatrix(const Point& p);        //ベクトルを行列に変換
	static Matrix<3,3> MakeMoveMatrix(double x,double y);    //平行移動行列作成
	static Matrix<3,3> MakeRotateMatrix(double radius);      //回転移動行列作成
	static Matrix<3,3> MakeScaleMatrix(double dx,double dy); //拡大行列作成
	static current MakeIdentityMatrix();//単位行列生成
	static constexpr bool isSquare(); //正方行列の判定

	Value    getDeterminant()const; //行列式取得
	transpose getTranspose()const;   //転置行列取得
	Point pos()const;

	Value getElement(size_t w,size_t h)const;
	void setElement (size_t w,size_t h,Value v);

	//演算子定義
	Value  operator()(size_t w,size_t h)const;//抽出
	//単項演算
	current operator+()const; //正の単項演算
	current operator-()const; //負の単項演算
	//二項演算
	current operator+(const current& rhs)const;  //和
	current operator-(const current& rhs)const;  //差
	current operator*(double rhs)const;  //スカラー倍
	template<size_t C>
	Matrix<C,H> operator*(const Matrix<C,W>& rhs)const;//積

	virtual void Print(std::ostream& ost)const;
};

typedef Matrix<3,1> vMat; //ベクトル
typedef Matrix<3,3> cMat; //変換行列

//変換
Point    operator* (const Point&   p,const cMat& mat);
Polygon  operator* (const Polygon& p,const cMat& mat);
Point&   operator*=(Point&   p,const cMat& mat);
Polygon& operator*=(Polygon& p,const cMat& mat);



