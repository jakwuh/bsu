#ifndef __COMP_TEMPLATE_H_INCLUDED__
#define __COMP_TEMPLATE_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <iomanip>
#include "sort.h"

using namespace std;

template <typename T>
class COMP
{
private:
	int count;
	T* M;
public:

	COMP(int count_ = 0, T* M_ = 0) : count(count_), M(M_) {};
	~COMP() { delete M; }

	COMP(COMP const& comp)
	{
		(*this) = comp;
	};

	friend std::ostream& operator << (std::ostream& out, COMP const& comp)
	{
		out << comp.count << endl;
		for (int i = 0; i < comp.count; ++i) {
			out << comp.M[i];
		};
		return out;
	};

	friend std::istream& operator >> (std::istream& in, COMP& comp)
	{
		in >> comp.count;
		in.ignore(10, '\n');
		comp.M = new T[comp.count];
		for (int i = 0; i < comp.count; ++i) {
			in >> comp.M[i];
		}
		return in;
	}

	void print(std::ostream& out)
	{
		out << "Total count:" << "\t\t" << count << endl;
		if (count > 0) M[0].printHeader(out);
		out << setfill(' ');
		for (int i = 0; i < count; ++i) M[i].print(out);
	}

	COMP& operator = (COMP const& comp)
	{
		count = comp.count;
		M = new T[count];
		memcpy(M, comp.M, sizeof(T) * count);
		return *this;
	}

	friend COMP operator + (COMP const& comp1, COMP const& comp2)
	{
		int count = comp1.count + comp2.count;
		T* M = new T[count];
		std::memcpy(M, comp1.M, sizeof(T) * comp1.count);
		std::memcpy(M + comp1.count, comp2.M, sizeof(T) * comp2.count);
		shell_sort<T>(M, count);
		int real_count = 0;
		for (int i = 0; i < count; ++i) {
			if (i == count - 1) real_count++;
			else if (M[i] != M[i + 1]) real_count++;
		}
		COMP comp;
		comp.count = real_count;
		comp.M = new T[comp.count];
		int j = 0;
		for (int i = 0; i < count; ++i) {
			if (i == count - 1) comp.M[j++] = M[i];
			else if (M[i] != M[i + 1]) comp.M[j++] = M[i];
		}
		delete M;
		return comp;
	}

	int getCount() { return count; };

	T* find(char* name)
	{
		T* ptr = 0;
		for (int i = 0; i < count; ++i) {
			if (strcmp(M[i].Name, name) == 0) ptr = &M[i];
		}
		return ptr;
	}

	T& operator [] (int i)
	{
		return M[i];
	}

	void sortByNameAsc()
	{
		shell_sort<T>(M, count);
	}

	void sortByNameDesc()
	{
		sortByNameAsc();
		for (int i = 0; i < count / 2; ++i) 
			std::swap(M[i], M[count - i - 1]);
	}

	void sortBySectionAscNameDesc();
	
};


#endif