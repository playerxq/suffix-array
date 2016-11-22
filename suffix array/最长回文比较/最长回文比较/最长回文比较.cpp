// 最长回文比较.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int ss[10]={1,2,2,0,1,2,3,2,1,0};
int sss[22];
int p[21];
void init()
{
	sss[0]=-10001;
	int j = 1;
	for(int i = 0;i<10;i++)
	{
		sss[j++]=-10000;
		sss[j++]=ss[i];
	}
	sss[j]=-10000;
}
//p[id]为包括id的最长半径
//mx为id+p[id] 为回文上届id+p[id]-1的下个位置
//i到m-1恰为m-i，与p[2*id-i]较小者为潜在的p[i]
int get_max()
{
	int id = 0,mx = 0,temp = 0;
	memset(p,0,sizeof(p));
	for(int i = 1;i<=21;i++)
	{
		p[i]=(mx>i)?min(mx-i,p[2*id-i]):1;
		while(sss[i+p[i]]==sss[i-p[i]])
			p[i]++;
		if(i+p[i]>mx)
		{
			mx=i+p[i];
			id = i;
		}
		if(p[i]>temp)
			temp = p[i];
	}
	return temp-1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	init();
	printf("%d\n",get_max());
	getchar();
	return 0;
}

