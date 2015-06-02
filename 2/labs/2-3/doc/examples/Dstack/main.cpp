#include <iostream>
using namespace std;

#include "Stack.h"

void main()
{
	Stack stack1,stack2;
	cout<<"Input size of string:"<<endl;
	int n,x;
	cin>>n;
		
	for(int i=0;i<n;i++)
	{
		stack1.push(2*i);
		
	}
		for(int i=0;i<n;i++)
	{
		stack2.push(3*i);
	}
	while (	!stack1.empty())
	{
		x=stack1.pop();
   cout<<x<<endl;
	}
	while (	!stack2.empty())
	{
		x=stack2.pop();
   cout<<x<<endl;
	}
}