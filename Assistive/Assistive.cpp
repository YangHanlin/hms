// Assistive.cpp
// ��Դ�ļ��а��� Assistive.h ��������������ʵ��

#include "../HMS.h"

#include <cstdlib>
#include <cctype>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::ostringstream;
using std::left;
using std::setfill;
using std::setw;
using std::vector;
using std::sort;

void initLoginScreen(Form &loginScreen) {
	Label captionLabel(loginScreen.width() / 2 - 6 - 1, loginScreen.height() / 2 - 2 - 1),
		  usernameLabel(loginScreen.width() / 2 - 8 - 1, loginScreen.height() / 2 - 1),
		  passwordLabel(loginScreen.width() / 2 - 8 - 1, loginScreen.height() / 2 + 1 - 1);
	TextBox usernameBox(loginScreen.width() / 2 - 1, loginScreen.height() / 2 - 1),
		    passwordBox(loginScreen.width() / 2 - 1, loginScreen.height() / 2 + 1 - 1);
	Button loginButton(loginScreen.width() / 2 - 2 - 1, loginScreen.height() / 2 + 3 - 1);
	captionLabel.text("�Ƶ����ϵͳ");
	usernameLabel.text("�û�����");
	passwordLabel.text("���룺");
	passwordBox.hidden(true);
	loginButton.text("��¼");
	loginButton.click(loginVerify);
	loginScreen.add(captionLabel);
	loginScreen.add(usernameLabel);
	loginScreen.add(usernameBox);
	loginScreen.add(passwordLabel);
	loginScreen.add(passwordBox);
	loginScreen.add(loginButton);
	loginScreen.defaulti(loginScreen.size() - 1);
	return;
}

void initAdminMainMenuScreen(Form &mainMenuScreen, const Admin &currentUser) {
	Label welcomeLabel(mainMenuScreen.width() / 2 - (22 + currentUser.name.length()) / 2 - 1, 2);
    Label welcomeLabel2(mainMenuScreen.width() / 2 - 5 - 1, 3);
    welcomeLabel.text(("�𾴵�"+currentUser.name+"������Ա��������").c_str());
    welcomeLabel2.text("��ѡ�����"); 
    mainMenuScreen.add(welcomeLabel);
    mainMenuScreen.add(welcomeLabel2);
    Menu mainMenu(mainMenuScreen.width() / 2 - 11 / 2 - 1, 5);
    mainMenu.add("1.�ͷ���Ϣ ");
	mainMenu.last().click(AdminActions::showMenu_1);
    mainMenu.add("2.VIP����Ϣ");
	mainMenu.last().click(AdminActions::showMenu_2);
    mainMenu.add("3.�޸����� ");
	mainMenu.last().click(changePassword);
    mainMenu.add("4.�˳�     ");
    mainMenu.last().click(exitFromSystem);
    mainMenuScreen.add(mainMenu);
	return;
}

void initServerMainMenuScreen(Form &mainMenuScreen, const Server &currentUser) {
	Label welcomeLabel(mainMenuScreen.width() / 2 - (22 + currentUser.name.length()) / 2 - 1, 2);
    Label welcomeLabel2(mainMenuScreen.width() / 2 - 5 - 1, 3);
    welcomeLabel.text(("�𾴵�"+currentUser.name+"������Ա��������").c_str());
    welcomeLabel2.text("��ѡ�����"); 
    mainMenuScreen.add(welcomeLabel);
    mainMenuScreen.add(welcomeLabel2);
    Menu mainMenu(mainMenuScreen.width() / 2 - 7 - 1, 5);
    mainMenu.add("1.Ԥ������    ");
	mainMenu.last().click(ServerActions::showMenu_1);
    mainMenu.add("2.��ס        ");
	mainMenu.last().click(ServerActions::showMenu_2);
    mainMenu.add("3.�˷�        ");
	mainMenu.last().click(ServerActions::showMenu_3);
    mainMenu.add("4.�ͷ���Ϣ    ");
	mainMenu.last().click(ServerActions::showMenu_4);
	mainMenu.add("5.������Ϣ��ѯ");
	mainMenu.last().click(ServerActions::showMenu_5);
    mainMenu.add("6.VIP����ѯ   ");
	mainMenu.last().click(ServerActions::showMenu_6);
	mainMenu.add("7.�޸�����    ");
	mainMenu.last().click(changePassword);
    mainMenu.add("8.�˳�        ");
    mainMenu.last().click(exitFromSystem);
    mainMenuScreen.add(mainMenu);
	return;
}

void initChangePasswordScreen(Form &actionScreen) {
	Label oldPasswordLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 3),
	      newPasswordLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 2),
		  confirmPasswordLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 1),
		  msgLabel(actionScreen.width() / 2 - 11 - 1, actionScreen.height() - 1 - 1);
	TextBox oldPasswordBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 3),
	        newPasswordBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 2),
			confirmPasswordBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 1);
	Button submitButton(actionScreen.width() / 2 - 6 - 1, actionScreen.height() / 2 + 1),
	       backButton(actionScreen.width() / 2 + 2 - 1, actionScreen.height() / 2 + 1);
	oldPasswordLabel.text("ԭ���룺  ");
	newPasswordLabel.text("�����룺  ");
	confirmPasswordLabel.text("ȷ�����룺");
	submitButton.text("ȷ��");
	backButton.text("ȡ��");
	oldPasswordBox.hidden(true);
	newPasswordBox.hidden(true);
	confirmPasswordBox.hidden(true);
	submitButton.click(changePasswordCheck);
	backButton.click(backToLastMenu);
	actionScreen.add(oldPasswordLabel);
	actionScreen.add(oldPasswordBox);
	actionScreen.add(newPasswordLabel);
	actionScreen.add(newPasswordBox);
	actionScreen.add(confirmPasswordLabel);
	actionScreen.add(confirmPasswordBox);
	actionScreen.add(submitButton);
	actionScreen.add(backButton);
	actionScreen.add(msgLabel);
	actionScreen.defaulti(6);
	return;
}

void initRoomInfoScreen(Form &actionScreen) {
	Button recordButton(4, 1),
	       deleteButton(12, 1),
		   modifyButton(20, 1),
		   backButton(actionScreen.width() - 8 - 1, 1);
	recordButton.text("¼��");
	recordButton.click(AdminActions::showMenu_1_1);
	deleteButton.text("ɾ��");
	deleteButton.click(AdminActions::showMenu_1_2);
	modifyButton.text("�޸�");
	modifyButton.click(AdminActions::showMenu_1_3);
	backButton.text("����");
	backButton.click(backToLastMenu);
	actionScreen.add(recordButton);
	actionScreen.add(deleteButton);
	actionScreen.add(modifyButton);
	actionScreen.add(backButton);
	return;
}

void initAddRoomScreen(Form &actionScreen) {
	TextBox roomNumberBox(4, 4 + rooms.size()),
	        roomTypeBox(17, 4 + rooms.size()),
			roomPriceBox(30, 4 + rooms.size());
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	if (rooms.empty()) {
		roomNumberBox.y(roomNumberBox.y() + 1);
		roomTypeBox.y(roomTypeBox.y() + 1);
		roomPriceBox.y(roomPriceBox.y() + 1);
	}
	okButton.text("ȷ��");
	okButton.click(checkNewRoom);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(roomNumberBox);
	actionScreen.add(roomTypeBox);
	actionScreen.add(roomPriceBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(3);
	return;
}

void initDeleteRoomScreen(Form &actionScreen) {
	Label roomNumberLabel(4, 1);
	TextBox roomNumberBox(12, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	roomNumberLabel.text("����ţ�");
	okButton.text("ȷ��");
	okButton.click(checkDeleteRoom);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(roomNumberLabel);
	actionScreen.add(roomNumberBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(2);
	return;
}

void initModifyRoomScreen(Form &actionScreen) {
	Label roomNumberLabel(4, 1);
	TextBox roomNumberBox(12, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	roomNumberLabel.text("����ţ�");
	okButton.text("ȷ��");
	okButton.click(checkModifyRoom);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(roomNumberLabel);
	actionScreen.add(roomNumberBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(2);
	return;
}

void initModifyActionScreen(Form &actionScreen, int roomIndex) {
	TextBox roomNumberBox(4, 4 + roomIndex),
	        roomTypeBox(17, 4 + roomIndex),
			roomPriceBox(30, 4 + roomIndex);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	ostringstream roomNumberStrOut, priceStrOut;
	roomNumberStrOut << rooms[roomIndex].roomNumber;
	priceStrOut << rooms[roomIndex].price;
	roomNumberBox.text(roomNumberStrOut.str().c_str());
	roomTypeBox.text(rooms[roomIndex].roomType);
	roomPriceBox.text(priceStrOut.str().c_str());
	okButton.text("ȷ��");
	okButton.click(checkModifyAction);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(roomNumberBox);
	actionScreen.add(roomTypeBox);
	actionScreen.add(roomPriceBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(3);
	return;
}

void initVIPInfoScreen(Form &actionScreen) {
	Button recordButton(4, 1),
	       deleteButton(12, 1),
		   modifyButton(20, 1),
		   backButton(actionScreen.width() - 8 - 1, 1);
	recordButton.text("¼��");
	recordButton.click(AdminActions::showMenu_2_1);
	deleteButton.text("ɾ��");
	deleteButton.click(AdminActions::showMenu_2_2);
	modifyButton.text("�޸�");
	modifyButton.click(AdminActions::showMenu_2_3);
	backButton.text("����");
	backButton.click(backToLastMenu);
	actionScreen.add(recordButton);
	actionScreen.add(deleteButton);
	actionScreen.add(modifyButton);
	actionScreen.add(backButton);
	return;
}

void initAddVIPScreen(Form &actionScreen) {
	TextBox vipNumberBox(4, 4 + vips.size()),
	        vipIDBox(12, 4 + vips.size()),
			vipNameBox(32, 4 + vips.size()),
			vipPhoneNumberBox(44, 4 + vips.size());
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	if (vips.empty()) {
		vipNumberBox.y(vipNumberBox.y() + 1);
		vipIDBox.y(vipIDBox.y() + 1);
		vipNameBox.y(vipNameBox.y() + 1);
		vipPhoneNumberBox.y(vipPhoneNumberBox.y() + 1);
	}
	okButton.text("ȷ��");
	okButton.click(checkNewVIP);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(vipNumberBox);
	actionScreen.add(vipIDBox);
	actionScreen.add(vipNameBox);
	actionScreen.add(vipPhoneNumberBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(4);
	return;
}

void initDeleteVIPScreen(Form &actionScreen) {
	Label vipNumberLabel(4, 1);
	TextBox vipNumberBox(10, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	vipNumberLabel.text("���ţ�");
	okButton.text("ȷ��");
	okButton.click(checkDeleteVIP);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(vipNumberLabel);
	actionScreen.add(vipNumberBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(2);
	return;
}

void initModifyVIPScreen(Form &actionScreen) {
	Label vipNumberLabel(4, 1);
	TextBox vipNumberBox(10, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	vipNumberLabel.text("���ţ�");
	okButton.text("ȷ��");
	okButton.click(checkModifyVIP);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(vipNumberLabel);
	actionScreen.add(vipNumberBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(2);
	return;
}

void initModifyVIPActionScreen(Form &actionScreen, int vipIndex) {
	TextBox vipNumberBox(4, 4 + vipIndex),
	        vipIDBox(12, 4 + vipIndex),
			vipNameBox(32, 4 + vipIndex),
			vipPhoneNumberBox(44, 4 + vipIndex);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	ostringstream vipNumberStrOut;
	vipNumberStrOut << left << setfill('0') << setw(6)
	                << vips[vipIndex].VIPCard;
	vipNumberBox.text(vipNumberStrOut.str().c_str());
	vipIDBox.text(vips[vipIndex].ID.c_str());
	vipNameBox.text(vips[vipIndex].Name.c_str());
	vipPhoneNumberBox.text(vips[vipIndex].phoneNumber.c_str());
	okButton.text("ȷ��");
	okButton.click(checkModifyVIPAction);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(vipNumberBox);
	actionScreen.add(vipIDBox);
	actionScreen.add(vipNameBox);
	actionScreen.add(vipPhoneNumberBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(4);
	return;
}

void initAddBookInfoScreen(Form &actionScreen) {
	Button recordButton(4, 1),
	       deleteButton(16, 1),
		   backButton(actionScreen.width() - 8 - 1, 1);
	recordButton.text("Ԥ������");
	recordButton.click(ServerActions::showMenu_1_1);
	deleteButton.text("�ͷ�Ԥ��");
	deleteButton.click(ServerActions::showMenu_1_2);
	backButton.text("����");
	backButton.click(backToLastMenu);
	actionScreen.add(recordButton);
	actionScreen.add(deleteButton);
	actionScreen.add(backButton);
	return;
}

void initAddBookInfoActionScreen(Form &actionScreen) {
	Label dateLabel(4, 1);
	TextBox dateBox(16, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	dateLabel.text("Ԥ��ס���ڣ�");
	okButton.text("ȷ��");
	okButton.click(checkNewBookInfoDate);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(dateLabel);
	actionScreen.add(dateBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(2);
}

void initPickEmptyUnbookedRoom(Form &actionScreen) {
	Label bookNumberLabel(4, 1);
	TextBox bookNumberBox(10, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	bookNumberLabel.text("��ţ�");
	okButton.text("ȷ��");
	okButton.click(checkPickEmptyUnbookedRoom);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(bookNumberLabel);
	actionScreen.add(bookNumberBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(2);
	return;
}

void initFormFillScreen(Form &actionScreen) {
	Label idLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 3 - 1),
	      nameLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 2 - 1);
	TextBox idBox(actionScreen.width() / 2  - 1, actionScreen.height() / 2 - 3 - 1),
	        nameBox(actionScreen.width() / 2  - 1, actionScreen.height() / 2 - 2 - 1);
	Button submitButton(actionScreen.width() / 2 - 6 - 1, actionScreen.height() / 2 + 1),
	       backButton(actionScreen.width() / 2 + 2 - 1, actionScreen.height() / 2 + 1);
	idLabel.text("���֤�ţ�");
	nameLabel.text("������    ");
	submitButton.text("ȷ��");
	submitButton.click(checkFormFill);
	backButton.text("ȡ��");
	backButton.click(backToLastMenu);
	actionScreen.add(idLabel);
	actionScreen.add(idBox);
	actionScreen.add(nameLabel);
	actionScreen.add(nameBox);
	actionScreen.add(submitButton);
	actionScreen.add(backButton);
	actionScreen.defaulti(4);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height()- 1 - 1));
	return;
}

void initInquireBasicInfoScreen(Form &actionScreen) {
	Label idLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 2 - 1),
	      dateLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 1 - 1);
	TextBox idBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 2 - 1),
	        dateBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 1 - 1);
	Button submitButton(actionScreen.width() / 2 - 6 - 1, actionScreen.height() / 2 + 1 - 1),
	       backButton(actionScreen.width() / 2 + 2 - 1, actionScreen.height() / 2 + 1 - 1);
	idLabel.text("���֤�ţ�");
	dateLabel.text("��ס���ڣ�");
	submitButton.text("ȷ��");
	submitButton.click(checkInquireBasicInfo);
	backButton.text("ȡ��");
	backButton.click(backToLastMenu);
	actionScreen.add(idLabel);
	actionScreen.add(idBox);
	actionScreen.add(dateLabel);
	actionScreen.add(dateBox);
	actionScreen.add(submitButton);
	actionScreen.add(backButton);
	actionScreen.defaulti(4);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	return;
}

void initInquireAdvancedInfoScreen(Form &actionScreen) {
	Label nameLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 3 - 1),
	      sexLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 2 - 1),
		  cashLabel(actionScreen.width() / 2 - 10 - 1, actionScreen.height() / 2 - 1 - 1);
	TextBox nameBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 3 - 1),
	        sexBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 2 - 1),
			cashBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 1 - 1);
	Button submitButton(actionScreen.width() / 2 - 6 - 1, actionScreen.height() / 2 + 1 - 1),
	       backButton(actionScreen.width() / 2 + 2 - 1, actionScreen.height() / 2 + 1 - 1);
	nameLabel.text("������    ");
	sexLabel.text("�Ա�    ");
	cashLabel.text("����Ѻ��");
	submitButton.text("ȷ��");
	submitButton.click(checkInquireAdvancedInfo);
	backButton.text("ȡ��");
	backButton.click(backToLastMenu);
	actionScreen.add(nameLabel);
	actionScreen.add(nameBox);
	actionScreen.add(sexLabel);
	actionScreen.add(sexBox);
	actionScreen.add(cashLabel);
	actionScreen.add(cashBox);
	actionScreen.add(submitButton);
	actionScreen.add(backButton);
	actionScreen.defaulti(6);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	return;
}

void initInquireRoomNumberScreen(Form &actionScreen) {
	Label roomNumberLabel(actionScreen.width() / 2 - 8 - 1, actionScreen.height() / 2 - 1 - 1);
	TextBox roomNumberBox(actionScreen.width() / 2 - 1, actionScreen.height() / 2 - 1 - 1);
	Button submitButton(actionScreen.width() / 2 - 6 - 1, actionScreen.height() / 2 + 1 - 1),
	       backButton(actionScreen.width() / 2 + 2 - 1, actionScreen.height() / 2 + 1 - 1);
	roomNumberLabel.text("����ţ�");
	submitButton.text("ȷ��");
	submitButton.click(checkInquireRoomNumber);
	backButton.text("ȡ��");
	backButton.click(backToLastMenu);
	actionScreen.add(roomNumberLabel);
	actionScreen.add(roomNumberBox);
	actionScreen.add(submitButton);
	actionScreen.add(backButton);
	actionScreen.defaulti(2);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	return;
}

void initDeleteBookInfoActionScreen(Form &actionScreen) {
	Label bookNumberLabel(4, 1);
	TextBox bookNumberBox(10, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       cancelButton(actionScreen.width() - 8 - 1, 1);
	bookNumberLabel.text("��ţ�");
	okButton.text("ȷ��");
	okButton.click(checkDeleteBookInfo);
	cancelButton.text("ȡ��");
	cancelButton.click(backToLastMenu);
	actionScreen.add(bookNumberLabel);
	actionScreen.add(bookNumberBox);
	actionScreen.add(okButton);
	actionScreen.add(cancelButton);
	actionScreen.add(Label(actionScreen.width() / 2 - 8 - 1, actionScreen.height() - 1 - 1));
	actionScreen.defaulti(2);
	return;
}

void initCustomerInfoQueryScreen(Form &actionScreen) {
	Label queryLabel(4, 1),
	      resultLabel(4, 3),
		  initialLabel(4, 4);
	TextBox queryBox(28, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       backButton(actionScreen.width() - 8 - 1, 1);
	queryLabel.text("������������һ�ֶ���Ϣ��");
	resultLabel.text("��ѯ���");
	initialLabel.text("���ı������������ݣ�ѡ�񡰲�ѯ����ť���� Enter ���������");
	okButton.text("��ѯ");
	okButton.click(customerInfoQuery);
	backButton.text("����");
	backButton.click(backToLastMenu);
	actionScreen.add(queryLabel);
	actionScreen.add(queryBox);
	actionScreen.add(okButton);
	actionScreen.add(backButton);
	actionScreen.add(resultLabel);
	actionScreen.add(initialLabel);
	actionScreen.defaulti(2);
	return;
}

void initRoomViewScreen(Form &actionScreen) {
	Label captionLabel(4, 1);
	Button backButton(actionScreen.width() - 8 - 1, 1);
	captionLabel.text("ȫ���ͷ���Ϣ��״̬");
	backButton.text("����");
	backButton.click(backToLastMenu);
	actionScreen.add(captionLabel);
	actionScreen.add(backButton);
	return;
}

void initVIPViewScreen(Form &actionScreen) {
	Label filterLabel(4, 1);
	TextBox filterBox(28, 1);
	Button okButton(actionScreen.width() - 16 - 1, 1),
	       backButton(actionScreen.width() - 8 - 1, 1);
	filterLabel.text("������������һ�ֶ���Ϣ��");
	okButton.text("ɸѡ");
	okButton.click(filterVIPInfo);
	backButton.text("����");
	backButton.click(backToLastMenu);
	actionScreen.add(filterLabel);
	actionScreen.add(filterBox);
	actionScreen.add(okButton);
	actionScreen.add(backButton);
	actionScreen.defaulti(2);
	return;
}

int sample(Form &src) {
	system("cls");
	Console currentConsole;
	currentConsole.gotoxy(2, 1);
	cout<<"���˵���δ���ɡ�";
	currentConsole.gotoxy(2, 2);
	cout<<"�ڽ��ɺ��뽫�˺�����Ϊ��ĺ�����";
	currentConsole.gotoxy(2, 4);
	system("pause");
	return Control::backReturn + 1;
}

int loginVerify(Form &src) {
	int res = checkUsers(src[2].text(), src[4].text());
	if (res != -1)
		return Control::backReturn + res;
	if (src.size() == 6) {
		src.add(Label(src.width() / 2 - 8 - 1, src.height() - 1 - 1));
		src.last().text("�û������������");
		src.last().show();
	}
	return Control::backContinue;
}

int changePassword(Form &src) {
	if (currentUserIndex == -1 || currentUserIndex > users.size()) {
		Console currentConsole;
		system("cls");
		currentConsole.gotoxy(2, 1);
		cout<<"������һ���ڲ�����";
		currentConsole.gotoxy(2, 2);
		cout<<"�����ڽ��޷��޸����롣";
		currentConsole.gotoxy(2, 3);
		cout<<"������ϸ��Ϣ��currentUserIndex ֵ��Ч";
		currentConsole.gotoxy(2, 5);
		system("pause");
		return Control::backReturn;
	}
	Form changePasswordScreen;
	initChangePasswordScreen(changePasswordScreen);
	changePasswordScreen.show();
	changePasswordScreen.onFocus();
	return Control::backReturn;
}

int changePasswordCheck(Form &src) {
	if (src[1].text() != users[currentUserIndex]->password) {
		src.last().text("      ԭ�������      ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	if (string(src[3].text()) != string(src[5].text())) {
		src.last().text("��������ȷ�����벻ƥ��");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	if (string(src[3].text()).empty()) {
		src.last().text("     ���벻��Ϊ��     ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[3].text()[i]; ++i)
		if (isspace(src[3].text()[i])) {
			src.last().text("   ���벻�ܺ��пհ�   ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	users[currentUserIndex]->password = src[3].text();
	if (!updateUserArray()) {
		src.last().text(" �����û���Ϣ�ļ�ʧ�� ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	return Control::backReturn;
}

int checkNewRoom(Form &src) {
	if (string(src[0].text()).empty() || string(src[1].text()).empty() || string(src[2].text()).empty()) {
		src.last().text("  �ֶβ���Ϊ��  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[0].text()[i]; ++i)
		if (!isdigit(src[0].text()[i])) {
			src.last().text("   ����ŷǷ�   ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (int i = 0; src[2].text()[i]; ++i)
		if (!isdigit(src[2].text()[i]) && src[2].text()[i] != '.') {
			src.last().text("  ����۸�Ƿ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (vector<Room>::size_type i = 0; i < rooms.size(); ++i)
		if (rooms[i].show_roomNumber() == atoi(src[0].text())) {
			src.last().text(" ����Ų����ظ� ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	return Control::backReturn + 1;
}

int checkDeleteRoom(Form &src) {
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i])) {
			src.last().text("   ����ŷǷ�   ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (vector<Room>::size_type i = 0; i < rooms.size(); ++i)
		if (atoi(src[1].text()) == rooms[i].show_roomNumber())
			return Control::backReturn + i + 1;
	src.last().text("  �÷��䲻����  ");
	src.last().hide();
	src.last().show();
	return Control::backContinue;
}

int checkModifyRoom(Form &src) {
	return checkDeleteRoom(src);
}

int checkModifyAction(Form &src) {
	if (string(src[0].text()).empty() || string(src[1].text()).empty() || string(src[2].text()).empty()) {
		src.last().text("  �ֶβ���Ϊ��  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[0].text()[i]; ++i)
		if (!isdigit(src[0].text()[i])) {
			src.last().text("   ����ŷǷ�   ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (int i = 0; src[2].text()[i]; ++i)
		if (!isdigit(src[2].text()[i]) && src[2].text()[i] != '.') {
			src.last().text("  ����۸�Ƿ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (vector<Room>::size_type i = 0; i < rooms.size(); ++i) {
		if (i == src[0].y() - 4)
			continue;
		if (rooms[i].show_roomNumber() == atoi(src[0].text())) {
			src.last().text(" ����Ų����ظ� ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	}
	return Control::backReturn + 1;
}

int checkNewVIP(Form &src) {
	for (vector<VIP>::size_type i = 0; i < 4; ++i)
		if (string(src[i].text()).empty()) {
			src.last().text("  �ֶβ���Ϊ��  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (int i = 0; src[0].text()[i]; ++i)
		if (!isdigit(src[0].text()[i])) {
			src.last().text("    ���ŷǷ�    ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	if (string(src[1].text()).length() != 18 && string(src[1].text()).length() != 15) {
		src.last().text("  ���֤�ŷǷ�  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i]) && src[1].text()[i] != 'X') {
			src.last().text("  ���֤�ŷǷ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (int i = 0; src[3].text()[i]; ++i)
		if (!isdigit(src[3].text()[i])) {
			src.last().text("  �绰����Ƿ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (vector<VIP>::size_type i = 0; i < vips.size(); ++i)
		if (vips[i].VIPCard == atoi(src[0].text())) {
			src.last().text("  ���Ų����ظ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	return Control::backReturn + 1;
}

int checkDeleteVIP(Form &src) {
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i])) {
			src.last().text("    ���ŷǷ�    ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (vector<VIP>::size_type i = 0; i < vips.size(); ++i)
		if (atoi(src[1].text()) == vips[i].VIPCard)
			return Control::backReturn + i + 1;
	src.last().text("  ��VIP�������� ");
	src.last().hide();
	src.last().show();
	return Control::backContinue;
}

int checkModifyVIP(Form &src) {
	return checkDeleteVIP(src);
}

int checkModifyVIPAction(Form &src) {
	for (vector<VIP>::size_type i = 0; i < 4; ++i)
		if (string(src[i].text()).empty()) {
			src.last().text("  �ֶβ���Ϊ��  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (int i = 0; src[0].text()[i]; ++i)
		if (!isdigit(src[0].text()[i])) {
			src.last().text("    ���ŷǷ�    ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	if (string(src[1].text()).length() != 18 && string(src[1].text()).length() != 15) {
		src.last().text("  ���֤�ŷǷ�  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i]) && src[1].text()[i] != 'X') {
			src.last().text("  ���֤�ŷǷ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (int i = 0; src[3].text()[i]; ++i)
		if (!isdigit(src[3].text()[i])) {
			src.last().text("  �绰����Ƿ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	for (vector<Room>::size_type i = 0; i < rooms.size(); ++i) {
		if (i == src[0].y() - 4)
			continue;
		if (rooms[i].show_roomNumber() == atoi(src[0].text())) {
			src.last().text("  ���Ų����ظ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	}
	return Control::backReturn + 1;
}

int checkNewBookInfoDate(Form &src) {
	if (string(src[1].text()).length() != 8) {
		src.last().text("    ������Ч    ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i])) {
			src.last().text("    ������Ч    ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	return Control::backReturn + 1;
}

int checkNewBookInfo(Form &src) {
	sample(src);
}

int checkPickEmptyUnbookedRoom(Form &src) {
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i])) {
			src.last().text("    ��ŷǷ�    ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	if (atoi(src[1].text()) < 1) {
		src.last().text("    ��ŷǷ�    ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	return Control::backReturn + atoi(src[1].text());
}

int checkFormFill(Form &src) {
	if (string(src[1].text()).empty() || string(src[3].text()).empty()) {
		src.last().text("  �ֶβ���Ϊ��  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	if (string(src[1].text()).length() != 18 && string(src[1].text()).length() != 15) {
		src.last().text("  ���֤�ŷǷ�  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i]) && src[1].text()[i] != 'X') {
			src.last().text("  ���֤�ŷǷ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	return Control::backReturn + 1;
}

int checkInquireBasicInfo(Form &src) {
	if (string(src[1].text()).empty() || string(src[3].text()).empty()) {
		src.last().text("  �ֶβ���Ϊ��  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	if (string(src[1].text()).length() != 18 && string(src[1].text()).length() != 15) {
		src.last().text("  ���֤�ŷǷ�  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	int i = 0;
	for (i = 0; src[1].text()[i + 1]; ++i)
		if (!isdigit(src[1].text()[i])) {
			src.last().text("  ���֤�ŷǷ�  ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	if (!isdigit(src[1].text()[i]) && src[1].text()[i] != 'X') {
		src.last().text("  ���֤�ŷǷ�  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	if (string(src[3].text()).length() != 8) {
		src.last().text("    ���ڷǷ�    ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	return Control::backReturn + 1;
}

int checkInquireAdvancedInfo(Form &src) {
	if (string(src[1].text()).empty() || string(src[3].text()).empty() || string(src[5].text()).empty()) {
		src.last().text("  �ֶβ���Ϊ��  ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[5].text()[i]; ++i)
		if (!isdigit(src[5].text()[i]) && src[5].text()[i] != '.') {
			src.last().text("  ����Ѻ����Ч  ");
			src.last().text()[0] = i + '0';
			src.last().text()[14] = (!isdigit(src[3].text()[i])) + '0';
			src.last().text()[15] = (src[3].text()[i] != '.') + '0';
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	return Control::backReturn + 1;
}

int checkInquireRoomNumber(Form &src) {
	if (string(src[1].text()).empty()) {
		src.last().text(" ����Ų���Ϊ�� ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i])) {
			src.last().text("   ����ŷǷ�   ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	int guestMatch = -1;
	for (int i = 0; i < guests.size(); ++i)
		if (guests[i].getRoom()->show_roomNumber() == atoi(src[1].text())) {	
			guestMatch = i;
			break;
		}
	if (guestMatch == -1) {
		src.last().text(" û�ж�Ӧ����Ϣ ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	return Control::backReturn + guestMatch + 1;
}

int checkDeleteBookInfo(Form &src) {
	if (string(src[1].text()).empty()) {
		src.last().text("    �����Ч    ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	for (int i = 0; src[1].text()[i]; ++i)
		if (!isdigit(src[1].text()[i])) {
			src.last().text("    �����Ч    ");
			src.last().hide();
			src.last().show();
			return Control::backContinue;
		}
	if (atoi(src[1].text()) > bookings.size() || atoi(src[1].text()) < 1) {
		src.last().text("    �����Ч    ");
		src.last().hide();
		src.last().show();
		return Control::backContinue;
	}
	return Control::backReturn + atoi(src[1].text());
}

int customerInfoQuery(Form &src) {
	Console currentConsole;
	int prevX = currentConsole.getX(),
	    prevY = currentConsole.getY();
	for (int i = 4; i < currentConsole.getSizeY(); ++i) {
		currentConsole.gotoxy(4, i);
		for (int j = 4; j < currentConsole.getSizeX(); ++j)
			cout << " ";
	}
	if (string(src[1].text()).empty()) {
		currentConsole.gotoxy(4, 4);
		cout << "���ı������������ݣ�ѡ�񡰲�ѯ����ť���� Enter ���������";
		currentConsole.gotoxy(prevX, prevY);
		return Control::backContinue;
	}
	vector<BookInfo *> foundBookings;
	for (vector<BookInfo>::size_type i = 0; i < bookings.size(); ++i)
		if (string(src[1].text()) == bookings[i].id || string(src[1].text()) == bookings[i].name)
			foundBookings.push_back(&bookings[i]);
	vector<VIP *> foundVIPs;
	for (vector<VIP>::size_type i = 0; i < vips.size(); ++i)
		if (atoi(src[1].text()) == vips[i].VIPCard || string(src[1].text()) == vips[i].ID || string(src[1].text()) == vips[i].Name || string(src[1].text()) == vips[i].phoneNumber)
			foundVIPs.push_back(&vips[i]);
	vector<EntranceInfo *> foundGuests;
	for (vector<EntranceInfo>::size_type i = 0; i < guests.size(); ++i)
		if (string(src[1].text()) == guests[i].id || string(src[1].text()) == guests[i].name)
			foundGuests.push_back(&guests[i]);
	int line = 4;
	currentConsole.gotoxy(4, line++);
	cout << "Ԥ����Ϣ (" << foundBookings.size() << "��)";
	if (foundBookings.size() > 0) {
		currentConsole.gotoxy(4, line++);
		cout << "���֤��            ����        �����  Ԥ��ס����";
		for (vector<BookInfo *>::size_type i = 0; i < foundBookings.size(); ++i) {
			currentConsole.gotoxy(4, line++);
			cout << *foundBookings[i];
		}
	}
	++line;
	currentConsole.gotoxy(4, line++);
	cout << "VIP ����Ϣ (" << foundVIPs.size() << "��)";
	if (foundVIPs.size() > 0) {
		currentConsole.gotoxy(4, line++);
		cout << "����    ���֤��            ����        �绰����     ���� ";
		for (vector<VIP *>::size_type i = 0; i < foundVIPs.size(); ++i) {
			currentConsole.gotoxy(4, line++);
			cout << *foundVIPs[i];
		}
	}
	++line;
	currentConsole.gotoxy(4, line++);
	cout << "��ס��Ϣ (" << foundGuests.size() << "��)";
	if (foundGuests.size() > 0) {
		currentConsole.gotoxy(4, line++);
		cout << "���֤��            ����        �Ա�  �����  ��ס����  ����Ѻ��";
		for (vector<EntranceInfo *>::size_type i = 0; i < foundGuests.size(); ++i) {
			currentConsole.gotoxy(4, line++);
			cout << *foundGuests[i];
		}
	}
	currentConsole.gotoxy(prevX, prevY);
}

int filterVIPInfo(Form &src) {
	if (string(src[1].text()).empty()) {
		displayAllVIPs();
		return Control::backContinue;
	}
	vector<VIP> foundVIPs;
	for (vector<VIP>::size_type i = 0; i < vips.size(); ++i) {
		if (vips[i].VIPCard == atoi(src[1].text()) || vips[i].ID == src[1].text() || vips[i].Name == src[1].text() || vips[i].phoneNumber == src[1].text())
			foundVIPs.push_back(vips[i]);
	}
	Console currentConsole;
	int prevX = currentConsole.getX(),
	    prevY = currentConsole.getY();
	for (vector<VIP>::size_type i = 0; i < vips.size(); ++i) {
		currentConsole.gotoxy(4, 4 + i);
		for (int j = 0; j < 6 + 2 + 18 + 2 + 10 + 2 + 11 + 2 + 5; ++j)
			cout << " ";
	}
	if (foundVIPs.empty()) {
		currentConsole.gotoxy(4, 4);
		cout << "(��)";
	} else {
		for (vector<VIP>::size_type i = 0; i < foundVIPs.size(); ++i) {
			currentConsole.gotoxy(4, 4 + i);
			cout << foundVIPs[i];
		}
	}
	currentConsole.gotoxy(prevX, prevY);
	return Control::backContinue;
}

int backToLastMenu(Form &src) {
	return Control::backReturn;
}

int exitFromSystem(Form &src) {
    exit(0);
}

void displayAllRooms() {
	Console currentConsole;
	int prevX = currentConsole.getX(),
	    prevY = currentConsole.getY();
	currentConsole.gotoxy(4, 3);
	cout << "�����       ��������     �۸�(Ԫ/��)  �Ƿ����   " << endl;
	if (rooms.empty()) {
		currentConsole.gotoxy(4, 4);
		cout << "(��)";
	} else {
		for (vector<Room>::size_type i = 0; i < rooms.size(); ++i) {
			currentConsole.gotoxy(4, i + 4);
			cout << rooms[i];
		}
	}
	currentConsole.gotoxy(prevX, prevY);
	return;
}

vector<Room *> displaySpareRooms() {
	Console currentConsole;
	int prevX = currentConsole.getX(),
	    prevY = currentConsole.getY();
	currentConsole.gotoxy(4, 3);
	cout << "���  �����       ��������     �۸�(Ԫ/��)  �Ƿ����   " << endl;
	vector<Room *> spareRooms;
	findSpareRooms(spareRooms);
	if (spareRooms.empty()) {
		currentConsole.gotoxy(4, 4);
		cout << "(��)";
	} else {
		for (vector<Room>::size_type i = 0; i < spareRooms.size(); ++i) {
			currentConsole.gotoxy(4, i + 4);
			cout << left << setw(4) << i + 1 << "  " << *spareRooms[i];
		}
	}
	currentConsole.gotoxy(prevX, prevY);
	return spareRooms;
}

vector<Room *> displayUnbookedSpareRooms(int date) {
	Console currentConsole;
	int prevX = currentConsole.getX(),
	    prevY = currentConsole.getY();
	currentConsole.gotoxy(4, 3);
	cout << "���  �����       ��������     �۸�(Ԫ/��)  �Ƿ����   " << endl;
	vector<Room *> spareRooms;
	findUnbookedSpareRooms(spareRooms, date);
	if (spareRooms.empty()) {
		currentConsole.gotoxy(4, 4);
		cout << "(��)";
	} else {
		for (vector<Room>::size_type i = 0; i < spareRooms.size(); ++i) {
			currentConsole.gotoxy(4, i + 4);
			cout << left << setw(4) << i + 1 << "  " << *spareRooms[i];
		}
	}
	currentConsole.gotoxy(prevX, prevY);
	return spareRooms;
}

void displayAllVIPs() {
	Console currentConsole;
	int prevX = currentConsole.getX(),
	    prevY = currentConsole.getY();
	currentConsole.gotoxy(4, 3);
	cout << "����    ���֤��            ����        �绰����     ���� " << endl;
	if (vips.empty()) {
		currentConsole.gotoxy(4, 4);
		cout << "(��)";
	} else {
		for (vector<VIP>::size_type i = 0; i < vips.size(); ++i) {
			currentConsole.gotoxy(4, i + 4);
			cout << vips[i];
		}
	}
	currentConsole.gotoxy(prevX, prevY);
	return;
}

void displayAllBookInfos() {
	Console currentConsole;
	int prevX = currentConsole.getX(),
	    prevY = currentConsole.getY();
	currentConsole.gotoxy(4, 3);
	cout << "���  ���֤��            ����        �����  Ԥ��ס����" << endl;
	if (bookings.empty()) {
		currentConsole.gotoxy(4, 4);
		cout << "(��)";
	} else {
		for (vector<BookInfo>::size_type i = 0; i < bookings.size(); ++i) {
			currentConsole.gotoxy(4, i + 4);
			cout << left << setw(4) << i + 1 << "  " << bookings[i];
		}
	}
	currentConsole.gotoxy(prevX, prevY);
	return;
}

void findSpareRooms(vector<Room *> &res) {
	for (vector<Room>::size_type i = 0; i < rooms.size(); ++i)
		if (rooms[i].isSpare)
			res.push_back(&rooms[i]);
	sort(res.begin(), res.end());
	return;
}

void findUnbookedSpareRooms(vector<Room *> &res, int date) {
	findSpareRooms(res);
	for (vector<BookInfo>::size_type i = 0; i < bookings.size(); ++i)
		if (bookings[i].date != date)
			res.push_back(bookings[i].attachedRoom);
	sort(res.begin(), res.end());
	return;
}
