// User.h

#ifndef USER_H
#define USER_H

#include "../HMS.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class User {
    friend int checkUsers(const string &_id, const string &_password);
    friend int changePasswordCheck(Form &src);
protected:
    string id;
    string name;
    string password;
public:
    User(const string &_id, const string &_username, const string &_password);
    virtual void showMenu() = 0;
    virtual bool writeRecord() = 0;
};

class Admin : public User {
    friend void initAdminMainMenuScreen(Form &mainMenuScreen, const Admin &currentUser);
public:
    Admin(const string &_id, const string &_username, const string &_password);
    void showMenu();
    bool writeRecord();
};

class Server : public User {
    friend void initServerMainMenuScreen(Form &mainMenuScreen, const Server &currentUser);
public:
    Server(const string &_id, const string &_username, const string &_password);
    void showMenu();
    bool writeRecord();
};

struct AdminActions {
    static int showMenu_1(Form &src);
    static int showMenu_1_1(Form &src);
    static int showMenu_1_2(Form &src);
    static int showMenu_1_3(Form &src);
    static int showMenu_2(Form &src);
    static int showMenu_2_1(Form &src);
    static int showMenu_2_2(Form &src);
    static int showMenu_2_3(Form &src);
    static int modifyAction(int index);
    static int modifyVIPAction(int index);
};

struct ServerActions {
    static int showMenu_1(Form &src);
    static int showMenu_1_1(Form &src);
    static int showMenu_1_2(Form &src);
    static int showMenu_2(Form &src);
    static int showMenu_3(Form &src);
    static int showMenu_4(Form &src);
    static int showMenu_5(Form &src);
    static int showMenu_6(Form &src);
};

extern vector<User *> users;
extern int currentUserIndex;

bool initUserArray();
bool updateUserArray();
int checkUsers(const string &_id, const string &_password);

#endif
