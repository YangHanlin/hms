// main.cpp

#include "HMS.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>

using std::cout;
using std::endl;

int main() {
	initUserArray();
	Form loginScreen;
	initLoginScreen(loginScreen);
	system("title �Ƶ����ϵͳ");
	loginScreen.show();
	users[currentUserIndex = loginScreen.onFocus()]->showMenu();
	return 0;
}
