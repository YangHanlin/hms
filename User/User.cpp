// User.cpp
// ��Դ�ļ��а����� User.h ��������������ʵ��

#include "../HMS.h"

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert> // for debugging
#include <conio.h>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;

vector<User *> users;
int currentUserIndex = -1;

User::User(const string &_id, const string &_username, const string &_password): id(_id), name(_username), password(_password) {}

Admin::Admin(const string &_id, const string &_username, const string &_password) : User(_id, _username, _password) {}

void Admin::showMenu() {
    Form mainMenuScreen;
    initAdminMainMenuScreen(mainMenuScreen, *this);
	while (true) {
    	mainMenuScreen.show();
    	mainMenuScreen.onFocus();
	}
    return;
}

bool Admin::writeRecord() {
	string confPath = _pgmptr;
	confPath = confPath.substr(0, confPath.find_last_of('\\') + 1) + "admins.conf";
	ofstream adminFileOut(confPath.c_str(), ios::app);
	if (!adminFileOut)
		return false;
	adminFileOut << id << " " << name << " " << password << " " << endl;
	bool res = !adminFileOut.fail();
	adminFileOut.close();
	return res;
}

Server::Server(const string &_id, const string &_username, const string &_password) : User(_id, _username, _password) {}

void Server::showMenu() {
    Form mainMenuScreen;
    initServerMainMenuScreen(mainMenuScreen, *this);
	while (true) {
    	mainMenuScreen.show();
    	mainMenuScreen.onFocus();
	}
    return;
}

bool Server::writeRecord() {
	string confPath = _pgmptr;
	confPath = confPath.substr(0, confPath.find_last_of('\\') + 1) + "servers.conf";
	ofstream serverFileOut(confPath.c_str(), ios::app);
	if (!serverFileOut)
		return false;
	serverFileOut << id << " " << name << " " << password << " " << endl;
	bool res = !serverFileOut.fail();
	serverFileOut.close();
	return res;
}

int AdminActions::showMenu_1(Form &src) {
	if (!initRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ����ͷ���Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	Form roomInfoScreen;
	initRoomInfoScreen(roomInfoScreen);
	do {
		roomInfoScreen.show();
		displayAllRooms();
	} while (roomInfoScreen.onFocus() != 0);
	if (!updateRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ�Ŀͷ���Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	return Control::backReturn;
}

int AdminActions::showMenu_1_1(Form &src) {
	Form addRoomScreen;
	initAddRoomScreen(addRoomScreen);
	addRoomScreen.show();
	displayAllRooms();
	if (addRoomScreen.onFocus() == 1)
		rooms.push_back(Room(atoi(addRoomScreen[0].text()), addRoomScreen[1].text(), atof(addRoomScreen[2].text()), true));
	return Control::backReturn + 1;
}

int AdminActions::showMenu_1_2(Form &src) {
	Form deleteRoomScreen;
	initDeleteRoomScreen(deleteRoomScreen);
	deleteRoomScreen.show();
	displayAllRooms();
	int returnValue = deleteRoomScreen.onFocus();
	if (returnValue != 0)
		rooms.erase(rooms.begin() + returnValue - 1);
	return Control::backReturn + 1;
}

int AdminActions::showMenu_1_3(Form &src) {
	Form modifyRoomScreen, modifyActionScreen;
	initModifyRoomScreen(modifyRoomScreen);
	do {
		modifyRoomScreen.show();
		displayAllRooms();
		int returnValue = modifyRoomScreen.onFocus();
		if (returnValue == 0)
			break;
		if (AdminActions::modifyAction(returnValue - 1) == 1)
			break;
	} while (true);
	return Control::backReturn + 1;
}

int AdminActions::showMenu_2(Form &src) {
	if (!initVIPArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ���VIP����Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� vipdata.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	Form vipInfoScreen;
	initVIPInfoScreen(vipInfoScreen);
	do {
		vipInfoScreen.show();
		displayAllVIPs();
	} while (vipInfoScreen.onFocus() != 0);
	if (!updateVIPArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ��VIP����Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ vipdata.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	return Control::backReturn;
}

int AdminActions::showMenu_2_1(Form &src) {
	Form addVIPScreen;
	initAddVIPScreen(addVIPScreen);
	addVIPScreen.show();
	displayAllVIPs();
	if (addVIPScreen.onFocus() == 1)
		vips.push_back(VIP(atoi(addVIPScreen[0].text()), addVIPScreen[1].text(), addVIPScreen[2].text(), addVIPScreen[3].text(), 0));
	return Control::backReturn + 1;
}

int AdminActions::showMenu_2_2(Form &src) {
	Form deleteVIPScreen;
	initDeleteVIPScreen(deleteVIPScreen);
	deleteVIPScreen.show();
	displayAllVIPs();
	int returnValue = deleteVIPScreen.onFocus();
	if (returnValue != 0)
		vips.erase(vips.begin() + returnValue - 1);
	return Control::backReturn + 1;
}

int AdminActions::showMenu_2_3(Form &src) {
	Form modifyVIPScreen, modifyActionScreen;
	initModifyVIPScreen(modifyVIPScreen);
	do {
		modifyVIPScreen.show();
		displayAllVIPs();
		int returnValue = modifyVIPScreen.onFocus();
		if (returnValue == 0)
			break;
		if (AdminActions::modifyVIPAction(returnValue - 1) == 1)
			break;
	} while (true);
	return Control::backReturn + 1;
}

int AdminActions::modifyAction(int index) {
	Form modifyActionScreen;
	Console currentConsole;
	initModifyActionScreen(modifyActionScreen, index);
	modifyActionScreen.show();
	displayAllRooms();
	int returnValue = modifyActionScreen.onFocus();
	if (returnValue == 1)
		rooms[index] = Room(atoi(modifyActionScreen[0].text()), modifyActionScreen[1].text(), atof(modifyActionScreen[2].text()), rooms[index].isSpare);
	return returnValue;
}

int AdminActions::modifyVIPAction(int index) {
	Form modifyVIPActionScreen;
	Console currentConsole;
	initModifyVIPActionScreen(modifyVIPActionScreen, index);
	modifyVIPActionScreen.show();
	displayAllVIPs();
	int returnValue = modifyVIPActionScreen.onFocus();
	if (returnValue == 1)
		vips[index] = VIP(atoi(modifyVIPActionScreen[0].text()), modifyVIPActionScreen[1].text(), modifyVIPActionScreen[2].text(), modifyVIPActionScreen[3].text(), vips[index].score);
	return returnValue;
}

int ServerActions::showMenu_1(Form &src) {
	if (!initRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ����ͷ���Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	if (!readBookInfo()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ���Ԥ����Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ����ͼ��ȡ bookInfo.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	Form addBookInfoScreen;
	initAddBookInfoScreen(addBookInfoScreen);
	while (true) {
		addBookInfoScreen.show();
		displayAllBookInfos();
		if (addBookInfoScreen.onFocus() == 0)
			break;
	}
	if (!writeBookInfo()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ��Ԥ����Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ bookInfo.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	if (!updateRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ�Ŀͷ���Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	return Control::backReturn;
}

int ServerActions::showMenu_1_1(Form &src) {
	Form addBookInfoActionScreen;
	initAddBookInfoActionScreen(addBookInfoActionScreen);
	while (true) {
		addBookInfoActionScreen.show();
		displayAllBookInfos();
		if (addBookInfoActionScreen.onFocus() == 0)
			break;
		Form pickEmptyUnbookedRoom;
		initPickEmptyUnbookedRoom(pickEmptyUnbookedRoom);
		pickEmptyUnbookedRoom.show();
		vector<Room *> unbookedSpareRooms = displayUnbookedSpareRooms(atoi(addBookInfoActionScreen[1].text()));
		int returnValue = pickEmptyUnbookedRoom.onFocus();
		if (returnValue == 0)
			break;
		Form formFillScreen;
		initFormFillScreen(formFillScreen);
		formFillScreen.show();
		if (formFillScreen.onFocus() == 0)
			break;
		bookings.push_back(BookInfo(formFillScreen[1].text(), formFillScreen[3].text(), unbookedSpareRooms[returnValue - 1], atoi(addBookInfoActionScreen[1].text())));
		unbookedSpareRooms[returnValue - 1]->isSpare = false;
		break;
	}
	return Control::backReturn + 1;
}

int ServerActions::showMenu_1_2(Form &src) {
	Form deleteBookInfoActionScreen;
	initDeleteBookInfoActionScreen(deleteBookInfoActionScreen);
	deleteBookInfoActionScreen.show();
	displayAllBookInfos();
	int returnValue = deleteBookInfoActionScreen.onFocus();
	if (returnValue != 0) {
		bookings[atoi(deleteBookInfoActionScreen[1].text()) - 1].attachedRoom->isSpare = true;
		bookings.erase(bookings.begin() + atoi(deleteBookInfoActionScreen[1].text()) - 1);
	}
	return Control::backReturn + 1;
}

int ServerActions::showMenu_2(Form &src) {
	if (!initRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ����ͷ���Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	if (!readBookInfo()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ���Ԥ����Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ����ͼ��ȡ bookInfo.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	if (!initGuestsArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ�����ס��Ϣ��";
		currentConsole.gotoxy(2, 4);
		cout<<"������ϸ��Ϣ����ͼ��ȡ guests.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	Form inquireBasicInfoScreen;
	initInquireBasicInfoScreen(inquireBasicInfoScreen);
	inquireBasicInfoScreen.show();
	if (inquireBasicInfoScreen.onFocus() == 0)
		return Control::backReturn + 1;
	Form inquireAdvancedInfoScreen;
	initInquireAdvancedInfoScreen(inquireAdvancedInfoScreen);
	string targetID = inquireBasicInfoScreen[1].text();
	int targetDate = atoi(inquireBasicInfoScreen[3].text());
	int bookInfoMatch = -1;
	int roomMatch = -1;
	for (vector<BookInfo>::size_type i = 0; i < bookings.size(); ++i)
		if (bookings[i].id == targetID && bookings[i].date == targetDate) {
			bookInfoMatch = i;
			break;
		}
	if (bookInfoMatch == -1) {
		Form pickEmptyUnbookedRoom;
		initPickEmptyUnbookedRoom(pickEmptyUnbookedRoom);
		pickEmptyUnbookedRoom.show();
		vector<Room *> emptyUnbookedRooms = displayUnbookedSpareRooms(targetDate);
		int returnValue = pickEmptyUnbookedRoom.onFocus();
		if (returnValue == 0)
			return Control::backReturn + 1;
		for (int i = 0; i < rooms.size(); ++i)
			if (emptyUnbookedRooms[returnValue - 1] == &rooms[i]) {
				roomMatch = i;
				break;
			}
		// for cases that are impossible to meet in real situations - begin
		if (roomMatch == -1) {
			system("cls");
			assert(false);
			system("pause");
		}
		// for cases that are impossible to meet in real situations - end
	} else {
		for (int i = 0; i < rooms.size(); ++i)
			if (bookings[bookInfoMatch].attachedRoom == &rooms[i]) {
				roomMatch = i;
				break;
			}
		// for cases that are impossible to meet in real situations - begin
		if (roomMatch == -1) {
			system("cls");
			assert(false);
			system("pause");
		}
		// for cases that are impossible to meet in real situations - end
	}
	inquireAdvancedInfoScreen.show();
	if (inquireAdvancedInfoScreen.onFocus() == 0)
		return Control::backReturn + 1;
	guests.push_back(EntranceInfo(targetID.c_str(), inquireAdvancedInfoScreen[1].text(), inquireAdvancedInfoScreen[3].text(), &rooms[roomMatch], targetDate, atof(inquireAdvancedInfoScreen[5].text())));
	rooms[roomMatch].isSpare = false;
	if (bookInfoMatch != -1)
		bookings.erase(bookings.begin() + bookInfoMatch);
	if (!updateGuestsArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ����ס��Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ guests.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	if (!writeBookInfo()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ��Ԥ����Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ bookInfo.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	if (!updateRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ�Ŀͷ���Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	return Control::backReturn + 1;
}

int ServerActions::showMenu_3(Form &src) {
	if (!initRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ����ͷ���Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	if (!initGuestsArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ�����ס��Ϣ��";
		currentConsole.gotoxy(2, 4);
		cout<<"������ϸ��Ϣ����ͼ��ȡ guests.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	if (!initVIPArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ���VIP����Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� vipdata.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	Form inquireRoomNumberScreen;
	initInquireRoomNumberScreen(inquireRoomNumberScreen);
	inquireRoomNumberScreen.show();
	int returnValue = inquireRoomNumberScreen.onFocus();
	if (returnValue == 0)
		return Control::backReturn + 1;
	int vipMatch = -1;
	for (int i = 0; i < vips.size(); ++i)
		if (vips[i].ID == guests[returnValue - 1].id) {
			vipMatch = i;
			break;
		}
	Console currentConsole;
	int prevX = currentConsole.getX(),
	    prevY = currentConsole.getY();
	system("cls");
	currentConsole.gotoxy(currentConsole.getSizeX() / 2 - 16 - 1, currentConsole.getSizeY() / 2 - 2 - 1);
	cout << "������ס�ķ���Ϊ " << guests[returnValue - 1].getRoom()->roomType << " ������ " << guests[returnValue - 1].getRoom()->price << " Ԫ��";
	currentConsole.gotoxy(currentConsole.getSizeX() / 2 - 16 - 1, currentConsole.getSizeY() / 2 - 1 - 1);
	cout << "Ӧ��Ѻ�� " << guests[returnValue - 1].cash << " Ԫ��";
	if (vipMatch != -1) {
		currentConsole.gotoxy(currentConsole.getSizeX() / 2 - 16 - 1, currentConsole.getSizeY() / 2 + 1 - 1);
		cout << "�ÿͻ����� VIP �������λ��� " << guests[returnValue - 1].getRoom()->price << " �֡�";
		currentConsole.gotoxy(currentConsole.getSizeX() / 2 - 16 - 1, currentConsole.getSizeY() / 2 + 2 - 1);
		cout << "VIP ����ǰ����Ϊ " << (vips[vipMatch].score += guests[returnValue - 1].getRoom()->price) << " �֡�";
	}
	guests[returnValue - 1].getRoom()->isSpare = true;
	guests.erase(guests.begin() + returnValue - 1);
	_getch();
	currentConsole.gotoxy(prevX, prevY);
	if (!updateVIPArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ��VIP����Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ vipdata.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	if (!updateGuestsArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ����ס��Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ guests.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	if (!updateRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�޸ĺ�Ŀͷ���Ϣ���ᱻ���档";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ������ room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
	}
	return Control::backReturn + 1;
}

int ServerActions::showMenu_4(Form &src) {
	Form roomViewScreen;
	initRoomViewScreen(roomViewScreen);
	initRoomArray();
	roomViewScreen.show();
	displayAllRooms();
	roomViewScreen.onFocus();
	return Control::backReturn;
}

int ServerActions::showMenu_5(Form &src) {
	if (!initRoomArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ����ͷ���Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� room.conf �ͷ���Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	if (!readBookInfo()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ���Ԥ����Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ����ͼ��ȡ bookInfo.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	if (!initGuestsArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ�����ס��Ϣ��";
		currentConsole.gotoxy(2, 4);
		cout<<"������ϸ��Ϣ����ͼ��ȡ guests.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	if (!initVIPArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ���VIP����Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� vipdata.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	Form customerInfoQueryScreen;
	initCustomerInfoQueryScreen(customerInfoQueryScreen);
	customerInfoQueryScreen.show();
	customerInfoQueryScreen.onFocus();
	return Control::backReturn + 1;
}

int ServerActions::showMenu_6(Form &src) {
	Form vipViewScreen;
	initVIPViewScreen(vipViewScreen);
	initVIPArray();
	vipViewScreen.show();
	displayAllVIPs();
	vipViewScreen.onFocus();
	return Control::backReturn;
}

bool initUserArray() {
    string currentPath = _pgmptr;
	currentPath=currentPath.substr(0, currentPath.find_last_of('\\')+1);
	ifstream adminFileIn((currentPath+"admins.conf").c_str()),
	         serverFileIn((currentPath+"servers.conf").c_str());
	string tmpId, tmpUsername, tmpPassword;
	if (!adminFileIn.is_open()) {
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ���������ϵͳ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���޷��� admins.conf �û���Ϣ�ļ�";
		currentConsole.gotoxy(2, 5);
		system("pause");
		exit(1);
	}
	while (adminFileIn>>tmpId>>tmpUsername>>tmpPassword)
		users.push_back(new Admin(tmpId, tmpUsername, tmpPassword));
	bool adminFileInSuccess = !(adminFileIn.fail() && !adminFileIn.eof());
	adminFileIn.close();
	if (!serverFileIn.is_open()) {
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ���������ϵͳ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���޷��� servers.conf �û���Ϣ�ļ�";
		currentConsole.gotoxy(2, 5);
		system("pause");
		exit(1);
	}
	if (!initVIPArray()) {
		system("cls");
		Console currentConsole;
		currentConsole.gotoxy(2, 1);
		cout<<"������һ������";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ����ܲ���VIP����Ϣ��";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ���� vipdata.conf ��Ϣ�ļ�ʱ����";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	while (serverFileIn>>tmpId>>tmpUsername>>tmpPassword)
		users.push_back(new Server(tmpId, tmpUsername, tmpPassword));
	bool serverFileInSuccess = !(serverFileIn.fail() && !serverFileIn.eof());
	serverFileIn.close();
	return adminFileInSuccess && serverFileInSuccess;
}

bool updateUserArray() {
	string currentPath = _pgmptr;
	currentPath=currentPath.substr(0, currentPath.find_last_of('\\')+1);
	ofstream adminFileOut((currentPath + "admins.conf").c_str()),
	         serverFileOut((currentPath + "servers.conf").c_str());
	if (!adminFileOut || !serverFileOut)
		return false;
	bool userFileOutSuccess = true;
	for (vector<User *>::iterator iter = users.begin(); iter != users.end();++iter)
		userFileOutSuccess &= (*iter)->writeRecord();
	return userFileOutSuccess;
}

int checkUsers(const string &_id, const string &_password) {
    for (vector<User *>::size_type i=0; i<users.size(); ++i)
        if (users[i]->id==_id && users[i]->password==_password)
            return i;
    return -1;
}
