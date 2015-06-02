#ifndef __RECORDS_H_INCLUDED__
#define __RECORDS_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <algorithm>
#include "stack.h"
#include <cstring>

struct Record
{
	Record() : next(0) 
	{
		name = new char[100];
	};
	Record(char* _name, int _score, Record* _next = 0) : score(_score), next(_next) 
	{
		name = new char[strlen(_name)];
		strcpy(name, _name);
	};
	int score;
	char* name;
	Record* next;
};

class Records
{
private:
	Record* head;
	Record* merge(Record*, Record*);
public:
	Records();
	Records(Record&);
	Records(const Records&);
	void sort();
	Records& operator += (const Record);
	Record* operator [] (int);
	friend Records operator + (Records&, Records&);
	friend std::istream& operator >> (std::istream&, Records&);
	friend std::ifstream& operator >> (std::ifstream&, Records&);
	friend std::ostream& operator << (std::ostream&, Records&);
	friend std::ofstream& operator << (std::ofstream&, Records&);
};

#endif