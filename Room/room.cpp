#include "../HMS.h"

#include <vector>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <algorithm>

using std::vector;
using std::ifstream;
using std::ostream;
using std::left;
using std::sort;

vector<Room> rooms;

Room::Room(int roomNumber, const char*ROOMTYPE, double price, bool ISSPARE)
{
	this->roomNumber = roomNumber;
	strcpy(roomType,ROOMTYPE );
	this->price = price;
	isSpare = ISSPARE;
}


int Room::show_roomNumber()
{
	return roomNumber;
}

void Room::show_roomInfo()
{
	cout << "房号是: " << roomNumber << endl;
	cout << "房型是: " << roomType;
	cout << "\n单价是: " << price << endl;
	cout << "状态是: ";
	if (isSpare)
		cout << "空闲" << endl;
	else
		cout << "已占用" << endl;
}

void Room::set_roomNumber(int roomNumber)
{
	this->roomNumber = roomNumber;
}

void Room::set_roomType(char*p)
{
	strcpy(roomType, p);
}

void Room::set_price(double price)
{
	this->price = price;
}

void Room::set_status(bool ISspare)
{
	isSpare = ISspare;
}

bool operator<(const Room &lhs, const Room &rhs) {
	return lhs.roomNumber < rhs.roomNumber;
}

ostream &operator<<(ostream &os, const Room &rhs) {
	os << left
	   << setw(11) << rhs.roomNumber << "  "
	   << setw(11) << rhs.roomType << "  "
	   << setw(11) << rhs.price << "  "
	   << setw(11) << (rhs.isSpare ? "是" : "否");
	return os;
}

ofstream &operator<<(ofstream &os, const Room &rhs) {
	os << left
	   << setw(11) << rhs.roomNumber << "  "
	   << setw(11) << rhs.roomType << "  "
	   << setw(11) << rhs.price << "  "
	   << setw(11) << (rhs.isSpare ? 1 : 0);
	return os;
}

bool initRoomArray() {
	rooms.clear();
	string currentPath = _pgmptr;
	currentPath = currentPath.substr(0, currentPath.find_last_of('\\') + 1) + "room.conf";
	ifstream roomFileIn(currentPath.c_str());
	if (!roomFileIn)
		return false;
	int roomNumber = 0, isSpareNumber = 0;
	double price = 0.0;
	string roomType;
	while (roomFileIn >> roomNumber >> roomType >> price >> isSpareNumber)
		rooms.push_back(Room(roomNumber, roomType.c_str(), price, static_cast<bool>(isSpareNumber)));
	bool roomFileInSuccess = !(roomFileIn.fail() && !roomFileIn.eof());
	roomFileIn.close();
	if (roomFileInSuccess)
		sort(rooms.begin(), rooms.end());
	return roomFileInSuccess;
}

bool updateRoomArray() {
	string currentPath = _pgmptr;
	currentPath = currentPath.substr(0, currentPath.find_last_of('\\') + 1) + "room.conf";
	ofstream roomFileOut(currentPath.c_str());
	if (!roomFileOut)
		return false;
	for (vector<Room>::size_type i = 0; i < rooms.size(); ++i)
		roomFileOut << rooms[i] << endl;
	bool roomFileOutSuccess = !roomFileOut.fail();
	roomFileOut.close();
	return roomFileOutSuccess;
}


