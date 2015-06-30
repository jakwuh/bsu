#ifndef __CONTAINER_H_INCLUDED__
#define __CONTAINER_H_INCLUDED__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <map>

struct Student
{
	Student(char* _name = 0, int _group = 0, double _gpa = 0) : name(_name), group(_group), gpa(_gpa){};
	char* name;			// surname
	int group;			// number of group
	double gpa;			// grade point average
};

class Container
{
private:
	int size, count;
	Student* p;
public:
	Container(const int& = 100);
	Container(const Container&);
	~Container();
	bool push(const Student&);
	bool remove(char*);
	void sortByName();
	void sortByGroupAndName();
	Student* findByName(char*);
	void report(std::ostream&);
	void print(std::ostream&);
	int getSize();
	int getCount();
};

#endif