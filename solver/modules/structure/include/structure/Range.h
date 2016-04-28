
#pragma once

template <class T>
class Range{
public:
	T max;
	T min;

public:

	Range(const T& Max,const T& Min):max(Max),min(Min){
	}

	decltype(maximum-minimum) diff()const{
		return maximum-minimum;
	}

};

