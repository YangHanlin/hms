#include "../HMS.h"

#include<iostream>
#include<cstring>
#include <vector>
using namespace std;

class EntranceInfo
{
private:
	static const int ID_LEN = 18;
    static const int NAME_LEN = 8;
    static const int SEX_LEN = 2;
    
	char id[ID_LEN+1];
	char name[NAME_LEN+1];
	char sex[SEX_LEN+1];
	Room *attachedRoom;
	int date;
	double cash;
public:
	EntranceInfo(const char *_id=NULL, const char *_name=NULL, const char *_sex=NULL,Room *_attachedRoom=NULL,int _date=0,double _cash=0);
	char* getId();
	int getDate();
	Room *getRoom();
	void showInfo();
	friend struct ServerActions;
	friend int customerInfoQuery(Form &src);
	friend ostream &operator<<(ostream &os, const EntranceInfo &rhs);
};

extern vector<EntranceInfo> guests;

ostream &operator<<(ostream &os, const EntranceInfo &rhs);

bool initGuestsArray();
bool updateGuestsArray();
