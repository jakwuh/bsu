#include <iostream>
#include <math.h>
using namespace std;
//Нахождение действительных корней квадратного уравнения 
void main()
{
  setlocale (LC_ALL,".1251");  //Для вывода русского текста
//  setlocale (LC_ALL,"rus");  //Для вывода русского текста
  double a,b,c,x1,x2,d;
 
   cout<<"введи коэффициенты \n";
   cin>>a>>b>>c;
   cout<<"резултьтат"<<endl;
 

   d= b*b-4*a*c;
   if (a==0)
   {     if (b==0)
		   cout<<"не корректный ввод  ";
	   else
	   {
		   x1=(-c)/b;
		   cout<<"x="<<x1;
	   }      }
   else
	   if (d<0)
		   cout<<"нет действительных корней\n";
	   else
	   {
		   x1=(-b+sqrt(d))/(2*a);
		   x2=(-b-sqrt(d))/(2*a);
		   cout<<"x1="<<x1; 
		   cout<<"x2="<<x2; 
	   }
}
