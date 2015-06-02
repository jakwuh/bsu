#include <queue>
#include <iostream>
#include <conio.h>
#include <time.h>
 
using namespace std;
 
 
void main()
{setlocale (LC_ALL, "Russian");
srand((unsigned) time(NULL));
int b,action,n;
queue <int> Q;
cout << "Введите количество элементов очереди: ";
cin >> n;
for (int i=0; i<n; i++)
Q.push (b=rand() % 50);
queue <int> newQ = Q;
 
while (!newQ.empty()){
cout << newQ.front() << " ";
newQ.pop();}
cout << "\nПервый элемент очереди: " << Q.front()<<endl;
cout << "Последний элемент очереди: " << Q.back()<<endl;
newQ = Q;
newQ.pop();
cout << "Удаляем первый элемент очереди: \n";
Q = newQ;
cout << "Оставшиеся элементы \n";
while (!newQ.empty()){
    cout << newQ.front() << " ";
    newQ.pop();}
cout << "\nКоличество элементов очереди: " << Q.size(); 
_getch();
}

