#ifndef PRESERVEINFO
#define PRESERVEINFO

#include "room.h"
#include <iostream>
#include <vector>
using namespace std;
class BookInfo
{
private:
	static const int ID_LEN = 18;
	static const int NAME_LEN = 8;
	char id[ID_LEN + 1];
	char name[NAME_LEN + 1];
	Room *attachedRoom;
	int date;
public:
	BookInfo (const char*, const char* ,Room*, int);
	void show_presereveInfo();
	friend void findUnbookedSpareRooms(vector<Room *> &res, int date);
	friend int customerInfoQuery(Form &src);
	friend ostream &operator<<(ostream &os, const BookInfo &rhs);
	friend bool operator<(const BookInfo &lhs, const BookInfo &rhs);
	friend struct ServerActions;
};

extern vector<BookInfo> bookings;

ostream &operator<<(ostream &os, const BookInfo &rhs);
bool operator<(const BookInfo &lhs, const BookInfo &rhs);

bool readBookInfo();
bool writeBookInfo();

#endif

