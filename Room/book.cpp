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
	cout << "���֤������: "<< id;
	cout << "\n������: "<<name;
	cout << "\n������: ";
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
		cout << "���棺";
		currentConsole.gotoxy(2, 2);
		cout << "��Ϣ�ļ��г��ִ���";
		currentConsole.gotoxy(2, 3);
		cout << "��Ҳ���ܹ�����ʹ��Ԥ�����ܣ���Ԥ����Ϣ���ܻᲿ�ֶ�ʧ��";
		currentConsole.gotoxy(2, 4);
		cout << "������ϸ��Ϣ��bookInfo.conf �г����˲����ڵķ����";
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
