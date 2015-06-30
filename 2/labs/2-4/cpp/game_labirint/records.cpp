#include "records.h"

std::istream &operator >> (std::istream &in, Record &r)
{
	in >> r.name >> r.score;
	return in;
}

std::ifstream &operator >> (std::ifstream &in, Record &r)
{
	in >> r.name >> r.score;
	return in;
}

std::ostream &operator << (std::ostream &out, const Record &r)
{
	out << r.name << ' ' << r.score;
	return out;
}

std::ofstream &operator << (std::ofstream &out, const Record &r)
{
	out << r.name << ' ' << r.score;
	return out;
}

Records::Records() : head(0) {};

Records::Records(Record& r) : head(&r){};

Records::Records(const Records& r)
{
	head = 0;
	Record* tmp = r.head;
	while (tmp)
	{
		*this += *tmp;
		tmp= tmp->next;
	}
}

Records& Records::operator += (const Record r)
{
	Record* tmp = head;
	while(tmp && tmp->next) tmp = tmp->next;
	if (tmp) tmp->next = new Record(r.name, r.score);
	else head = new Record(r.name, r.score);
	return *this;
}

Record* Records::operator [] (int i)
{
	Record* tmp = head;
	while (i-- && tmp)
		tmp = tmp->next;
	return tmp;
}

Records operator + (Records& r1, Records& r2)
{
	Records r;
	int i = 0;
	while (r1[i])
		r += *r1[i++];
	i = 0;
	while (r2[i])
		r += *r2[i++];
	r.sort();
	return r;
}

std::istream& operator >> (std::istream& in, Records& r)
{
	Record tmp;
	in >> tmp;
	while (!in.eof())
	{
		r += tmp;
		in >> tmp;
	}
	r.sort();
	return in;
}

std::ifstream& operator >> (std::ifstream& in, Records& r)
{	
	Record tmp;
	in >> tmp;
	while (!in.eof())
	{
		r += tmp;
		in >> tmp;
	}
	r.sort();
	return in;
}

std::ostream& operator << (std::ostream& out, Records& r)
{
	int i = 0;
	while (r[i]) out << *r[i++] << "\n";
	r.sort();
	return out;
}

std::ofstream& operator << (std::ofstream& out, Records& r)
{
	int i = 0;
	while (r[i]) out << *r[i++] << "\n";
	r.sort();
	return out;
}

Record* Records::merge(Record* r1, Record* r2)
{
	Record* out, *ptr;
	if (r1->score < r2->score) {
		out = r1;
		r1 = r1->next;
	} else {
		out = r2;
		r2 = r2->next;
	}
	ptr = out;
	while (r2 && r1) {
		if (r1->score < r2->score) {
			out->next = r1;
			r1 = r1->next;
		} else {
			out->next = r2;
			r2 = r2->next;
		}
		out = out->next;
	}
	if (r2) out->next = r2;
	else if (r1) out->next = r1;
	return ptr;
}

void Records::sort()
{
	if (!head) return;
	ArrayStack<int> ns(32);
	ArrayStack<Record*> rs(32);
	Record* tmp = head, *el;
	int i;
	while(tmp){
		i = 1;
		el = tmp->next;
		tmp->next = 0;	
		while(!ns.isEmpty() && ns.peek() == i) {
			tmp = merge(tmp, rs.peek());
			rs.pop();
			ns.pop();
			i *= 2;
		}
		ns.push(i);
		rs.push(tmp);
		tmp = el;
	}
	tmp = rs.peek();
	rs.pop();
	while (!rs.isEmpty()) {
		tmp = merge(tmp, rs.peek());
		rs.pop();
	};
	head = tmp;
}