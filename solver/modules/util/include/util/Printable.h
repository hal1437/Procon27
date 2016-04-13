

#pragma once
#include <iostream>

//出力可能インターフェイス
struct Printable{
	virtual void Print(std::ostream& ost)const = 0;
	friend std::ostream& operator<<(std::ostream& ost, const Printable& value);
};
