// 最长重复子串.cpp : 定义控制台应用程序的入口点。
//重复子串，必然是某两个后缀的公共前缀
//最长的一个重复子串应该是height中的最大值

#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxn=100010;
int wss[maxn],wa[maxn],wb[maxn],wv[maxn],a[maxn],sa[maxn],rank[maxn],height[maxn];
int cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int* r, int* sa, int n, int m)
{
	int i,j,p,*x=wa,*y=wb,*t;
	for(i = 0;i<m;i++)
		wss[i]=0;
	for(i = 0;i<n;i++)
	{
		x[i]=r[i];
		wss[x[i]]++;
	}
	for(i = 1;i<m;i++)
		wss[i]+=wss[i-1];
	for(i = n-1;i>=0;i--)
		sa[--wss[x[i]]]=i;
	for(p = 1,j = 1;p<n;j*=2,m=p)
	{
		for(p = 0,i = n-j;i<n;i++)
			y[p++]=i;
		for(i = 0;i<n;i++)
		{
			if(sa[i]>=j)
				y[p++]=sa[i]-j;
		}
		for(i = 0;i<n;i++)
			wv[i]=x[y[i]];
		for(i = 1;i<m;i++)
			wss[i]=0;
		for(i = 0;i<n;i++)
			wss[wv[i]]++;
		for(i = 1;i<m;i++)
			wss[i]+=wss[i-1];
		for(i = n-1;i>=0;i--)
			sa[--wss[wv[i]]]=y[i];
		for(t = x,x=y,y=t,p=1,x[sa[0]]=0,i = 1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
void calheight(int* r, int* sa, int n)
{
	int i,j,k=0;
	for(i = 1;i<=n;i++)
	{
		rank[sa[i]]=i;
		height[i]=0;
	}
	for(i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j = sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int _tmain(int argc, _TCHAR* argv[])
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int t,i,j;
    cin >> t;
    while (t--){
          char s[maxn];
          cin >> s;
          int n=strlen(s);
          for (i=0;i<n;i++) a[i]=static_cast<int>(s[i]);
          a[n]=0;
          da(a,sa,n+1,255);
          calheight(a,sa,n);
          int max=0,k=0;
          for (i=1;i<=n;i++) 
            if (max<height[i]){
               max=height[i];
               k=sa[i];
            }
          for (i=k,j=0;j<max;j++,i++) cout << s[i];
          cout << endl;
    }
    return 0;
}

