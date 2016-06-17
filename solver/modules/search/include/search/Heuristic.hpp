
#pragma once 

//評価値算出インターフェイス
template<class T>
class Heuristic{
public:

	virtual double operator()(const T& obj)const = 0;
};
