// Assistive.h
// 本头文件中包含所有绘制界面的函数声明、一部分响应按钮的函数声明，以及一部分其他函数的声明
// 注：响应按钮而显示二级菜单的函数一般不在这里声明，而是在各模块中声明

#ifndef ASSISTIVE_H
#define ASSISTIVE_H

#include "../HMS.h"

#include <vector>

// 以下为绘制界面的函数
// 函数命名的一般规则为：init+窗口名字，init意为initialize初始化

void initLoginScreen(Form &loginScreen);
void initAdminMainMenuScreen(Form &mainMenuScreen, const Admin &currentUser);
void initServerMainMenuScreen(Form &mainMenuScreen, const Server &currentUser);
void initChangePasswordScreen(Form &actionScreen);
void initRoomInfoScreen(Form &actionScreen);
void initAddRoomScreen(Form &actionScreen);
void initDeleteRoomScreen(Form &actionScreen);
void initModifyRoomScreen(Form &actionScreen);
void initModifyActionScreen(Form &actionScreen, int roomIndex);
void initVIPInfoScreen(Form &actionScreen);
void initAddVIPScreen(Form &actionScreen);
void initDeleteVIPScreen(Form &actionScreen);
void initModifyVIPScreen(Form &actionScreen);
void initModifyVIPActionScreen(Form &actionScreen, int vipIndex);
void initAddBookInfoScreen(Form &actionScreen);
void initAddBookInfoActionScreen(Form &actionScreen);
void initPickEmptyUnbookedRoom(Form &actionScreen);
void initFormFillScreen(Form &actionScreen);
void initInquireBasicInfoScreen(Form &actionScreen);
void initInquireAdvancedInfoScreen(Form &actionScreen);
void initInquireRoomNumberScreen(Form &actionScreen);
void initDeleteBookInfoActionScreen(Form &actionScreen);
void initCustomerInfoQueryScreen(Form &actionScreen);
void initRoomViewScreen(Form &actionScreen);
void initVIPViewScreen(Form &actionScreen);

// 以下为响应按钮的函数
// 其函数原型已经固定为：int functionName(Form &);

int sample(Form &src);
int loginVerify(Form &src);
int changePassword(Form &src);
int changePasswordCheck(Form &src);
int checkNewRoom(Form &src);
int checkDeleteRoom(Form &src);
int checkModifyRoom(Form &src);
int checkModifyAction(Form &src);
int checkNewVIP(Form &src);
int checkDeleteVIP(Form &src);
int checkModifyVIP(Form &src);
int checkModifyVIPAction(Form &src);
int checkNewBookInfoDate(Form &src);
int checkNewBookInfo(Form &src);
int checkPickEmptyUnbookedRoom(Form &src);
int checkFormFill(Form &src);
int checkInquireBasicInfo(Form &src);
int checkInquireAdvancedInfo(Form &src);
int checkInquireRoomNumber(Form &src);
int checkDeleteBookInfo(Form &src);
int customerInfoQuery(Form &src);
int filterVIPInfo(Form &src);
int backToLastMenu(Form &src);
int exitFromSystem(Form &src);

// 其他函数

void displayAllRooms();
std::vector<Room *> displaySpareRooms();
std::vector<Room *> displayUnbookedSpareRooms(int date);
void displayAllVIPs();
void displayAllBookInfos();
void findSpareRooms(std::vector<Room *> &res);
void findUnbookedSpareRoom(std::vector<Room *> res);

#endif