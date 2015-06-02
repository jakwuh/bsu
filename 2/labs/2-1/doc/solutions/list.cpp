
//Из листа клетчатой бумаги размером N x M удалили некоторые клетки.
//Определить, на сколько связных кусков распадается оставшаяся часть листа. 
//	К - количество удалённых клеток.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;
struct queue  //динамическая очередь
	{
		int x;       //номер строки матрицы
		int y;	     //номер столбца матрицы
		queue* next; //нссылка на след элемент
  };
	queue  *head,*tail;

void InitQueue() //инициализация  очереди
{
	head = 0;
	tail = 0;
}
bool isEmpty()  //проверка на пустоту
{
	return head == 0 ? true : false;
}
void peek( int *a,int *b) //взятие из   очереди первого элемента без удаления
{
  if (!isEmpty())
  {
	*a = head->x;
	*b = head->y;
  }
}

void pop()    // удаление из   очереди первого элемента
{
  if (!isEmpty())
  {
	queue* tmp = head;
	head = head->next;
	delete tmp;
  }
}

void push(int a,int b)  // добавление в   очередь  элемента
{
	queue* tmp = new queue;
	tmp->x=a;
	tmp->y=b;
	tmp->next = 0;
	if(head == 0)
	{
		head = tmp;
		tail = head;
		return;
	}
	tail->next = tmp;
	tail = tmp;
	tail->next=0;
}

void main()
{   setlocale(LC_ALL,"rus");
	ifstream f1;
	f1.open("input1.txt");
	if(!f1.is_open())
	{
		cerr<<"Open file failed."<<endl;
		return;
	}
	int i,j,n,m,k,x,y,x1,y1;
	int **Lst;  //матрица для хранения листа бумаги
	f1>>n>>m;
	
	Lst=new int *[n];
	for(i=0;i<n;i++)
	   Lst[i]=new int[m];
	cout<<"Лист бумаги дырки -1 "<<endl;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			f1>>Lst[i][j];
			cout<<setw(3)<<Lst[i][j]<<" ";
		}
		cout<<endl<<endl;
	}

InitQueue();	
	k=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{ 
	 	if (Lst[i][j]==0)
		  {
		   k++;
		   push(i,j);
		   Lst[i][j]=k;
   
		   while (!isEmpty()) 
		    {  
			while (!isEmpty()) 
			 {
				peek(&x,&y);
                if (  x>0 && Lst[x-1][y]==0 ) 
					{ x1=x-1; 
				      push(x1,y);
					  Lst[x1][y]=k;
				    }

				 if (  x<n-1 && Lst[x+1][y]==0 ) 
					{ x1=x+1; 
				      push(x1,y);
					  Lst[x1][y]=k;
				    }
				 if (  y>0 && Lst[x][y-1]==0 ) 
					{ y1=y-1; 
				      push(x,y1);
					  Lst[x][y1]=k;
				    }
				  if (  y<m-1 && Lst[x][y+1]==0 ) 
					{ y1=y+1; 
				      push(x,y1);
					  Lst[x][y1]=k;
				    }
				  pop();
			 }// for 
		   }//while is_empty
		  }//if
		  }   //for j
		}   //for i

		cout<<"Количество кусков k="<<k<<endl;
} 
