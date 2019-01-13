#include "../HMS.h"

#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;
using std::left;
using std::setw;

vector<EntranceInfo> guests;

EntranceInfo::EntranceInfo(const char *_id, const char *_name, const char *_sex,Room *_attachedRoom,int _date,double _cash)
{
	strcpy(id,_id);
	strcpy(name,_name);
	strcpy(sex,_sex);
	attachedRoom = _attachedRoom;
	date = _date;
	cash = _cash;
}

char* EntranceInfo::getId()
{
	return id;
}

int EntranceInfo::getDate()
{
	return date;
}

Room *EntranceInfo::getRoom()
{
	return attachedRoom;
}

void EntranceInfo::showInfo()
{
	cout<<id<<"  "<<name<<"  "<<sex<<"  "<<attachedRoom->show_roomNumber() <<"  "<<date<<"  "<<cash<<endl;
}

ostream &operator<<(ostream &os, const EntranceInfo &rhs) {
	os << left
	   << setw(18) << rhs.id << "  "
	   << setw(10) << rhs.name << "  "
	   << setw(4) << rhs.sex << "  "
	   << setw(6) << rhs.attachedRoom->show_roomNumber() << "  "
	   << setw(8) << rhs.date << "  "
	   << setw(8) << rhs.cash;
	return os;
}

bool initGuestsArray() {
	string currentPath = _pgmptr;
	currentPath = currentPath.substr(0, currentPath.find_last_of('\\') + 1) + "guests.conf";
	ifstream guestsFileIn(currentPath.c_str());
	if (!guestsFileIn)
		return false;
	guests.clear();
	string id, name, sex;
	int roomNumber = 0, date = 0;
	double cash = 0.0;
	bool everFailed = false;
	while (guestsFileIn >> id >> name >> sex >> roomNumber >> date >> cash) {
		Room *matchedRoom = NULL;
		for (vector<Room>::size_type i = 0; i < rooms.size(); ++i)
			if (rooms[i].show_roomNumber() == roomNumber)
				matchedRoom = &rooms[i];
		if (matchedRoom == NULL)
			everFailed = true;
		else
			guests.push_back(EntranceInfo(id.c_str(), name.c_str(), sex.c_str(), matchedRoom, date, cash));
	}
	if (everFailed) {
		system("cls");
		Console currentConsole;
		int prevX = currentConsole.getX(),
		    prevY = currentConsole.getY();
		currentConsole.gotoxy(2, 1);
		cout << "警告：";
		currentConsole.gotoxy(2, 2);
		cout << "信息文件中出现错误。";
		currentConsole.gotoxy(2, 3);
		cout << "您也许能够继续使用相关功能，但入住信息可能会部分丢失。";
		currentConsole.gotoxy(2, 4);
		cout << "错误详细信息：guests.conf 中出现了不存在的房间号";
		currentConsole.gotoxy(2, 6);
		system("pause");
		currentConsole.gotoxy(prevX, prevY);
	}
	bool guestsSuccess = !(guestsFileIn.fail() && !guestsFileIn.eof());
	guestsFileIn.close();
	return guestsSuccess;
}

bool updateGuestsArray() {
	string currentPath = _pgmptr;
	currentPath = currentPath.substr(0, currentPath.find_last_of('\\') + 1) + "guests.conf";
	ofstream guestsFileOut(currentPath.c_str());
	if (!guestsFileOut)
		return false;
	for (vector<EntranceInfo>::size_type i = 0; i < guests.size(); ++i)
		guestsFileOut << guests[i];
	bool guestsSuccess = !guestsFileOut.fail();
	guestsFileOut.close();
	return guestsSuccess;
}
