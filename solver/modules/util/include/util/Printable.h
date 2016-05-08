

#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>

//出力可能インターフェイス
struct Printable{
	template<class T>
	int getStringSize(const T& obj)const{
		std::stringstream ss;
		ss<<obj;
		return ss.str().size();
	}

	virtual void Print(std::ostream& ost)const = 0;
	friend std::ostream& operator<<(std::ostream& ost, const Printable& value);
};
