
#pragma once 
#include "Matrix.h"

template<size_t W,size_t H>
Matrix<W,H>::Matrix(){
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			_v[i][j] = 0;
		}
	}
}

template<size_t W,size_t H>
vMat Matrix<W,H>::ConvertMatrix(const Point& p){
	vMat ans;
	ans(0,0) = p.x;
	ans(1,0) = p.y;
	ans(2,0) = 1.0;
	return ans;
}

template<size_t W,size_t H>
cMat Matrix<W,H>::MakeMoveMatrix(double x,double y){
	cMat ans;
	//平行移動
	ans(0,0) = 1.0;
	ans(1,1) = 1.0;
	ans(2,2) = 1.0;
	ans(0,2) = x;
	ans(1,2) = y;
	return ans;
}
template<size_t W,size_t H>
cMat Matrix<W,H>::MakeRotateMatrix(double radius){
	cMat ans;
	//回転移動
	ans(0,0) =  std::cos(radius);ans(1,0) = std::sin(radius);
	ans(0,1) = -std::sin(radius);ans(1,1) = std::cos(radius);
	ans(2,2) = 1.0;
	return ans;
}
template<size_t W,size_t H>
cMat Matrix<W,H>::MakeScaleMatrix(double dx,double dy){
	cMat ans;
	//拡大
	ans(0,0) = dx;
	ans(1,1) = dy;
	ans(2,2) = 1.0;
	return ans;
}

template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::MakeIdentityMatrix(){
	static_assert(isSquare(),"単位行列は行と列が一致しなければなりません。");
	Matrix<W,H>::current ans;
	
	for(int i=0;i<W;i++){
		for(int j=0;j<W;j++){
			ans(i,j) = (i==j);
		}
	}
}

template<size_t W,size_t H>
constexpr bool Matrix<W,H>::isSquare(){
	return (W==H);
}


template<size_t W,size_t H>
double& Matrix<W,H>::operator()(size_t w,size_t h){
	return _v[w][h];
}
template<size_t W,size_t H>
double Matrix<W,H>::operator()(size_t w,size_t h)const{
	return _v[w][h];
}
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator+()const{
	return (*this);
}
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator-()const{
	Matrix<W,H>::current ans;
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			ans._v[i][j] = -this->_v[i][j];
		}
	}
	return ans;
}
//二項演算
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator+(const current& rhs)const{
	Matrix<W,H>::current ans;
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			ans(i,j) = this->_v[i][j] + rhs(i,j);
		}
	}
	return ans;
}
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator-(const current& rhs)const{
	Matrix<W,H>::current ans;
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			ans(i,j) = this->_v[i][j] - rhs(i,j);
		}
	}
	return ans;
}
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator*(double rhs)const{
	Matrix<W,H>::current ans;
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			ans(i,j) = this->_v[i][j] * rhs;
		}
	}
	return ans;
}

template<size_t W,size_t H>
template<size_t C>
Matrix<C,H> Matrix<W,H>::operator*(const Matrix<C,W>& rhs)const{
	Matrix<C,H> ans;
	//(W*H) * (C*W) = (C*H)
	for(int i=0;i<C;i++){
		for(int j=0;j<H;j++){
			double acc = 0;
			for(int w=0;w<W;w++){
				acc += this->_v[w][j] * rhs(i,w);
			}
			ans(i,j) = acc;
		}
	}
	return ans;
}


template<size_t W,size_t H>
Point Matrix<W,H>::pos()const{
	return Point(_v[0][0],_v[1][0]);
}

template<size_t W,size_t H>
void Matrix<W,H>::Print(std::ostream& ost)const{
	//もっとも横幅が大きい文字列に統一する。
	int index = 0;
	int max_width=0;
	for(int i=0;i<H*W;i++){
		int width = getStringSize(_v[i/H][i%H]);
		if(width > max_width){
			index = i;
			max_width = width;
		}
	}

	for(int i=0;i<H;i++){
		if     (H==1  )ost << "(";
		else if(i==0  )ost << "┏";
		else if(i==H-1)ost << "┗";
		else           ost << "┃";
		for(int j=0;j<W;j++){
			ost << std::setw(max_width+1) << _v[j][i];
			if(j!=W-1)ost << ",";
		}
		if     (H==1  )ost << ")";
		else if(i==0  )ost << "┓\n";
		else if(i==H-1)ost << "┛\n";
		else           ost << "┃\n";
	}
}
Point   operator* (const Point&   p,const cMat& mat){
	vMat v,after;
	v(0,0) = p.x;
	v(1,0) = p.y;
	v(2,0) = 1.0;
	after = v * mat;
	return Point(after(0,0),after(1,0));
}
Polygon operator* (const Polygon& p,const cMat& mat){
	Polygon ans;
	for(int i=0;i<p.size();i++)ans.addNode(p.getNode(i)*mat);
	return ans;
}
Point&   operator*=(Point&   p,const cMat& mat){
	p = p * mat;
	return p;
}
Polygon& operator*=(Polygon& p,const cMat& mat){
	p = p * mat;
	return p;
}

