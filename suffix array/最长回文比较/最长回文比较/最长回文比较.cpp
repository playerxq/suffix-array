// ����ıȽ�.cpp : �������̨Ӧ�ó������ڵ㡣
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
//p[id]Ϊ����id����뾶
//mxΪid+p[id] Ϊ�����Ͻ�id+p[id]-1���¸�λ��
//i��m-1ǡΪm-i����p[2*id-i]��С��ΪǱ�ڵ�p[i]
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

