#include "ui/all.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "comp.h"
#include "bag.h"
#include "market.h"
#include "comp_template.h"

std::map<std::string, UI*> ui;
HINSTANCE hI;
COMP<Comp> Comps;
COMP<Comp> Comps1;
COMP<Comp> Comps2;
COMP<Bag> Bags;
COMP<Bag> Bags1;
COMP<Bag> Bags2;
COMP<Market> Markets;
COMP<Market> Markets1;
COMP<Market> Markets2;

void build();
void buildBag();
void buildComp();
void buildMarket();
void intro();
void comp();
void bag();
void market();

void loadComp1();
void saveComp1();
void saveFormatComp1();
void sortComp1();
void loadComp2();
void saveComp2();
void saveFormatComp2();
void sortComp2();
void searchComp();

void loadBag1();
void saveBag1();
void saveFormatBag1();
void sortBag1();
void loadBag2();
void saveBag2();
void saveFormatBag2();
void sortBag2();
void searchBag();

void loadMarket1();
void saveMarket1();
void saveFormatMarket1();
void sortMarket1();
void loadMarket2();
void saveMarket2();
void saveFormatMarket2();
void sortMarket2();
void searchMarket();

int WINAPI WinMain(HINSTANCE hI_, HINSTANCE hPI, LPSTR lpCmdLine, int nCmdShow)
{
	try {
		setlocale(LC_ALL, "CP1251");
		hI = hI_;
		build();
		intro();
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

void build()
{
	Window* window = new Window(hI);
	window->resize(600, 400);
	window->setPosition(Position::hcenter, Position::vcenter);
	window->setText("Магазин");
	ui["window"] = window;

	Button* buttonComp = new Button(hI, ui["window"]);
	buttonComp->resize(200, 100);
	buttonComp->setPosition(Position::hcenter, 0);
	buttonComp->setText("Comp");
	buttonComp->setFont(fonts::button_text);
	buttonComp->on(Action::click, comp);
	ui["buttonComp"] = buttonComp;

	Button* buttonBag = new Button(hI, ui["window"]);
	buttonBag->resize(200, 100);
	buttonBag->setPosition(Position::hcenter, 120);
	buttonBag->setText("Bag");
	buttonBag->setFont(fonts::button_text);
	buttonBag->on(Action::click, bag);
	ui["buttonBag"] = buttonBag;

	Button* buttonMarket = new Button(hI, ui["window"]);
	buttonMarket->resize(200, 100);
	buttonMarket->setPosition(Position::hcenter, 240);
	buttonMarket->setText("Market");
	buttonMarket->setFont(fonts::button_text);
	buttonMarket->on(Action::click, market);
	ui["buttonMarket"] = buttonMarket;

    buildComp();
    buildBag();
    buildMarket();
}

void intro()
{
	for (auto it : ui) it.second->hide();
	ui["window"]->setText("Магазин");
	ui["window"]->show();
	ui["buttonComp"]->show();
	ui["buttonBag"]->show();
	ui["buttonMarket"]->show();
}

//////////////////////

void buildComp()
{
	Grid* grid = new Grid(hI, ui["window"]);
    grid->resize(300, 200);
    grid->setPosition(0, 0);
    grid->addColumn("Name", 0, 100);
    grid->addColumn("Section", 1, 100);
    grid->addColumn("Price", 2, 100);
    ui["gridComp1"] = grid;

    Button* button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 10);
	button->setText("Загрузить");
	button->on(Action::click, loadComp1);
	ui["buttonLoadComp1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(200, 20);
	button->setPosition(350, 40);
	button->setText("Сохранить");
	button->on(Action::click, saveComp1);
	ui["buttonSaveComp1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 70);
	button->setText("Сохранить(формат.)");
	button->on(Action::click, saveFormatComp1);
	ui["buttonSaveFormatComp1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 100);
	button->setText("Сортировать");
	button->on(Action::click, sortComp1);
	ui["buttonSortComp1"] = button;

	////////////////////

	grid = new Grid(hI, ui["window"]);
    grid->resize(300, 200);
    grid->setPosition(0, 200);
    grid->addColumn("Name", 0, 100);
    grid->addColumn("Section", 1, 100);
    grid->addColumn("Price", 2, 100);
    ui["gridComp2"] = grid;

    button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 210);
	button->setText("Загрузить");
	button->on(Action::click, loadComp2);
	ui["buttonLoadComp2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(200, 20);
	button->setPosition(350, 240);
	button->setText("Сохранить");
	button->on(Action::click, saveComp2);
	ui["buttonSaveComp2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 270);
	button->setText("Сохранить(формат.)");
	button->on(Action::click, saveFormatComp2);
	ui["buttonSaveFormatComp2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 300);
	button->setText("Сортировать");
	button->on(Action::click, sortComp2);
	ui["buttonSortComp2"] = button;

	//////////////////

	Edit* edit = new Edit(hI, ui["window"]);
	edit->resize(100, 20);
	edit->setPosition(350, 130);
	edit->setText("");
	ui["editSearchComp"] = edit;

	button = new Button(hI, ui["window"]);
	button->resize(50, 20);
	button->setPosition(470, 130);
	button->setText("Поиск");
	button->on(Action::click, searchComp);
	ui["buttonSearchComp"] = button;
}

void comp()
{
	for (auto it : ui) it.second->hide();
	ui["window"]->setText("Comp");
	ui["window"]->show();
	ui["gridComp1"]->show();
	ui["buttonLoadComp1"]->show();
	ui["buttonSaveComp1"]->show();
	ui["buttonSaveFormatComp1"]->show();
	ui["buttonSortComp1"]->show();
	ui["gridComp2"]->show();
	ui["buttonLoadComp2"]->show();
	ui["buttonSaveComp2"]->show();
	ui["buttonSaveFormatComp2"]->show();
	ui["buttonSortComp2"]->show();
	ui["buttonSearchComp"]->show();
	ui["editSearchComp"]->show();
}

void loadComp1()
{
	std::fstream in(Window::openFile(), std::ios::in);
	in >> Comps1;
	Grid* grid = dynamic_cast<Grid*>(ui["gridComp1"]);
	for (int i = 0; i < Comps1.getCount(); ++i) {
		Comp c = Comps1[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Price));
		grid->addRow(row);
	}
	ui["gridComp1"]->draw();
}

void loadComp2()
{
	std::fstream in(Window::openFile(), std::ios::in);
	in >> Comps2;
	Grid* grid = dynamic_cast<Grid*>(ui["gridComp2"]);
	for (int i = 0; i < Comps2.getCount(); ++i) {
		Comp c = Comps2[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Price));
		grid->addRow(row);
	}
	ui["gridComp2"]->draw();
}

void saveComp1()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	out << Comps1;
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveComp2()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	out << Comps2;
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveFormatComp1()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	Comps1.print(out);
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveFormatComp2()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	Comps2.print(out);
	Popup::show(hI, *ui["window"], "Сохранено");
}

void sortComp1()
{
	Grid* grid = dynamic_cast<Grid*>(ui["gridComp1"]);
	grid->clear();
	Comps1.sortByNameAsc();
	for (int i = 0; i < Comps1.getCount(); ++i) {
		Comp c = Comps1[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Price));
		grid->addRow(row);
	}
	ui["gridComp1"]->draw();
}

void sortComp2()
{
	Grid* grid = dynamic_cast<Grid*>(ui["gridComp2"]);
	grid->clear();
	Comps2.sortByNameAsc();
	for (int i = 0; i < Comps2.getCount(); ++i) {
		Comp c = Comps2[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Price));
		grid->addRow(row);
	}
	ui["gridComp2"]->draw();
}

void searchComp()
{
	char* tmp = new char[100];
	std::string s= ui["editSearchComp"]->getText();
	Comps = Comps1 + Comps2;
	strcpy_s(tmp, 100, s.c_str());
	Comp* c = Comps.find(tmp);
	if (!c) Popup::show(hI, *ui["window"], "Нет такого");
	else {
		stringstream ss;
		ss << *c;
		MessageBox(NULL, ss.str().c_str(),"Info", MB_OK);
	}
}

//////////////////////

void buildBag()
{
	Grid* grid = new Grid(hI, ui["window"]);
    grid->resize(300, 200);
    grid->setPosition(0, 0);
    grid->addColumn("Name", 0, 100);
    grid->addColumn("Section", 1, 100);
    grid->addColumn("Num", 2, 100);
    ui["gridBag1"] = grid;

    Button* button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 10);
	button->setText("Загрузить");
	button->on(Action::click, loadBag1);
	ui["buttonLoadBag1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(200, 20);
	button->setPosition(350, 40);
	button->setText("Сохранить");
	button->on(Action::click, saveBag1);
	ui["buttonSaveBag1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 70);
	button->setText("Сохранить(формат.)");
	button->on(Action::click, saveFormatBag1);
	ui["buttonSaveFormatBag1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 100);
	button->setText("Сортировать");
	button->on(Action::click, sortBag1);
	ui["buttonSortBag1"] = button;

	////////////////////

	grid = new Grid(hI, ui["window"]);
    grid->resize(300, 200);
    grid->setPosition(0, 200);
    grid->addColumn("Name", 0, 100);
    grid->addColumn("Section", 1, 100);
    grid->addColumn("Num", 2, 100);
    ui["gridBag2"] = grid;

    button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 210);
	button->setText("Загрузить");
	button->on(Action::click, loadBag2);
	ui["buttonLoadBag2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(200, 20);
	button->setPosition(350, 240);
	button->setText("Сохранить");
	button->on(Action::click, saveBag2);
	ui["buttonSaveBag2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 270);
	button->setText("Сохранить(формат.)");
	button->on(Action::click, saveFormatBag2);
	ui["buttonSaveFormatBag2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 300);
	button->setText("Сортировать");
	button->on(Action::click, sortBag2);
	ui["buttonSortBag2"] = button;

	//////////////////

	Edit* edit = new Edit(hI, ui["window"]);
	edit->resize(100, 20);
	edit->setPosition(350, 130);
	edit->setText("");
	ui["editSearchBag"] = edit;

	button = new Button(hI, ui["window"]);
	button->resize(50, 20);
	button->setPosition(470, 130);
	button->setText("Поиск");
	button->on(Action::click, searchBag);
	ui["buttonSearchBag"] = button;
}

void bag()
{
	for (auto it : ui) it.second->hide();
	ui["window"]->setText("Bag");
	ui["window"]->show();
	ui["gridBag1"]->show();
	ui["buttonLoadBag1"]->show();
	ui["buttonSaveBag1"]->show();
	ui["buttonSaveFormatBag1"]->show();
	ui["buttonSortBag1"]->show();
	ui["gridBag2"]->show();
	ui["buttonLoadBag2"]->show();
	ui["buttonSaveBag2"]->show();
	ui["buttonSaveFormatBag2"]->show();
	ui["buttonSortBag2"]->show();
	ui["buttonSearchBag"]->show();
	ui["editSearchBag"]->show();
}

void loadBag1()
{
	std::fstream in(Window::openFile(), std::ios::in);
	in >> Bags1;
	Grid* grid = dynamic_cast<Grid*>(ui["gridBag1"]);
	for (int i = 0; i < Bags1.getCount(); ++i) {
		Bag c = Bags1[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Num));
		grid->addRow(row);
	}
	ui["gridBag1"]->draw();
}

void loadBag2()
{
	std::fstream in(Window::openFile(), std::ios::in);
	in >> Bags2;
	Grid* grid = dynamic_cast<Grid*>(ui["gridBag2"]);
	for (int i = 0; i < Bags2.getCount(); ++i) {
		Bag c = Bags2[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Num));
		grid->addRow(row);
	}
	ui["gridBag2"]->draw();
}

void saveBag1()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	out << Bags1;
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveBag2()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	out << Bags2;
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveFormatBag1()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	Bags1.print(out);
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveFormatBag2()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	Bags2.print(out);
	Popup::show(hI, *ui["window"], "Сохранено");
}

void sortBag1()
{
	Grid* grid = dynamic_cast<Grid*>(ui["gridBag1"]);
	grid->clear();
	Bags1.sortByNameAsc();
	for (int i = 0; i < Bags1.getCount(); ++i) {
		Bag c = Bags1[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Num));
		grid->addRow(row);
	}
	ui["gridBag1"]->draw();
}

void sortBag2()
{
	Grid* grid = dynamic_cast<Grid*>(ui["gridBag2"]);
	grid->clear();
	Bags2.sortByNameAsc();
	for (int i = 0; i < Bags2.getCount(); ++i) {
		Bag c = Bags2[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Num));
		grid->addRow(row);
	}
	ui["gridBag2"]->draw();
}

void searchBag()
{
	char* tmp = new char[100];
	std::string s= ui["editSearchBag"]->getText();
	Bags = Bags1 + Bags2;
	strcpy_s(tmp, 100, s.c_str());
	Bag* c = Bags.find(tmp);
	if (!c) Popup::show(hI, *ui["window"], "Нет такого");
	else {
		stringstream ss;
		ss << *c;
		MessageBox(NULL, ss.str().c_str(),"Info", MB_OK);
	}
}

/////////////////////

void buildMarket()
{
	Grid* grid = new Grid(hI, ui["window"]);
    grid->resize(300, 200);
    grid->setPosition(0, 0);
    grid->addColumn("Name", 0, 75);
    grid->addColumn("Section", 1, 75);
    grid->addColumn("Num", 2, 75);
    grid->addColumn("Price", 3, 75);
    ui["gridMarket1"] = grid;

    Button* button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 10);
	button->setText("Загрузить");
	button->on(Action::click, loadMarket1);
	ui["buttonLoadMarket1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(200, 20);
	button->setPosition(350, 40);
	button->setText("Сохранить");
	button->on(Action::click, saveMarket1);
	ui["buttonSaveMarket1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 70);
	button->setText("Сохранить(формат.)");
	button->on(Action::click, saveFormatMarket1);
	ui["buttonSaveFormatMarket1"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 100);
	button->setText("Сортировать");
	button->on(Action::click, sortMarket1);
	ui["buttonSortMarket1"] = button;

	////////////////////

	grid = new Grid(hI, ui["window"]);
    grid->resize(300, 200);
    grid->setPosition(0, 200);
    grid->addColumn("Name", 0, 75);
    grid->addColumn("Section", 1, 75);
    grid->addColumn("Num", 2, 75);
    grid->addColumn("Price", 3, 75);
    ui["gridMarket2"] = grid;

    button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 210);
	button->setText("Загрузить");
	button->on(Action::click, loadMarket2);
	ui["buttonLoadMarket2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(200, 20);
	button->setPosition(350, 240);
	button->setText("Сохранить");
	button->on(Action::click, saveMarket2);
	ui["buttonSaveMarket2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 270);
	button->setText("Сохранить(формат.)");
	button->on(Action::click, saveFormatMarket2);
	ui["buttonSaveFormatMarket2"] = button;

	button = new Button(hI, ui["window"]);
	button->resize(100, 20);
	button->setPosition(350, 300);
	button->setText("Сортировать");
	button->on(Action::click, sortMarket2);
	ui["buttonSortMarket2"] = button;

	//////////////////

	Edit* edit = new Edit(hI, ui["window"]);
	edit->resize(100, 20);
	edit->setPosition(350, 130);
	edit->setText("");
	ui["editSearchMarket"] = edit;

	button = new Button(hI, ui["window"]);
	button->resize(50, 20);
	button->setPosition(470, 130);
	button->setText("Поиск");
	button->on(Action::click, searchMarket);
	ui["buttonSearchMarket"] = button;
}

void market()
{
	for (auto it : ui) it.second->hide();
	ui["window"]->setText("Market");
	ui["window"]->show();
	ui["gridMarket1"]->show();
	ui["buttonLoadMarket1"]->show();
	ui["buttonSaveMarket1"]->show();
	ui["buttonSaveFormatMarket1"]->show();
	ui["buttonSortMarket1"]->show();
	ui["gridMarket2"]->show();
	ui["buttonLoadMarket2"]->show();
	ui["buttonSaveMarket2"]->show();
	ui["buttonSaveFormatMarket2"]->show();
	ui["buttonSortMarket2"]->show();
	ui["buttonSearchMarket"]->show();
	ui["editSearchMarket"]->show();
}

void loadMarket1()
{
	std::fstream in(Window::openFile(), std::ios::in);
	in >> Markets1;
	Grid* grid = dynamic_cast<Grid*>(ui["gridMarket1"]);
	for (int i = 0; i < Markets1.getCount(); ++i) {
		Market c = Markets1[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Num));
		row.push_back(std::to_string(c.Price));
		grid->addRow(row);
	}
	ui["gridMarket1"]->draw();
}

void loadMarket2()
{
	std::fstream in(Window::openFile(), std::ios::in);
	in >> Markets2;
	Grid* grid = dynamic_cast<Grid*>(ui["gridMarket2"]);
	for (int i = 0; i < Markets2.getCount(); ++i) {
		Market c = Markets2[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Num));
		row.push_back(std::to_string(c.Price));
		grid->addRow(row);
	}
	ui["gridMarket2"]->draw();
}

void saveMarket1()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	out << Markets1;
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveMarket2()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	out << Markets2;
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveFormatMarket1()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	Markets1.print(out);
	Popup::show(hI, *ui["window"], "Сохранено");
}

void saveFormatMarket2()
{
	std::fstream out(Window::saveFile(), std::ios::out);
	Markets2.print(out);
	Popup::show(hI, *ui["window"], "Сохранено");
}

void sortMarket1()
{
	Grid* grid = dynamic_cast<Grid*>(ui["gridMarket1"]);
	grid->clear();
	Markets1.sortByNameAsc();
	for (int i = 0; i < Markets1.getCount(); ++i) {
		Market c = Markets1[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Num));
		row.push_back(std::to_string(c.Price));
		grid->addRow(row);
	}
	ui["gridMarket1"]->draw();
}

void sortMarket2()
{
	Grid* grid = dynamic_cast<Grid*>(ui["gridMarket2"]);
	grid->clear();
	Markets2.sortByNameAsc();
	for (int i = 0; i < Markets2.getCount(); ++i) {
		Market c = Markets2[i];
		std::vector<std::string> row;
		row.push_back(c.Name);
		row.push_back(c.Section);
		row.push_back(std::to_string(c.Num));
		row.push_back(std::to_string(c.Price));
		grid->addRow(row);
	}
	ui["gridMarket2"]->draw();
}

void searchMarket()
{
	char* tmp = new char[100];
	std::string s= ui["editSearchMarket"]->getText();
	Markets = Markets1 + Markets2;
	strcpy_s(tmp, 100, s.c_str());
	Market* c = Markets.find(tmp);
	if (!c) Popup::show(hI, *ui["window"], "Нет такого");
	else {
		stringstream ss;
		ss << *c;
		MessageBox(NULL, ss.str().c_str(),"Info", MB_OK);
	}
}

///////////////////