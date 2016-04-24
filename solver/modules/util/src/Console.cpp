
#include <util/Console.h>


bool Console::ClearScreen(int interval){
	printf("\x1b[2J");
	for(int i=0;i<interval;i++);
	return true;
}
bool Console::SetCursorPos(int x,int y){
	printf("\x1b[%d;%dH" ,y,x);
	return true;
}
bool Console::MoveCursorPos(int x,int y){

	if(x > 0)printf("\x1b[%dC" , x); //カーソルをx行だけ右に移動
	if(x < 0)printf("\x1b[%dD" ,-x); //カーソルを-x行だけ左に移動
	if(y > 0)printf("\x1b[%dB" , y); //カーソルをy行だけ下に移動
	if(y < 0)printf("\x1b[%dA" ,-y); //カーソルを-y行だけ上に移動
}

