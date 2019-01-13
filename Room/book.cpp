#include "../HMS.h"

#include <string>
#include<iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

vector<BookInfo> bookings;

BookInfo::BookInfo(const char *ID, const char *NAME, Room*p, int date)
{
	strcpy(id, ID);
	strcpy(name, NAME);
	attachedRoom = p;
	this->date = date;
}

void BookInfo::show_presereveInfo()
{
	cout << "身份证号码是: "<< id;
	cout << "\n姓名是: "<<name;
	cout << "\n房号是: ";
	attachedRoom->show_roomNumber();

}

ostream &operator<<(ostream &os, const BookInfo &rhs) {
	os << left
	   << setw(18) << rhs.id << "  "
	   << setw(10) << rhs.name << "  "
	   << setw(6) << rhs.attachedRoom->show_roomNumber() << "  "
	   << setw(10) << rhs.date;
	return os;
}

bool operator<(const BookInfo &lhs, const BookInfo &rhs) {
	return lhs.date < rhs.date;
}

bool readBookInfo()
{
	string currentPath = _pgmptr;
	currentPath = currentPath.substr(0, currentPath.find_last_of('\\') + 1) + "bookInfo.conf";
	ifstream bookInfo(currentPath.c_str());
	if (!bookInfo)
		return false;
	bookings.clear();
	string id;
	string name;
	int roomNumber;
	Room *roomPointer = NULL;
	int date;
	bool everFailed = false;
	while(bookInfo>>id>>name>>roomNumber>>date)
	{
		for(int i=0;i<rooms.size();++i)
		  if(roomNumber == rooms[i].show_roomNumber())
		    roomPointer = &rooms[i];
		if (roomPointer != NULL)
			bookings.push_back(BookInfo(id.c_str(),name.c_str(),roomPointer,date));
		else
			everFailed = true;
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
		cout << "您也许能够继续使用预订功能，但预订信息可能会部分丢失。";
		currentConsole.gotoxy(2, 4);
		cout << "错误详细信息：bookInfo.conf 中出现了不存在的房间号";
		currentConsole.gotoxy(2, 6);
		system("pause");
		currentConsole.gotoxy(prevX, prevY);
	}
	bool bookInfoSuccess = !(bookInfo.fail() && !bookInfo.eof());
	bookInfo.close();
	sort(bookings.begin(), bookings.end());
	return bookInfoSuccess;
}

bool writeBookInfo()
{
	string currentPath = _pgmptr;
	currentPath = currentPath.substr(0, currentPath.find_last_of('\\') + 1) + "bookInfo.conf";
	ofstream bookInfo(currentPath.c_str());
	if (!bookInfo)
		return false;
	for (int i = 0; i < bookings.size(); i++)
		bookInfo << bookings[i] << endl;
	bool bookInfoSuccess = !bookInfo.fail();
	bookInfo.close();
	return bookInfoSuccess;
}
