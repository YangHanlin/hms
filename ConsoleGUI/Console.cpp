// Console.cpp
// 本源文件中包含 Console.h 中声明的函数及类成员函数的定义。

#include "../HMS.h"

#include <Windows.h>
#include <cstdlib>

HANDLE getStdoutConsole() {
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

Console::Console(HANDLE _targetConsole) {
	handle(_targetConsole);
}

HANDLE Console::handle() {
	return targetConsole;
}

void Console::handle(HANDLE _targetConsole) {
	targetConsole = _targetConsole;
	return;
}

void Console::gotoxy(int x, int y) {
	if (targetConsole == NULL)
		return;
	COORD nextCursorPosition;
	nextCursorPosition.X = x;
	nextCursorPosition.Y = y;
	SetConsoleCursorPosition(targetConsole, nextCursorPosition);
	return;
}

void Console::setVisiblity(bool visibility) {
	CONSOLE_CURSOR_INFO currentCursor;
	GetConsoleCursorInfo(targetConsole, &currentCursor);
	currentCursor.bVisible = visibility;
	SetConsoleCursorInfo(targetConsole, &currentCursor);
	return;
}

int Console::getX() {
	if (targetConsole == NULL)
		return -1;
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBuffer;
	GetConsoleScreenBufferInfo(targetConsole, &consoleScreenBuffer);
	return consoleScreenBuffer.dwCursorPosition.X;
}

int Console::getY() {
	if (targetConsole == NULL)
		return -1;
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBuffer;
	GetConsoleScreenBufferInfo(targetConsole, &consoleScreenBuffer);
	return consoleScreenBuffer.dwCursorPosition.Y;
}

int Console::getSizeX() {
	if (targetConsole == NULL)
		return -1;
	CONSOLE_SCREEN_BUFFER_INFO targetConsoleScreenBuffer;
	GetConsoleScreenBufferInfo(targetConsole, &targetConsoleScreenBuffer);
	return targetConsoleScreenBuffer.srWindow.Right + 1;
}

int Console::getSizeY() {
	if (targetConsole == NULL)
		return -1;
	CONSOLE_SCREEN_BUFFER_INFO targetConsoleScreenBuffer;
	GetConsoleScreenBufferInfo(targetConsole, &targetConsoleScreenBuffer);
	return targetConsoleScreenBuffer.srWindow.Bottom + 1;
}
