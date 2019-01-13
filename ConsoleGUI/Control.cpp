// Control.cpp
// 本源文件中包含 Control.h 中的类成员函数定义。

#include "../HMS.h"

#include <conio.h>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

Control_base::Control_base() {}

Control_base::~Control_base() {}

Form::Form(const Console &_attachedConsole) : controlSize(0), defaultControlIndex(-1), attachedConsole(_attachedConsole) {
	for (int i = 0; i < CONTROL_MAX_SIZE; ++i)
		controls[i] = NULL;
}

Form::Form(const Form &rhs) : controlSize(rhs.controlSize), defaultControlIndex(rhs.defaultControlIndex), attachedConsole(rhs.attachedConsole) {
	for (int i = 0; i < CONTROL_MAX_SIZE; ++i)
		controls[i] = rhs.controls[i];
}

Form::~Form() {
	hide();
	for (int i = 0; i < controlSize; ++i)
		if (controls[i] != NULL) {
			delete controls[i];
			controls[i] = NULL;
		}
	attachedConsole.gotoxy(0, 0);
}

int Form::onFocus(int initialIndex) {
	if (controlSize == 0)
		return -1;
	if (initialIndex < 0)
		initialIndex = 0;
	if (initialIndex > controlSize - 1)
		initialIndex = controlSize - 1;
	for (int i = initialIndex; ; i = (i + 1) % controlSize) {
		if (controls[i]->onFocus() == Control::backContinue)
			while (true) {
				char key = _getch();
				int returnValue = Control::backContinue;
				if (key == '\r') {
					if (defaultControlIndex != -1)
						returnValue = controls[defaultControlIndex]->onKey(' ');
				}
				else
					returnValue = controls[i]->onKey(key);
				if (returnValue / Control::mod == Control::backBreak / Control::mod)
					break;
				else if (returnValue / Control::mod == Control::backReturn / Control::mod)
					return returnValue % Control::mod;
			}
	}
	return -1;
}

void Form::show() {
	hide();
	for (int k = 0; k < controlSize; ++k)
		controls[k]->show();
	return;
}

void Form::hide() {
	system("cls");
	return;
}

int Form::size() {
	return controlSize;
}

int Form::width() {
	return attachedConsole.getSizeX();
}

int Form::height() {
	return attachedConsole.getSizeY();
}

int Form::defaulti() {
	return defaultControlIndex;
}

void Form::defaulti(int _defaultControlIndex) {
	defaultControlIndex = _defaultControlIndex;
	return;
}

Console &Form::console() {
	return attachedConsole;
}

void Form::console(const Console &_attachedConsole) {
	attachedConsole = _attachedConsole;
	return;
}

void Form::add(const Label &rhs) {
	if (controlSize < CONTROL_MAX_SIZE) {
		controls[controlSize] = new Label(rhs);
		controls[controlSize]->attachedForm = this;
		++controlSize;
	}
}

void Form::add(const TextBox &rhs) {
	if (controlSize < CONTROL_MAX_SIZE) {
		controls[controlSize] = new TextBox(rhs);
		controls[controlSize]->attachedForm = this;
		++controlSize;
	}
}

void Form::add(const Button &rhs) {
	if (controlSize < CONTROL_MAX_SIZE) {
		controls[controlSize] = new Button(rhs);
		controls[controlSize]->attachedForm = this;
		++controlSize;
	}
}

void Form::add(const Menu &rhs) {
	if (controlSize < CONTROL_MAX_SIZE) {
		controls[controlSize] = new Menu(rhs);
		controls[controlSize]->attachedForm = this;
		++controlSize;
	}
}

void Form::clear() {
	for (int i=0; i<controlSize; ++i)
		if (controls[i] != NULL) {
			delete controls[i];
			controls[i] = NULL;
		}
}

Control &Form::operator[](int index) {
	if (index < 0)
		index = 0;
	else if (index > controlSize - 1)
		index = controlSize - 1;
	return *controls[index];
}

Control &Form::last() {
	return *controls[size() - 1];
}

Control::Control(int _coordinateX, int _coordinateY) : coordinateX(_coordinateX), coordinateY(_coordinateY), attachedForm(NULL) {
	text("");
}

Control::Control(const Control &rhs) : coordinateX(rhs.coordinateX), coordinateY(rhs.coordinateY), attachedForm(rhs.attachedForm) {
	text(rhs.textStr);
}

Control::~Control() {}

int Control::textStrLength() {
	int res = 0;
	for (res = 0; res < TEXTSTR_MAX_SIZE && textStr[res]; ++res);
	return res;
}

int Control::x() {
	return coordinateX;
}

int Control::y() {
	return coordinateY;
}

void Control::x(int _coordinateX) {
	coordinateX = _coordinateX;
	hide();
	show();
}

void Control::y(int _coordinateY) {
	coordinateY = _coordinateY;
	hide();
	show();
}

char *Control::text() {
	return textStr;
}

void Control::text(const char *_textStr) {
	int i = 0;
	for (i = 0; i < TEXTSTR_MAX_SIZE && (textStr[i] = _textStr[i]); ++i);
	for (; i < TEXTSTR_MAX_SIZE; ++i)
		textStr[i] = '\0';
	return;
}

Label::Label(int _coordinateX, int _coordinateY) : Control(_coordinateX, _coordinateY) {
	text("");
}

Label::Label(const Label &rhs) : Control(rhs) {
	text(rhs.textStr);
}

Label::~Label() {
	hide();
}

int Label::onFocus() {
	return Control::backBreak;
}

int Label::onKey(char key) {
	return Control::backBreak;
}

void Label::show() {
	if (attachedForm == NULL)
		return;
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	attachedForm->console().gotoxy(coordinateX, coordinateY);
	cout << textStr;
	attachedForm->console().gotoxy(prevX, prevY);
	return;
}

void Label::hide() {
	if (attachedForm == NULL)
		return;
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	attachedForm->console().gotoxy(coordinateX, coordinateY);
	for (int i = 0; i < TEXTSTR_MAX_SIZE && textStr[i]; ++i)
		cout << " ";
	attachedForm->console().gotoxy(prevX, prevY);
	return;
}

TextBox::TextBox(int _coordinateX, int _coordinateY) : Control(_coordinateX, _coordinateY), maxTextStrLength(0), characterHidden(false) {}

TextBox::TextBox(const TextBox &rhs) : Control(rhs), maxTextStrLength(rhs.maxTextStrLength), characterHidden(rhs.characterHidden) {}

TextBox::~TextBox() {
	hide();
}

int TextBox::onFocus() {
	attachedForm->console().setVisiblity(true);
	attachedForm->console().gotoxy(coordinateX + textStrLength(), coordinateY);
	return backContinue;
}

int TextBox::onKey(char key) {
	if (key == '\t')
		return Control::backBreak;
	else if (key == '\b') {
		int currentTextStrLength = textStrLength();
		if (currentTextStrLength != 0) {
			cout << "\b";
			cout << " ";
			cout << "\b";
			textStr[--currentTextStrLength] = '\0';
			return Control::backContinue;
		}
	}
	else if (maxTextStrLength == 0 || textStrLength() < maxTextStrLength) {
		textStr[textStrLength()] = key;
		cout << (characterHidden ? '*' : key);
	}
	return Control::backContinue;
}

void TextBox::show() {
	if (attachedForm == NULL)
		return;
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	attachedForm->console().gotoxy(coordinateX, coordinateY);
	cout << textStr;
	attachedForm->console().gotoxy(prevX, prevY);
	return;
}

void TextBox::hide() {
	if (attachedForm == NULL)
		return;
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	attachedForm->console().gotoxy(coordinateX, coordinateY);
	for (int i = 0; i < TEXTSTR_MAX_SIZE && textStr[i]; ++i)
		cout << " ";
	attachedForm->console().gotoxy(prevX, prevY);
	return;
}

bool TextBox::hidden() {
	return characterHidden;
}

void TextBox::hidden(bool _characterHidden) {
	characterHidden = _characterHidden;
	hide();
	show();
	return;
}

Button::Button(int _coordinateX, int _coordinateY) : Control(_coordinateX, _coordinateY), onClick(NULL) {}

Button::Button(const Button &rhs) : Control(rhs), onClick(rhs.onClick) {}

Button::~Button() {
	hide();
}

int Button::onFocus() {
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	attachedForm->console().setVisiblity(false);
	attachedForm->console().gotoxy(coordinateX - 2, coordinateY);
	cout << ">";
	attachedForm->console().gotoxy(coordinateX + textStrLength() + 1, coordinateY);
	cout << "<";
	attachedForm->console().gotoxy(prevX, prevY);
	return backContinue;
}

void Button::deFocus() {
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	attachedForm->console().gotoxy(coordinateX - 2, coordinateY);
	cout << " ";
	attachedForm->console().gotoxy(coordinateX + textStrLength() + 1, coordinateY);
	cout << " ";
	attachedForm->console().gotoxy(prevX, prevY);
	return;
}

int Button::onKey(char key) {
	if (key == ' ') {
		int returnValue = click();
		if (returnValue / Control::mod != Control::backContinue / Control::mod)
			deFocus();
		return returnValue;
	}
	else if (key == '\t') {
		deFocus();
		return Control::backBreak;
	}
	else {
		return Control::backContinue;
	}
}

void Button::show() {
	if (attachedForm == NULL)
		return;
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	attachedForm->console().gotoxy(coordinateX, coordinateY);
	cout << textStr;
	attachedForm->console().gotoxy(prevX, prevY);
	return;
}

void Button::hide() {
	if (attachedForm == NULL)
		return;
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	attachedForm->console().gotoxy(coordinateX, coordinateY);
	for (int i = 0; i < TEXTSTR_MAX_SIZE && textStr[i]; ++i)
		cout << " ";
	attachedForm->console().gotoxy(prevX, prevY);
	return;
}

int Button::click() {
	if (onClick != NULL)
		return onClick(*attachedForm);
	return Control::backContinue;
}

void Button::click(int(*_onClick)(Form &attachedForm)) {
	onClick = _onClick;
	return;
}

Menu::Menu(int _coordinateX, int _coordinateY) : Control(_coordinateX, _coordinateY), buttonSize(0), currentPosition(0) {
	for (int i = 0; i < BUTTONLIST_MAX_SIZE; ++i)
		buttonList[i] = NULL;
}

Menu::Menu(const Menu &rhs) : Control(rhs), buttonSize(rhs.buttonSize), currentPosition(rhs.currentPosition) {
	for (int i = 0; i < buttonSize; ++i)
		buttonList[i] = new Button(*rhs.buttonList[i]);
}

Menu::~Menu() {
	hide();
	for (int i = 0; i < BUTTONLIST_MAX_SIZE; ++i)
		if (buttonList[i] != NULL) {
			delete buttonList[i];
			buttonList[i] = NULL;
		}
}

int Menu::onFocus() {
	if (buttonSize == 0)
		return Control::backBreak;
	buttonList[currentPosition]->onFocus();
	return Control::backContinue;
}

int Menu::onKey(char key) {
	if (key == '\t') {
		if (currentPosition + 1 < buttonSize) {
			buttonList[currentPosition]->deFocus();
			++currentPosition;
			buttonList[currentPosition]->onFocus();
			return Control::backContinue;
		}
		else {
			buttonList[currentPosition]->deFocus();
			currentPosition = (currentPosition + 1) % buttonSize;
			return Control::backBreak;
		}
	}
	else if (key == ' ') {
		return buttonList[currentPosition]->click();
	}
	return backContinue;
}

void Menu::show() {
	if (attachedForm == NULL)
		return;
	for (int i = 0; i < buttonSize; ++i)
		buttonList[i]->attachedForm = attachedForm;
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	for (int i = 0; i < buttonSize; ++i)
		buttonList[i]->show();
	attachedForm->console().gotoxy(prevX, prevY);
	return;
}

void Menu::hide() {
	if (attachedForm == NULL)
		return;
	int prevX = attachedForm->console().getX(),
		prevY = attachedForm->console().getY();
	for (int i = 0; i < buttonSize; ++i)
		buttonList[i]->hide();
	return;
}

int Menu::size() {
	return buttonSize;
}

void Menu::add(const char *_textStr) {
	if (buttonSize < BUTTONLIST_MAX_SIZE) {
		buttonList[buttonSize] = new Button(coordinateX, coordinateY + buttonSize);
		buttonList[buttonSize]->text(_textStr);
		++buttonSize;
	}
	return;
}

Button &Menu::operator[](int index) {
	if (index < 0)
		index = 0;
	else if (index > buttonSize)
		index = buttonSize;
	return *buttonList[index];
}

Button &Menu::last() {
	return *buttonList[size() - 1];
}
