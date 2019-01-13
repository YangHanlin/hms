// Console.h
// ��ͷ�ļ��а��������̨һЩ������ص��༰�����������ඨ�塣

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
