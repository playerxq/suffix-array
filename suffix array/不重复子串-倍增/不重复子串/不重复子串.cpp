// ���ظ��Ӵ�.cpp : �������̨Ӧ�ó������ڵ㡣
//����һ���ַ����������Ĳ��ظ��Ӵ��ж��ٸ�
//�����ִ�Ϊĳ����׺��ǰ׺
//����sa[k]������n-sa[k]���Ӵ�ǰ׺��������height[k]���Ǻ���һ����׺�ظ��ģ�����Ҫ��ȥ

#include "stdafx.h"
#include <iostream>
using namespace std;
const long maxn = 1010;
long wa[maxn];
long a[maxn];
long wb[maxn];
long wv[maxn];
long wss[maxn];
char r[maxn];
long rank[maxn];
long height[maxn];
long sa[maxn];
long cmp(long* r, long a, long b, long l)
{
	return (r[a]==r[b])&&(r[a+l]==r[b+l]);
}
void da(long* r, long* sa, long n, long m)
{
	long i,j,p,*x=wa,*y=wb,*t;
	for(int i = 0;i<m;i++)
		wss[i]=0;
	for(int i = 0;i<n;i++)
	{
		x[i]=r[i];
		wss[x[i]]++;
	}
	for(int i = 1;i<m;i++)
		wss[i]+=wss[i-1];
	for(int i = n-1;i>=0;i--)
		sa[--wss[x[i]]]=i;
	for(p=1,j=1;p<n;j*=2,m=p)
	{
		for(p=0,i = n-j;i<n;i++)
			y[p++]=i;
		for(int i = 0;i<n;i++)
		{
			if(sa[i]>=j)
				y[p++]=sa[i]-j;
		}
		for(int i = 0;i<n;i++)
			wv[i]=x[y[i]];
		for(int i = 0 ;i<m;i++)
			wss[i]=0;
		for(int i = 0;i<n;i++)
			wss[wv[i]]++;
		for(int i = 1;i<m;i++)
			wss[i]+=wss[i-1];
		for(int i = n-1;i>=0;i--)
			sa[--wss[wv[i]]]=y[i];
		for(t=x,x=y,y=t,x[sa[0]]=0,p=1,i=1;i<n;i++)
		{
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
		}
	}
}
void calheight(long* r, long* sa, long n)
{
	long i,j,k=0;
	for(int i = 1;i<=n;i++)
	{
		rank[sa[i]]=i;
		height[i]=0;
	}
	for(int i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j = sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int _tmain(int argc, _TCHAR* argv[])
{
	long t,i;
	cin>>t;
	while(t--)
	{
		 cin >> r;
          long n=strlen(r);
          for (int i=0;i<n;i++) a[i]=static_cast<int>(r[i]);
          a[n]=0;
          da(a,sa,n+1,256);
          calheight(a,sa,n);
          long sum=0;
          for (i=1;i<=n;i++) sum+=n-sa[i]-height[i];
          cout << sum << endl;
	}
	return 0;
}

