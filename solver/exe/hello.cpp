
#include <iostream>
#include <string>
#include <util/Console.h>
#include <util/Timer.h>

int main(){
	std::string str = "HELLO  WORLD";
	std::string author = "Yuya Omi";

	//枠を描画
	std::cout << "==================================================\n"
				 "=                                                =\n"
				 "=                                                =\n"
				 "=                                                =\n"
				 "=                                                =\n"
				 "==================================================\n";
	
	//strの描画
	Console::MoveCursorPos(25 - str.size(),-4);
	for(int i=0;i<str.size()*2;i++){
		std::cout << ( (i%2==0) ? str[i/2] : ' ') << std::flush;
		WaitTime(100);
	}

	WaitTime(1000);

	//著者の描画
	Console::MoveCursorPos(-50,0);
	Console::MoveCursorPos(44 - author.size(),2);
	for(int i=0;i<author.size();i++){
		std::cout << author[i] << std::flush;
		WaitTime(100);
	}

	WaitTime(1000);

	//終了処理
	Console::MoveCursorPos(0,3);
	std::cout << std::endl;
}

