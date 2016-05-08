
#pragma once 
#include <util/Printable.h>


//数学的行列
template<size_t W,size_t H = W>
class Matrix:public Printable{
public:
	typedef Matrix<W,H> current;   //通常
	typedef Matrix<H,W> transpose; //転置
private:
	double _v[W][H]; //成分

public:

	Matrix();//コンストラクタ

	static current MakeIdentityMatrix();//単位行列生成
	static constexpr bool isSquare(); //正方行列の判定

	double    getDeterminant()const; //行列式取得
	transpose getTranspose()const;   //転置行列取得


	//演算子定義
	double& operator()(size_t w,size_t h);//抽出
	//単項演算
	current operator+()const; //正の単項演算
	current operator-()const; //負の単項演算
	//二項演算
	current operator+(const current& rhs)const;  //和
	current operator-(const current& rhs)const;  //差
	current operator*(double rhs)const;  //スカラー倍
	template<size_t C> Matrix<H,C> operator*(const Matrix<W,C>& rhs)const;//積

	virtual void Print(std::ostream& ost)const;
};
