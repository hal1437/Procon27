
#pragma once
#include <cstdio>

class Console{
public:

	static bool ClearScreen(int interval=20000);
	static bool SetCursorPos(int x,int y);
	static bool MoveCursorPos(int x,int y);
};
