// Console.h
// 本头文件中包含与控制台一些操作相关的类及函数声明及类定义。

#ifndef CONSOLE_H
#define CONSOLE_H

#include "../HMS.h"

#include <Windows.h>

HANDLE getStdoutConsole();

class Console;

class Console {
private:
	HANDLE targetConsole;
public:
	Console(HANDLE _targetConsole = getStdoutConsole());
	HANDLE handle();
	void handle(HANDLE _targetConsole);
	void gotoxy(int x, int y);
	void setVisiblity(bool visibility);
	int getX();
	int getY();
	int getSizeX();
	int getSizeY();
};

#endif
