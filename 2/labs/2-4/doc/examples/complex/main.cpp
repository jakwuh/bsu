#include "complex.h"
#include <iostream>
using namespace std;

int main()
{
	try
	{
		Complex z1;
		cout<<z1<<endl;
		
		double a,b;
		cout<<"Enter re and im:"<<endl;
		cin>>a>>b;
		Complex z2(a,b);
		cout<<z2<<endl;

		Complex z3=z2+z1;
		cout<<z3<<endl;

		z3+=z2;
		cout<<z3<<endl;

		Complex z4=z2/z3;
		cout<<z4<<endl;

		z4+=z3;

		if(z1>z2)
			cout<<z1<<">"<<z2<<endl;
		else
			cout<<z1<<"<"<<z2<<endl;
		z2=z3/z4;
		cout<<z2<<endl;

		cout<<z3[1]<<endl;
		
		cout<<"*********"<<endl<<z3<<endl;
		z3++;
		cout<<z3<<endl;
		cout<<++z3<<endl;

	}
	catch(zero_divide)
	{
		cout<<"Error!"<<endl;
	}
	catch(bad_index)
	{
		cout<<"Wrong index!"<<endl;
	}
	return 1;
}