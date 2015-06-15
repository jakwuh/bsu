#ifndef __MARKET_H_INCLUDED__
#define __MARKET_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Market
{
	char Name[30];
	char Section[20];
	int Price;
	int Num;

	void print(std::ostream&);
	void printHeader(std::ostream&);
};

std::ostream& operator << (std::ostream& out, Market const& market)
{
	out << market.Name << endl << market.Section << endl << market.Price << endl << market.Num << endl;
	return out;
};

std::istream& operator >> (std::istream& in, Market& market)
{
	in.getline(market.Name, 30);
	in.getline(market.Section, 20);
	in >> market.Price;
	in.ignore(10, '\n');
	in >> market.Num;
	in.ignore(10, '\n');
	return in;
}

void Market::print(std::ostream& out)
{
	out << setfill(' ') << setw(30) << Name << setw(20) << Section << setw(10) << Price << setw(10) << Num << endl;
}

void Market::printHeader(std::ostream& out)
{
	out << setw(30) << setfill('=') << "Name" << setw(20) << "Section" << setw(10) << "Price" << setw(10) << "Num" << endl;
}

bool operator == (Market const& market1, Market const& market2)
{
	return (strcmp(market1.Name, market2.Name) == 0);
}

bool operator != (Market const& market1, Market const& market2)
{
	return !(market1 == market2);
}

bool operator > (Market const& market1, Market const& market2)
{
	return (strcmp(market1.Name, market2.Name) == 1);
}

bool operator < (Market const& market1, Market const& market2)
{
	return (strcmp(market1.Name, market2.Name) == -1);
}


#endif