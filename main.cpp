// main.cpp

#include "HMS.h"

#include <cstdlib>

using std::cout;
using std::endl;

int main() {
	system("cls");
	initUserArray();
	Form loginScreen;
	initLoginScreen(loginScreen);
	system("title �Ƶ����ϵͳ");
	loginScreen.show();
	users[currentUserIndex = loginScreen.onFocus()]->showMenu();
	return 0;
}
