// poj-2406-DC3最大复制k次得到原串.cpp : 定义控制台应用程序的入口点。
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
const int maxn=1000003;
int wa[maxn],wb[maxn],wv[maxn],wss[maxn],a[maxn];
int rankx[maxn],height[maxn];
int r[maxn*3],sa[maxn*3];
char str[maxn];
int f[maxn],n;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
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
	int i,j,k=0;
	for(i = 1;i<=n;i++)
	{
		height[i]=0;
		rankx[sa[i]]=i;
	}
	for(i = 0;i<n;height[rankx[i++]]=k)
		for(k?k--:0,j=sa[rankx[i]-1];r[i+k]==r[j+k];k++);

}
void rmq()//f[i]为排名i的后缀与排名rank[0]后缀（suffix(0)）的公共前缀  即height[i+1]:height[rank[0]]或者height[rank[0]+1]:height[i]区间最小值
{
     int i,j=rankx[0];
	 f[j]=1000000;//j为0索引后缀的排名  要计算的是排名为i的后缀与排名rank[0]的0号索引后缀的最长前缀 即height[i]与height[rank[0]]区间的最小值
     for (i=j-1;i>=0;i--){//搜索i:rank[0]区间上的最小值
         if(f[i+1]>height[i+1])
			 f[i]=height[i+1];
		 else
			 f[i]=f[i+1];
     }
     for (i=j+1;i<=n;i++){//搜索rank[0]:n区间上的最小值
         if(f[i-1]>height[i])
			 f[i]=height[i];
		 else
			 f[i]=f[i-1];
     }
     return;
}
int work(int n){
    int i;
    for (i=1;i<=n/2;i++)
        if (n%(i)==0)//子串长度为n的约数
           if (f[rankx[i]]==n-i) return n/(i);//长度为i+1 即第一个串为0:i 则第二个串的开始索引为i+1 考察f[rank[i+1]]即排名rank[i+1]后缀与排名rank[0]后缀前缀长度 亦即起始i+1的后缀suffix(i+1)与suffix(0)公共前缀 若为n-i-1则为0:i的复制n/(i+1)次
    return 1;
}
int f[maxn][20],n,ft[maxn];
int len,len1;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	for(int i = 0;i<maxn;i++)
		ft[i]=(int)((double)(log((double)i))/log(2));
	while (scanf("%s",str)!=EOF && !(str[0]=='.' && strlen(str)==1))  
    {  
		memset(r,0,sizeof(r));
        n=strlen(str);  
		for(int i=0;i<n;i++)  
	      r[i]=str[i];  
		r[n]=0; 
        dc3(r,sa,n+1,128);  
        calheight(r,sa,n);  
        rmq();  
        printf("%d\n",work(n));  
    }
	return 0;
}

