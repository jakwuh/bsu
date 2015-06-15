#include "ui/all.h"
#include <map>
#include <string>

std::map<std::string, UI*> ui;
HINSTANCE hI;

void home();
void login();
void go();

int WINAPI WinMain(HINSTANCE hI_, HINSTANCE hPI, LPSTR lpCmdLine, int nCmdShow)
{
	try {
		hI = hI_;
		login();
		Window::initialize();
		for (auto it : ui) delete it.second;
	}
	catch (Exception& e) {
		MessageBox(NULL, e.what(), "ERROR", MB_OK);
		exit(0);
	}
	catch (...) {
		MessageBox(NULL, "Unknown error", "ERROR", MB_OK);
		exit(0);
	}
	return 0;
}

void login()
{
	Window* window = new Window(hI);
	window->resize(600, 400);
	window->setPosition(Position::hcenter, Position::vcenter);
	window->setText("Тестовое окно");
	window->show();
	ui["window"] = window;

	Label* labelName = new Label(hI, ui["window"]);
	labelName->resize(200,25);
	labelName->setPosition(Position::hcenter, 300);
	labelName->show();
	ui["labelName"] = labelName;

	Edit* editName = new Edit(hI, ui["window"]);
	editName->resize(200, 100);
	editName->setPosition(Position::hcenter, 200);
	editName->show();
	editName->on(Action::focus, go);
	ui["editName"] = editName;

	Button* buttonExit = new Button(hI, ui["window"]);
	buttonExit->resize(200, 100);
	buttonExit->setPosition(Position::hcenter, 100);
	buttonExit->setText("Выход");
	buttonExit->setFont(fonts::button_text);
	buttonExit->show();
	buttonExit->on(Action::click, home);
	ui["buttonExit"] = buttonExit;

	CheckBox* checkBox = new CheckBox(hI, ui["window"]);
	checkBox->resize(100, 20);
	checkBox->setPosition(Position::hcenter, 0);
	checkBox->setText("blavla");
	checkBox->show();
	checkBox->on(Action::click, go);
	ui["checkBox"] = checkBox;
}

void go()	
{
	Popup::show(hI, *ui["window"], "hihihi");
	// CheckBox* checkBox = dynamic_cast<CheckBox*>(ui["checkBox"]);
	// checkBox->setState(true);
	// MessageBox(NULL, Window::saveFile().c_str(), "SDfd", MB_OK);
}

void home()
{
	ui["labelName"]->hide();
	ui["editName"]->hide();
	ui["buttonExit"]->hide();

	ComboBox* comboBox = new ComboBox(hI, ui["window"]);
	comboBox->resize(100, 300);
	comboBox->setPosition(Position::hcenter, 50);
	comboBox->show();
	comboBox->addItem("jim");
	comboBox->addItem("marina");
	comboBox->addItem("marina");
	comboBox->deleteItem(2);
	ui["comboBox"] = comboBox;

	TextBox* textBox = new TextBox(hI, ui["window"]);
	textBox->resize(200,100);
	textBox->setPosition(Position::hcenter, 325);
	textBox->show();
	textBox->setText("test\nsfsd\nsfsdf");
	ui["textBox"] = textBox;

	EditBox* editBox = new EditBox(hI, ui["window"]);
	editBox->resize(200, 100);
	editBox->setPosition(Position::hcenter, 425);
	editBox->show();
	ui["editBox"] = editBox;

    // Timer* timer = new Timer(hI, ui["window"]);
    // timer->begin(500);

    Grid* grid = new Grid(hI, ui["window"]);
    grid->resize(200, 200);
    grid->setPosition(Position::hcenter, 100);
    grid->show();
    grid->addColumn("james", 0, 100);
    grid->addColumn("marina", 1, 100);
    std::vector<std::string> row;
    row.push_back("test1");
    row.push_back("test2");
    grid->addRow(row);
    grid->addRow(row);
    grid->addRow(row);
    grid->getSelectedId();
    grid->on(Action::select, go);
    ui["grid"] = grid;
}

// #include <iostream>
// #include <fstream>
// #include "binary/binary.h"
// #include "binary/utils.h"

// using namespace std;

// class Test : public Binary::Binary
// {
// public:
// 	Test(){};
// 	int x, y, z;
// 	friend std::ostream& operator << (std::ostream& out, Test const& t)
// 	{
// 		out << t.x << ' ' << t.y << ' ' << t.z;
// 		return out;
// 	}

// };

// int main()
// {
// 	// ifstream in("out.bin", ios::in | ios::binary);
// 	// ofstream out("out.bin", ios::out | ios::binary);
// 	// stringstream ss;
// 	// Test a, b, c, d;
// 	// a.x = a.y = a.z = 1;
// 	// c.x = c.y = c.z = 2;
// 	// out << a << b << c;
// 	// out.close();
// 	// in.close();
// 	system("pause");
// }