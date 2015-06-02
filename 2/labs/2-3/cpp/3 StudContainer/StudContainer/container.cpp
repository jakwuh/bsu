#include "container.h"

Container::Container(const int& _size) : size(_size), count(0) {
	 p = new Student[size];
}

Container::Container(const Container& c) {
	Container(c.size);
	for (int i = 0; i < c.count; i++)
		push(c.p[i]);
}

Container::~Container() {
	delete[] p;
}

bool Container::push(const Student& s) {
	if (count >= size) return false;
	p[count++] = s;
	return true;
}

bool Container::remove(char* name) {
	int i = 0;
	while (i < count) {
		if (strcmp(p[i].name, name) == 0) {
			while (i < count - 1) {
				p[i] = p[i + 1];
				i++;
			}
			count--;
			return true;
		}
		i++;
	}
	return false;
}

int nameComparator(const void *a, const void *b){
	return strcmp((*(Student*)a).name,(*(Student*)b).name);
}

int nameAndGroupComparator(const void *a, const void *b){
	if ((*(Student*)a).group == (*(Student*)b).group)
		return strcmp((*(Student*)a).name,(*(Student*)b).name);
	else return ((*(Student*)a).group - (*(Student*)b).group);
}

void Container::sortByName() {
	qsort(p, count, sizeof(Student), nameComparator);
}

void Container::sortByGroupAndName() {
	qsort(p, count, sizeof(Student), nameAndGroupComparator);
}

Student* Container::findByName(char* name) {
	Student* tmp = 0;
	for (int i = 0; i < count; i++)
		if (strcmp(p[i].name, name) == 0)
			tmp = &p[i];
	return tmp;
}

int Container::getSize() {
	return size;
}

int Container::getCount() {
	return count;
}

void Container::report(std::ostream& out) {
	std::map<int, double> gpad;
	std::map<int, int> gpan;
	for (int i = 0; i < count; i++) {
		gpan[p[i].group] = 0;
		gpad[p[i].group] = 0;
	}
		
	for (int i = 0; i < count; i++)
	{
		gpan[p[i].group] = gpan[p[i].group] + 1;
		gpad[p[i].group] = gpad[p[i].group] + (p[i].gpa - gpad[p[i].group]) / gpan[p[i].group];
	}
	out.flags(std::ios::left);
	out << std::setw(10) << "Группа" << std::setw(20) << "Средний балл" << "\n\n";
	for (std::map<int, double>::iterator it = gpad.begin(); it != gpad.end(); ++it)
		out << std::setw(10) << it->first << std::setw(20) << it->second << '\n';
}

void Container::print(std::ostream& out) {\
	out.flags(std::ios::left);
	out << std::setw(3) << '#' << std::setw(20) << "Фамилия" << std::setw(10) << "Группа" << std::setw(20) << "Средний балл" << "\n\n";
	for (int i = 0; i < count; i++)
		out << std::setw(3) << (i + 1) << std::setw(20) << p[i].name << std::setw(10) << p[i].group << std::setw(20) << p[i].gpa << std::endl;
}