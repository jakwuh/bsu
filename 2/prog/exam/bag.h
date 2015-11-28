#ifndef __BAG_H_INCLUDED__
#define __BAG_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <iomanip>
#include "market.h"

using namespace std;

struct Bag
{
	char Name[30];
	char Section[20];
	int Num;

	void print(std::ostream&);
	void printHeader(std::ostream&);
	operator Market();
};

std::ostream& operator << (std::ostream& out, Bag const& bag)
{
	out << bag.Name << endl << bag.Section << endl << bag.Num << endl;
	return out;
};

std::istream& operator >> (std::istream& in, Bag& bag)
{
	in.getline(bag.Name, 30);
	in.getline(bag.Section, 20);
	in >> bag.Num;
	in.ignore(10, '\n');
	return in;
}

void Bag::print(std::ostream& out)
{
	out << setfill(' ') << setw(30) << Name << setw(20) << Section << setw(10) << Num << endl;
}

void Bag::printHeader(std::ostream& out)
{
	out << setw(30) << setfill('=') << "Name" << setw(20) << "Section" << setw(10) << "Count" << endl;
}

bool operator == (Bag const& bag1, Bag const& bag2)
{
	return (strcmp(bag1.Name, bag2.Name) == 0);
}

bool operator != (Bag const& bag1, Bag const& bag2)
{
	return !(bag1 == bag2);
}

bool operator > (Bag const& bag1, Bag const& bag2)
{
	return (strcmp(bag1.Name, bag2.Name) == 1);
}

bool operator < (Bag const& bag1, Bag const& bag2)
{
	return (strcmp(bag1.Name, bag2.Name) == -1);
}

Bag::operator Market ()
{
	Market m;
	strcpy_s(m.Name, 30, Name);
	strcpy_s(m.Section, 30, Section);
	m.Price = 1000;
	m.Num = Num;
	return m;
}


#endif