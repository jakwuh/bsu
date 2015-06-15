#ifndef __COMP_H_INCLUDED__
#define __COMP_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <iomanip>
#include "market.h"

using namespace std;

struct Comp
{
	char Name[30];
	char Section[20];
	int Price;

	void print(std::ostream&);
	void printHeader(std::ostream&);
	operator Market ();
};

std::ostream& operator << (std::ostream& out, Comp const& comp)
{
	out << comp.Name << endl << comp.Section << endl << comp.Price << endl;
	return out;
};

std::istream& operator >> (std::istream& in, Comp& comp)
{
	in.getline(comp.Name, 30);
	in.getline(comp.Section, 20);
	in >> comp.Price;
	in.ignore(10, '\n');
	return in;
}

void Comp::print(std::ostream& out)
{
	out << setfill(' ') << setw(30) << Name << setw(20) << Section << setw(10) << Price << endl;
}

void Comp::printHeader(std::ostream& out)
{
	out << setw(30) << setfill('=') << "Name" << setw(20) << "Section" << setw(10) << "Price" << endl;
}

bool operator == (Comp const& comp1, Comp const& comp2)
{
	return (strcmp(comp1.Name, comp2.Name) == 0);
}

bool operator != (Comp const& comp1, Comp const& comp2)
{
	return !(comp1 == comp2);
}

bool operator > (Comp const& comp1, Comp const& comp2)
{
	return (strcmp(comp1.Name, comp2.Name) == 1);
}

bool operator < (Comp const& comp1, Comp const& comp2)
{
	return (strcmp(comp1.Name, comp2.Name) == -1);
}

Comp::operator Market ()
{
	Market m; 
	strcpy_s(m.Name, 30, Name);
	strcpy_s(m.Section, 30, Section);
	m.Price = Price;
	m.Num = 1;
	return m;
}

#endif