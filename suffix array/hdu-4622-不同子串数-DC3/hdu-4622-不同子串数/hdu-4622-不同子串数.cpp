// hdu-4622-不同子串数.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
const int maxn = 2010;
int wa[maxn],wb[maxn],wv[maxn],wss[maxn],a[maxn];
int rankx[maxn],height[maxn];
int r[maxn*3],sa[maxn*3];
char str[maxn];
int f[maxn][20],n,ft[maxn];
int len,len1;
inline int c0(int* r, int a, int b)
{
	return r[a]==r[b]&&(r[a+1]==r[b+1])&&(r[a+2]==r[b+2]);
}
int c12(int k, int* r,int a, int b)//a b不一定哪个是整除3的  因此用k标识当前是模3余多少的
{
	if(k==2)//suffix(3j)和suffix(3j+2)
		return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
	else//r[3j]+suffix(3j+1)与r[3j+1]+suffix(3j+2)的比较 后面两个属于模3不为0组 由wv计算
		return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];//wv[]按排名序列计算wv[wb[i]=G(san[i])]=i=wv[t]  即排名i号的模3不为0后缀在原串中索引为t,wv[t]=i为名次

}
void sort(int* r, int* a, int* b, int n, int m)//计数排序 r为rankxx数组 a为索引数组 a[i]对应原串的索引位置 r[a[i]]即rankxx[a[i]]为以a[i]开头的后缀之前计算的排名 对此排名做关键字计数排序得到sa[--wss[r[a[i]]]]为a[i]开头的后缀的排名在当前串中的名次对应的起始位置 即sa[--wss[r[a[i]]]]=a[i]
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
	sort(r,wa,wb,tbc,m);
	
	for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
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
	int i,j,k = 0;
	for(i = 1;i<=n;i++)
	{
		height[i]=0;
		rankx[sa[i]]=i;
	}
	for(i=0;i<n;height[rankx[i++]]=k)
	{
		for(k?k--:0,j = sa[rankx[i]-1];r[i+k]==r[j+k];k++);
	}
}
int nmin(int a,int b){
    return a<b?a:b;
}
void rmq(int n){
     int i,j;
     for (i=1;i<=n;i++) 
       f[i][0]=height[i];
     for (j=1;j<20;j++)
         for (i=1;i+(1<<j)-1<=n;i++)
         f[i][j]=nmin(f[i][j-1],f[i+(1<<j-1)][j-1]);
     return;
}
int lcp(int a,int b){//rmq 索引a b开头的后缀的height区间的最小值  即公共前缀
    int x=rankx[a],y=rankx[b];
    if (x>y) {int t=x; x=y; y=t;}
    x++;//rankx[a]+1开始
    int t=ft[y-x+1];//log(y-x+1)
    return nmin(f[x][t],f[y-(1<<t)+1][t]);
}
int pos[maxn];
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int t;
	for (int i=0;i<maxn;i++) ft[i]=int(double(log((double)i))/log((double)2.00));
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",str);
		len = strlen(str);
		for(int i = 0;i<len;i++)
			r[i]=str[i]-'a'+1;
		r[len]=0;
		dc3(r,sa,len+1,200);
		calheight(r,sa,len);
		rmq(len);
		int q,st,ed;
		scanf("%d",&q);
		for(int m = 1;m<=q;m++)
		{
			scanf("%d%d",&st,&ed);
			int ans = 0;
			for(int i = 0;i<=len;i++)
				pos[i]=-1;
			for(int i = st;i<=ed;i++)//实际索引为st-1:ed-1
				pos[rankx[i-1]]=i-1;//st:ed段后缀的名次为i时则索引为pos[i]
			int pre = -1;
			int d = 0;//d为上一个后缀与之前后缀的最大公共部分长度
			for(int i = 1;i<=len;i++)//按排名枚举每个后缀
			{
				if(pos[i]!=-1)//名次为i的后缀介于st:ed之间
				{
					if(pre != -1)
					{
						int k = lcp(pre,pos[i]);
						d = min(d,k);//当前后缀与上上个以前后缀公共部分
						k = min(k,ed-pre);//当前后缀与上一个后缀公共部分
						d = max(d,k);//当前后缀与之前后缀公共部分
						ans+=ed-pos[i]-min(d,ed-pos[i]);
						pre = pos[i];
					}
					else//第一个介于st:ed的后缀
					{
						pre = pos[i];
						ans+=ed-pos[i];//产生的后缀数
					}
				}
			}	
			printf("%d\n",ans);
		}
	}
}
