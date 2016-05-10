
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
		if     (i==0  )ost << "┏";
		else if(i==H-1)ost << "┗";
		else           ost << "┃";
		for(int j=0;j<W;j++){
			ost << std::setw(max_width+1) << _v[j][i];
			if(j!=W-1)ost << ",";
		}
		if     (i==0  )ost << "┓\n";
		else if(i==H-1)ost << "┛\n";
		else           ost << "┃\n";
	}
}

