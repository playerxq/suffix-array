// poj-2774-DC3�������е���ظ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
const int maxn=200004;
int wa[maxn],wb[maxn],wv[maxn],wss[maxn],a[maxn];
int rankx[maxn],height[maxn];
int r[maxn*3],sa[maxn*3];
char s[maxn];
char s1[100001];
int n,n1;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
inline int c0(int* r, int a, int b)
{
	return r[a]==r[b]&&(r[a+1]==r[b+1])&&(r[a+2]==r[b+2]);
}
int c12(int k, int* r,int a, int b)//a b��һ���ĸ�������3��  �����k��ʶ��ǰ��ģ3����ٵ�
{
	if(k==2)//suffix(3j)��suffix(3j+2)
		return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
	else//r[3j]+suffix(3j+1)��r[3j+1]+suffix(3j+2)�ıȽ� ������������ģ3��Ϊ0�� ��wv����
		return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];//wv[]���������м���wv[wb[i]=G(san[i])]=i=wv[t]  ������i�ŵ�ģ3��Ϊ0��׺��ԭ��������Ϊt,wv[t]=iΪ����

}
void sort(int* r, int* a, int* b, int n, int m)
{
	int i;
	for(i = 0;i<m;i++)
		wss[i]=0;
	for(i = 0;i<n;i++)
		wv[i]=r[a[i]];
	for(i = 0;i<n;i++)
		wss[wv[i]]++;
	for(i = 1;i<m;i++)
		wss[i]+=wss[i-1];
	for(i=n-1;i>=0;i--)
		b[--wss[wv[i]]]=a[i];
}
void dc3(int* r, int* sa, int n, int m)
{
	int i,j,ta=0,tb=(n+1)/3,tbc=0,p,*rn=r+n,*san=sa+n;
	r[n]=0;
	r[n+1]=0;
	for(i = 0;i<n;i++)
		if(i%3!=0)
			wa[tbc++]=i;
	sort(r+2,wa,wb,tbc,m);  
	sort(r+1,wb,wa,tbc,m);
	sort(r,wa,wb,tbc,m);//wb[i]Ϊǰ�����ַ�����������i����ʼ����
	for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)//������˳��  ���ν���ʼ����תΪF�������Ӧrank
		rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
    if(p<tbc) dc3(rn,san,tbc,p);
	else
		for(i = 0;i<tbc;i++)
			san[rn[i]]=i;
	for(i = 0;i<tbc;i++)
		if(san[i]<tb)
			wb[ta++]=san[i]*3;
	if(n%3==1)
		wb[ta++]=n-1;
	sort(r,wb,wa,ta,m);
	for(i = 0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;
	for(i = 0,p = 0,j = 0;i<ta&&j<tbc;p++)
		sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
	for(;i<ta;p++)
		sa[p]=wa[i++];
	for(;j<tbc;p++)
		sa[p]=wb[j++];
}
void calheight(int* r, int* sa, int n)
{
	int i,j,k=0;
	for(i = 1;i<=n;i++)
	{
		height[i]=0;
		rankx[sa[i]]=i;
	}
	for(i = 0;i<n;height[rankx[i++]]=k)
		for(k?k--:0,j=sa[rankx[i]-1];r[i+k]==r[j+k];k++);

}
int work()  
{  
    int i,ans=0;  
    for (i=2;i<=n;i++)  
        if (sa[i]<n1) a[i]=0;  
        else a[i]=1;  
    for (i=3;i<=n;i++)  
        if (a[i]!=a[i-1] && height[i]>ans)  //����һ������  ȡheight���ֵ
           ans=height[i];  
    return ans;  
} 
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%s",s);  
    scanf("%s",s1);  
    n1=strlen(s);  
    strcat(s,"$");  
    strcat(s,s1);  
    n=strlen(s);  
    for(int i = 0;i<n;i++)
		r[i]=s[i];
	r[n]=0;
    dc3(r,sa,n+1,128);  
    calheight(r,sa,n);  
    printf("%d\n",work());  
	return 0;
}

