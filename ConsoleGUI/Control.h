// Control.h
// 本头文件中包含与一些 "GUI" 控件相关的类声明及定义。

#ifndef CONTROL_H
#define CONTROL_H

#include "../HMS.h"

class Control_base;
class Form;
class Control;
class Label;
class TextBox;
class Button;
class Menu;

class Control_base {
public:
	Control_base();
	virtual ~Control_base();
	virtual void show() = 0;
	virtual void hide() = 0;
};

class Form : public Control_base {
private:
	static const int CONTROL_MAX_SIZE = 20;
	int controlSize;
	int defaultControlIndex;
	Control *controls[CONTROL_MAX_SIZE];
	Console attachedConsole;
public:
	Form(const Console &_attachedConsole = Console());
	Form(const Form &rhs);
	virtual ~Form();
	virtual void show();
	virtual void hide();
	int onFocus(int initialIndex = 0);
	int size();
	int width();
	int height();
	int defaulti();
	void defaulti(int _defaultControlIndex = -1);
	Console &console();
	void console(const Console &console);
	void add(const Label &rhs);
	void add(const TextBox &rhs);
	void add(const Button &rhs);
	void add(const Menu &rhs);
	void clear();
	Control &operator[](int index);
	Control &last();
};

class Control : public Control_base {
	friend class Form;
protected:
	static const int TEXTSTR_MAX_SIZE = 100;
	int coordinateX, coordinateY;
	Form *attachedForm;
	char textStr[TEXTSTR_MAX_SIZE];
	int textStrLength();
	virtual int onFocus() = 0;
	virtual int onKey(char key) = 0;
public:
	static const int mod = 10000000;
	static const int backContinue = mod * 1, backBreak = mod * 2, backReturn = mod * 3;
	Control(int _coordinateX, int _coordinateY);
	Control(const Control &rhs);
	virtual ~Control();
	virtual void show() = 0;
	virtual void hide() = 0;
	int x();
	int y();
	void x(int _coordinateX);
	void y(int _coordinateY);
	char *text();
	void text(const char *_textStr);
};

class Label :public Control {
private:
	virtual int onFocus();
	virtual int onKey(char key);
public:
	Label(int _coordinateX, int _coordinateY);
	Label(const Label &rhs);
	virtual ~Label();
	virtual void show();
	virtual void hide();
};

class TextBox : public Control {
private:
	int maxTextStrLength;
	bool characterHidden;
	virtual int onFocus();
	virtual int onKey(char key);
public:
	TextBox(int _coordinateX, int _coordinateY);
	TextBox(const TextBox &rhs);
	virtual ~TextBox();
	virtual void show();
	virtual void hide();
	bool hidden();
	void hidden(bool _charcactersHidden);
};

class Button : public Control {
	friend class Menu;
private:
	int(*onClick)(Form &attachedForm);
	virtual int onFocus();
	void deFocus();
	virtual int onKey(char key);
public:
	Button(int _coordinateX, int _coordinateY);
	Button(const Button &rhs);
	~Button();
	virtual void show();
	virtual void hide();
	int click();
	void click(int(*_onClick)(Form &attachedForm));
};

class Menu : public Control {
private:
	static const int BUTTONLIST_MAX_SIZE = 20;
	int buttonSize;
	int currentPosition;
	Button *buttonList[BUTTONLIST_MAX_SIZE];
	virtual int onFocus();
	virtual int onKey(char key);
public:
	Menu(int _coordinateX, int _coordinateY);
	Menu(const Menu &rhs);
	~Menu();
	virtual void show();
	virtual void hide();
	int size();
	void add(const char *_textStr = "");
	Button &operator[](int index);
	Button &last();
};

#endif
