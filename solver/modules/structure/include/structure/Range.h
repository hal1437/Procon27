
#pragma once

template <class T>
class Range{
public:
	T maximum;
	T minimum;

public:

	Range(const T& max,const T& min):maximum(max),minimum(min){
	}

	decltype(maximum-minimum) diff()const{
		return maximum-minimum;
	}

};

