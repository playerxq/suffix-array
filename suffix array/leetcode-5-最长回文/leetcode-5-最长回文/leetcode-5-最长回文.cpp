// leetcode-5-最长回文.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <queue>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
const int maxx = 3005;
int wa[maxx],wb[maxx],wv[maxx],wss[maxx];
int rankx[maxx],height[maxx];
int f[maxx][20];
inline int c0(int* r, int a, int b)
{
	return (r[a]==r[b])&&(r[a+1]==r[b+1])&&(r[a+2]==r[b+2]);
}
int c12(int k, int* r, int a, int b)
{
	if(k==2)
	{
		return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
	}
	else
		return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];
}
void sort(int* r, int* a, int* b, int n,int m)
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
	for(i = n-1;i>=0;i--)
		b[--wss[wv[i]]]=a[i];
}
void dc3(int* r, int* sa, int n, int m)
{
	int i,j,ta = 0,tb = (n+1)/3, tbc = 0,p,*rn = r+n,*san = sa+n;
	r[n]=0;
	r[n+1]=0;
	for(i = 0;i<n;i++)
		if(i%3)
			wa[tbc++]=i;
	sort(r+2,wa,wb,tbc,m);
	sort(r+1,wb,wa,tbc,m);
	sort(r,wa,wb,tbc,m);
	for(p = 1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
		rn[F(wb[i])] = c0(r,wb[i-1],wb[i])?p-1:p++;
	if(p<tbc)
		dc3(rn,san,tbc,p);
	else
		for(i = 0;i<tbc;i++)
			san[rn[i]]=i;
	for(i = 0;i<tbc;i++)
	{
		if(san[i]<tb)
			wb[ta++] = 3*san[i];
	}
	if(n%3==1)
		wb[ta++] = n-1;
	sort(r,wb,wa,ta,m);
	for(i = 0;i<tbc;i++)
		wv[wb[i]=G(san[i])]=i;
	for(i = 0,p = 0,j=0;i<ta&&j<tbc;p++)
		sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
	for(;i<ta;p++)
		sa[p] = wa[i++];
	for(;j<tbc;p++)
		sa[p] = wb[j++];
}
void calheight(int* r, int* sa, int n)
{
	int i,j,k=0;
	for(i = 1;i<=n;i++)
	{
		rankx[sa[i]]=i;
		height[i]=0;
	}
	for(i = 0;i<n;height[rankx[i++]]=k)
		for(k?k--:0,j = sa[rankx[i]-1];r[i+k]==r[j+k];k++);
}
int nmax(int a,int b){
    if (a>b) return a; else return b;
}
int nmin(int a,int b){
    if (a<b) return a; else return b;
}
void rmq(int* rank, int n)
{
	int i,j;
	memset(f,127,sizeof(f));
	for(i = 1;i<=n;i++)
		f[i][0]=height[i];
	for(j = 1;j<20;j++)
	{
		for(i = 1;i+(1<<j)-1<=n;i++)
		{
			f[i][j]=nmin(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
}
int get_rmq(int a, int b)
{
	int x = rankx[a];
	int y = rankx[b];
	if(x>y)
	{
		int t = x;
		x = y;
		y = t;
	}
	x++;
	int v = int(log((double)(y-x+1))/log(2.00));
	return nmin(f[x][v],f[y-(1<<v)+1][v]);
}
int r[3*maxx],sa[3*maxx];

class Solution {
public:
    string longestPalindrome(string s) {
        int i,ans=0,k=0;
		string str;
		int len = s.length();
		for(int i = 0;i<len;i++)
			r[i]=(int)(s[i]);
		r[len]=1;
		for (i=0;i<len;i++) r[i+len+1]=int(s[len-1-i]);
		r[2*len+1]=0;
		dc3(r,sa,2*len+2,123);
		calheight(r,sa,2*len+1);
		rmq(rankx,2*len+1);
		for(i = 0;i<len;i++)
		{
			int t = get_rmq(i,2*len-i)*2-1;
			if(t>ans)
			{
				ans = t;
				k = i;
			}
			if (i>0) 
			{
				 t=get_rmq(i,2*len-i+1)*2;
				 if (t>ans) 
				 {
					  ans=t;
					  k=i;
				 }
			}
		}
		int id = 0;
		if (ans%2!=0) for(i=k-ans/2;i<=k+ans/2;i++) str.push_back(s[i]);
		else for(i=k-ans/2;i<k+ans/2;i++) str.push_back(s[i]);
		return str;
    }
};
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	string s;
	getline(cin,s);
	Solution ss;
	cout<<ss.longestPalindrome(s);
}

