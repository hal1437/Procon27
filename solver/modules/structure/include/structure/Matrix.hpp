
#pragma once 
#include "Matrix.h"

template<size_t W,size_t H>
Matrix<W,H>::Matrix(){
#ifdef USE_ArrayFire
	_m = af::array(H, W);
#endif
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			this->setElement(i,j,0);
		}
	}
}
#ifdef USE_ArrayFire
template<size_t W,size_t H>
Matrix<W,H>::Matrix(af::array arg){
	_m = arg;
}
#endif

template<size_t W,size_t H>
vMat Matrix<W,H>::ConvertMatrix(const Point& p){
	vMat ans;
	ans.setElement(0,0,p.x);
	ans.setElement(1,0,p.y);
	ans.setElement(2,0,1.0);
	return ans;
}

template<size_t W,size_t H>
cMat Matrix<W,H>::MakeMoveMatrix(double x,double y){
	cMat ans;
	//平行移動
	ans.setElement(0,0,1.0);
	ans.setElement(1,1,1.0);
	ans.setElement(2,2,1.0);
	ans.setElement(0,2,x);
	ans.setElement(1,2,y);
	return ans;
}
template<size_t W,size_t H>
cMat Matrix<W,H>::MakeRotateMatrix(double radius){
	cMat ans;
	//回転移動
	ans.setElement(0,0, std::cos(radius));ans.setElement(1,0,std::sin(radius));
	ans.setElement(0,1,-std::sin(radius));ans.setElement(1,1,std::cos(radius));
	ans.setElement(2,2, 1.0);
	return ans;
}
template<size_t W,size_t H>
cMat Matrix<W,H>::MakeScaleMatrix(double dx,double dy){
	cMat ans;
	//拡大
	ans.setElement(0,0,dx);
	ans.setElement(1,1,dy);
	ans.setElement(2,2,1.0);
	return ans;
}

template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::MakeIdentityMatrix(){
	static_assert(isSquare(),"単位行列は行と列が一致しなければなりません。");
	Matrix<W,H>::current ans;
	
	for(int i=0;i<W;i++){
		for(int j=0;j<W;j++){
			ans.setElement(i,j,(i==j));
		}
	}
}

template<size_t W,size_t H>
constexpr bool Matrix<W,H>::isSquare(){
	return (W==H);
}


template<size_t W,size_t H>
typename Matrix<W,H>::Value Matrix<W,H>::getElement(size_t w,size_t h)const{
#ifdef USE_ArrayFire
	return _m(h,w).template scalar<float>();
#else
	return _v[w][h];
#endif
}
template<size_t W,size_t H>
void Matrix<W,H>::setElement (size_t w,size_t h,Value v){
#ifdef USE_ArrayFire
	_m(h,w) = v;
#else
	_v[w][h] = v;
#endif
}



template<size_t W,size_t H>
typename Matrix<W,H>::Value Matrix<W,H>::operator()(size_t w,size_t h)const{
	return this->getElement(w,h);
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
			ans.setElement(i,j,-(*this)(i,j));
		}
	}
	return ans;
}

//ArrayFireが導入されていれば
#ifdef USE_ArrayFire

//二項演算
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator+(const current& rhs)const{
	return (this->_m + rhs._m);
}
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator-(const current& rhs)const{
	return (this->_m - rhs._m);
}
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator*(double rhs)const{
	return (this->_m*rhs);
}

template<size_t W,size_t H>
template<size_t C>
Matrix<C,H> Matrix<W,H>::operator*(const Matrix<C,W>& rhs)const{
	return af::matmul(_m, rhs._m);
}

#else


//二項演算
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator+(const current& rhs)const{
	Matrix<W,H>::current ans;
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			ans.setElement(i,j,(*this)(i,j) + rhs(i,j));
		}
	}
	return ans;
}
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator-(const current& rhs)const{
	Matrix<W,H>::current ans;
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			ans.setElement(i,j,(*this)(i,j) - rhs(i,j));
		}
	}
	return ans;
}
template<size_t W,size_t H>
typename Matrix<W,H>::current Matrix<W,H>::operator*(double rhs)const{
	Matrix<W,H>::current ans;
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			ans.setElement(i,j,(*this)(i,j) * rhs);
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
				acc += (*this)(w,j) * rhs(i,w);
			}
			ans.setElement(i,j,acc);
		}
	}
	return ans;
}


#endif

template<size_t W,size_t H>
Point Matrix<W,H>::pos()const{
	return Point((*this)(0,0),(*this)(1,0));
}

template<size_t W,size_t H>
void Matrix<W,H>::Print(std::ostream& ost)const{
	//もっとも横幅が大きい文字列に統一する。
	int index = 0;
	int max_width=0;
	for(int i=0;i<H*W;i++){
		int width = getStringSize((*this)(i/H,i%H));
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
			ost << std::setw(max_width+1) << (*this)(j,i);
			if(j!=W-1)ost << ",";
		}
		if     (H==1  )ost << ")";
		else if(i==0  )ost << "┓\n";
		else if(i==H-1)ost << "┛\n";
		else           ost << "┃\n";
	}
}

