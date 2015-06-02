//Обрабаботка двунаправленного  динамического списка
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;
struct node						/* элемент списка */
	{
		int  item;					/* данные */
		node*  next;				/* указатель на следующий элемент */
		node*  prev;				/* указатель на предыдущий элемент */
	};
	
void InitList(node **head,node **tail )							/* конструктор */
{
	*head = 0;
	*tail = 0;
}

void RemoveList(node **head, node **tail )							/* деструктор */
{node *tmp = *head;
	while(tmp != 0)
	{   node *tmp1 = tmp;
		tmp = tmp->next;
		delete tmp1;
	}
	*head = 0;
	*tail = 0;
}

void push_front(node **head,node **tail,int n)			/* включить элемент в начало списка */
{
	node* tmp = new node;
	tmp->item = n;
	tmp->prev = 0;
	tmp->next = *head;
	if(*head)
	{ node* tmp1=*head;
		tmp1->prev = tmp;
	}
	else
	*tail = tmp;
	*head = tmp;
}
/*
void push_back(int n)		
// включить элемент в конец списка 
{
	node* tmp = new node;
	tmp->item = n;
	tmp->next = 0;
	tmp->prev = tail;
	if(tail)
		tail->next = tmp;
	else
		head = tmp;
	tail = tmp;
}

int pop_front()		
// исключить элемент из начала списка 
{
	if(head)
	{
		int res = head->item;
		node *tmp = head;
		if(head->next)
			head->next->prev = 0;
		else
			tail = 0;
		head = head->next;
		delete tmp;
		return res;
	}
	return 0;
}

int pop_back()	
// исключить элемент из конца списка 
{
	if(tail)
	{
		int res = tail->item;
		node *tmp = tail;
		if(tail->prev)
			tail->prev->next = 0;
		else
			head = 0;
		tail = tail->prev;
		delete tmp;
		return res;
	}
	return 0;
}

void insert(int data, int pos)
// вставить в позицию pos+1 
{
	node* tmp = new node;
	tmp->item = data;
	node* ptmp = head;
	if(ptmp == 0)
	{
		tmp->next = 0;
		tmp->prev = 0;
		head = tmp;
		tail = tmp;
		return;
	}
    int i = 0;
	while ((i<pos)&&(ptmp->next))
	{
		ptmp = ptmp->next;
		i++;
	}
    if  (ptmp->next == 0)
		{
			ptmp->next = tmp;
			tmp->prev = ptmp;
			tmp->next = 0;
			tail = tmp;
			return;
		}
	
	ptmp->next->prev = tmp;
	tmp->next = ptmp->next;
	ptmp->next = tmp;
	tmp->prev = ptmp;
}

int remove(int pos)	
// удалить элемент c позиции pos
{
	node* ptmp = head;
	for(int i = 0; i<pos; i++)
	{
		if(ptmp == 0)
		{
			return 0;
		}
		ptmp = ptmp->next;
	}
	ptmp->next->prev = ptmp->prev;
	if(ptmp->prev != 0)
		ptmp->prev->next = ptmp->next;
	int res = ptmp->item;
	delete ptmp;
	return res;
}

bool isEmpty()	
// пустой список? 
{
	return head == 0;
}

*/
void print ( node **head)			//Печать содержимого стека
{
	node* temp = *head;
	
	while (temp)
	{
		cout<<temp->item<<endl;
		temp = temp->next;
	}
}

void main()
{/* указатели на первый и последний элементы в списке */
	node *head, *tail;
	InitList(&head, &tail);
	push_front(&head,&tail,1);
 	push_front(&head,&tail,2);
	push_front(&head,&tail,3);
	print (&head);	
/* 	push_back(33);
 	push_back(44);
 	push_back(55);
	
//	insert(300,6);
//		insert(500,2);
print ();	
cout<<" **"<<endl;
//	remove(3);
   pop_back();
   pop_front();	
	//print ();	
	insert(100, 3);
	print ();	
	//cout<<pop_front()<<endl;
 
//	cout<<pop_back()<<endl;
	
*/
	
}