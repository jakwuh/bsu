/*
1.2	Описать процедуру, которая подсчитывает количество элементов стека, 
//у которых равные "соседи".
*/
//tomkevich Alina 8 gruppa

#include <iostream>
#include "Stack.h"
#include<string.h>
using namespace std;
//#include "vichislenia.h"
using namespace std;
int main()
{
	setlocale(LC_ALL,".1251");
    Stack a;
	int l,g,x1,x2,x3,n;
	
	FILE *IN,*OUT;

	if((IN=fopen("input.txt","rt"))==NULL)
	{
		printf("Проверьте наличие файла \"input.txt\"\n");
		return 0;
	}
	char tmp[100];
	char* c=(char*)malloc(100);
	n=0;
    while(!feof(IN))
	{
		fgets(tmp,100,IN);
		c=strtok(tmp," ");

		while (c)
		{
			n++;
			g=atoi(c);
		    a.Push(g);
			c=strtok(NULL," ");
			
		}
		
	}
	l=0;
	OUT=fopen("output.txt","w");
	if (n<=2) 
	{
		fprintf(OUT,"%d",0);
		return 0;
	}
	x1=a.Pop();
	x2=a.Pop();
	while (!(a.isEmpty()))
	{
		x3=a.Pop();
		if (x1==x3) l++;
		x1=x2;
		x2=x3;
	}
	fclose(IN);
	
	fprintf(OUT,"%d",l);
	fclose(OUT);
	return 0;
}