// poj-3639-重复次数最多的连续重复子串.cpp : 定义控制台应用程序的入口点。
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
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
const int maxn = 100010;
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
	int i,j,k=0;
	for(i = 1;i<=n;i++)
	{
		height[i]=0;
		rankx[sa[i]]=i;
	}
	for(i = 0;i<n;height[rankx[i++]]=k)
		for(k?k--:0,j=sa[rankx[i]-1];r[i+k]==r[j+k];k++);

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
void solve(){
     int i,j,k,t,r,l,maxx=0,tot=0;
     for (l=1;l<len;l++)
	 {
         for (i=0;i+l<len;i+=l)
		 {
             k=lcp(i,i+l);//查看i与i+l的公共前缀k 
             r=k/l+1;//r为当前l长度的子串连续重复出现次数
             t=i-(l-k%l);//令x=k%l 原l串为x:l-x 现在反转为l-x:x 从t处考虑 恰好多一个
             if (t>=0&&k%l!=0)
			 {
                if (lcp(t,t+l)>=k)
				{
					r++;
			     }
			}
             if (r>maxx)
			 {
				 tot=0;  
                 a[++tot]=l;  
                 maxx=r; 
			 }
			 else if (r==maxx) 
			 {  
                  a[++tot]=l; 
			 }   
         }
	 }
     int st=0,tl=n;  
	 //按字典序找到匹配
     for (i=1;i<len;++i)  
	 {
         for (j=1;j<=tot;++j)  //不同长度 但保证重复次数都是maxx
         {  
             k=lcp(sa[i],sa[i]+a[j]);  
             if (k>=(maxx-1)*a[j])  //若a[j]是重复数目最多的子串长度 重复maxx次 则前缀长度(maxx-1)a[j]
             {  
                 st=sa[i];  
                 tl=maxx*a[j];  
                 i=len;  
                 break;  
             }  
         } 
	 }
     for (i=st;i<st+tl;i++)  
         printf("%c",str[i]);  
     printf("\n"); 
     return;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	for (int i=0;i<maxn;i++) ft[i]=int(double(log((double)i))/log((double)2.00));
	int kase = 1;
	while(scanf("%s",str)!=EOF)  
    {  
		if(str[0]=='#')
			break;
        len=strlen(str);
        for(int i=0;i<len;i++)  
           r[i]=str[i];  
        r[len]=0;           //注意最后一个元素尽量小，所以为0合适  
        dc3(r,sa,len+1,300);  
        calheight(r,sa,len);
		rmq(len);
		printf("Case %d: ",kase++);
		solve();
    }
}

