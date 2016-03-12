#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;


int *d=new int[12];int num=0;int maxdeep=0;int T=12;

struct BoolInt{
	int key;
	bool result;
}tmp;

int LoadDominoes(void)
{
	int S=0;
	for(int i=0;i<12;i++) d[i]=0;
	int n;int a,b;
	ifstream p("input.txt");
	p>>n;
	for(int i=1;i<=n;i++){
		p>>a;p>>b;
		if(a!=b){switch (a-b) {
			case -6 : d[0]++;break;
			case -5 : d[1]++;break;
			case -4 : d[2]++;break;
			case -3 : d[3]++;break;
			case -2 : d[4]++;break;
			case -1 : d[5]++;break;
			case 1 : d[6]++;break;
			case 2 : d[7]++;break;
			case 3 : d[8]++;break;
			case 4 : d[9]++;break;
			case 5 : d[10]++;break;
			case 6 : d[11]++;break;}
		S+=(a-b);
		num++;}
	}
	return S;
}

BoolInt deeper1(int sum,int *d,int deep)
{
	if(((deep==maxdeep-1)&&(abs(sum)>12))||(sum<-12)||(deep>maxdeep)){BoolInt a;a.key=maxdeep+1;a.result=false;return a;}
	if(abs(sum)<T){BoolInt a;a.key=0;a.result=true;return a;}	
	BoolInt min;min.key=maxdeep;min.result=false;
	for(int j=11;j>=0;j--)
	{
		if(d[j])
		{
			d[j]--;
			tmp=deeper1((j>5)?(sum-2*(j-5)):(sum+2*(6-j)),d,deep+1);
			if(tmp.result){tmp.key++;return tmp;}
			if(min.key>tmp.key) {min=tmp;if (maxdeep==min.key+deep){min.result=true;min.key++;return min;}}
			d[j]++;
		}
	}
	min.key++;
	return min;
}

BoolInt deeper2(int sum,int *d,int deep)
{
	if(((deep==maxdeep-1)&&(abs(sum)>12))||(sum>12)||(deep>maxdeep)){BoolInt a;a.key=maxdeep+1;a.result=false;return a;}
	if(abs(sum)<T){BoolInt a;a.key=0;a.result=true;return a;}	
	BoolInt min;min.key=maxdeep;min.result=false;
	for(int j=0;j<12;j++)
	{
		if(d[j])
		{
			d[j]--;
			tmp=deeper2((j>5)?(sum-2*(j-5)):(sum+2*(6-j)),d,deep+1);
			if(tmp.result){tmp.key++;return tmp;}
			if(min.key>tmp.key) {min=tmp;if (maxdeep==min.key+deep){min.result=true;min.key++;return min;}}
			d[j]++;
		}
	}
	min.key++;
	return min;
}

int checkdeep(int sum,int *d2)
{
	int k=0;
	if (sum<0)
		for(int j=0;j<6;j++)
		{
			while(d2[j])
			{
				d2[j]--;k++;
				sum+=2*(6-j);
				maxdeep++;
				if(sum>0){d2[j]+=k; return maxdeep;}
			}
			d2[j]+=k;
			k=0;
		}
	else
		for(int j=11;j>5;j--)
		{
			while(d2[j])
			{
				d2[j]--;k++;
				sum-=2*(j-5);
				maxdeep++;
				if(sum<0){d2[j]+=k; return maxdeep;}
			}
			d2[j]+=k;
			k=0;
		}
}

void checkT(int k)
{
	if(k!=1)
	{
	for(int i=0;i<6;i++)
		for(int j=i+1;j<6;j++)
			if(d[i]&&d[j]&&(T>(j-i)*2)) T=2*(j-i);
	for(int i=11;i>5;i--)
		for(int j=i-1;j>5;j--)
			if(d[i]&&d[j]&&(T>(i-j)*2)) T=2*(i-j);
	if(T!=2)
		for(int i=0;i<6;i++)
			for(int j=11;j>5;j--)
				if(d[i]&&d[j]&&(T>2*abs(j+i-11))) T=2*abs(j+i-11);
	}
	else 
	{
		int i=0;
		while(!d[i]) i++;
		(i>5)?T=2*(i-5):T=2*(6-i);
	}
}

int f1(int sum)
{
	//if(abs(sum)<T) return 0;
	if(!sum) return 0;
	int m=num;
	if(sum<0)
	{
		for(int i=0;i<6;i++)
		if(d[i])	
		{
			int tmp=f1(sum+2*(6-i));
			if (m>tmp) m=tmp;
		}
	}
	else
	{
		for(int i=11;i>5;i--)
		if(d[i])
		{
			int tmp=f1(sum-2*(i-5));
			if (m>tmp) m=tmp;
		}
	}
	return m+1;
}

int Result(int sum)
{	
	int s=0;int k=0;
//	checkT();
	for(int i=0;i<12;i++)
		if(d[i]) {s+=d[i];k++;}
		if ((abs(sum)<=s)&&(k<=3)) return f1(sum);
	int min=0;
	int j=11;
	while (sum>182)
		{
		if(d[j]) {sum-=2*(j-5);d[j]--;num--;min++;}
		else j--;
		}
	j=0;
	while (sum<-182)
		{
		if(d[j]) {sum+=2*(6-j);d[j]--;num--;min++;}
		else j++;
		}
	checkT(k);
	maxdeep=checkdeep(sum,d);
	return (sum>0)? (min+deeper1(sum,d,0).key):(min+deeper2(sum,d,0).key);
}

int main(void)
{
	ofstream p("output.txt");
	p<<Result(LoadDominoes());
	return 0;
}