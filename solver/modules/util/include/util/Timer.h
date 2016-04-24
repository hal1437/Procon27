
#pragma once
#include <chrono>

void WaitTime(int ms){
	auto begin = std::chrono::system_clock::now();
	while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin).count() < ms);
}
