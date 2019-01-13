#ifndef ROOM
#define ROOM

#include "../HMS.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Room
{
private:
	static const int TYPE_LEN = 6;
	int roomNumber;
	char roomType[TYPE_LEN + 1];
	double price;
	bool isSpare;

public:
	int show_roomNumber();   //打印房号
	Room(int , const char* ,double , bool);  //初始化
	void show_roomInfo();   //打印房间所有信息
	void set_roomNumber(int);  //设置房号
	void set_roomType(char*); //设置房型
	void set_price(double); //设置价格
	void set_status(bool); //设置状态
	friend bool operator<(const Room &lhs, const Room &rhs);
	friend ostream &operator<<(ostream &os, const Room &rhs);
	friend ofstream &operator<<(ofstream &os, const Room &rhs);
	friend void initModifyActionScreen(Form &src, int roomIndex);
	friend void findSpareRooms(vector<Room *> &res);
	friend void findUnbookedSpareRooms(vector<Room *> &res, int date);
	friend struct AdminActions;
	friend struct ServerActions;
};

extern vector<Room> rooms;

bool operator<(const Room &lhs, const Room &rhs);
ostream &operator<<(ostream &os, const Room &rhs);
ofstream &operator<<(ofstream &os, const Room &rhs);
bool initRoomArray();
bool updateRoomArray();

#endif
