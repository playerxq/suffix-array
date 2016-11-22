// 最长回文.cpp : 定义控制台应用程序的入口点。
//将字符串反转，拼接到原字符串之后，中间用不影响后缀排序的不为0的字符隔开，比如1，最后照常添加元素0
//转化为求一个后缀和一个倒着写的后缀的最长公共前缀
//两个后缀的最长公共前缀为两个后缀排序之后，它们之间的串的height值的最小值。这个可以自己举个具体例子好好体会。用st算法求解rmq问题即可。
////设A[i]是要求区间最值的数列，F[i, j]表示从第i个数起连续2^j个数中的最大值。（DP的状态）F[i,0]就等于A[i]
//F[i, j]=max（F[i，j-1], F[i + 2^(j-1)，j-1]）
//查询的区间为(i,j)  k=log2( j - i + 1)，则有：RMQ(A, i, j)=max{F[i , k], F[ j - 2 ^ k + 1, k]}
#include "stdafx.h"
#include <iostream>
#include "math.h"
using namespace std;
const int maxn=2010;
int n,wss[maxn],wa[maxn],wb[maxn],wv[maxn],a[maxn],sa[maxn],rank[maxn],height[maxn],f[maxn][20];
int cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int* r, int* sa, int n, int m)
{
	int i,j,p,*x=wa,*y=wb,*t;
	for(i = 0;i<m;i++)
		wss[i]=0;
	for(i = 0;i<n;i++)
		wss[x[i]=r[i]]++;
	for(i = 1;i<m;i++)
		wss[i]+=wss[i-1];
	for(i = n-1;i>=0;i--)
		sa[--wss[x[i]]]=i;
	for(p=1,j=1;p<n;j*=2,m=p)
	{
		for(i = n-j,p=0;i<n;i++)
			y[p++]=i;
		for(i = 0;i<n;i++)
			if(sa[i]>=j)
				y[p++]=sa[i]-j;
		for(i = 0;i<n;i++)
			wv[i]=x[y[i]];
		for(i = 0;i<m;i++)
			wss[i] = 0;
		for(i = 0;i<n;i++)
			wss[wv[i]]++;
		for(i = 1;i<m;i++)
			wss[i]+=wss[i-1];
		for(i = n-1;i>=0;i--)
			sa[--wss[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
void calheight(int* r, int* sa, int n)
{
	int i,j,k=0;
	for(i = 1;i<=n;i++)
	{
		rank[sa[i]]=i;
		height[i] = 0;
	}
	for(i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int nmax(int a,int b){
    if (a>b) return a; else return b;
}
int nmin(int a,int b){
    if (a<b) return a; else return b;
}
void rmq(int *rank,int n){//dp rmq
     int i,j;
     memset(f,127,sizeof(f));
     for (i=1;i<=n;i++) f[i][0]=height[i];
     for (j=1;j<20;j++)
         for (i=1;i+(1<<j)-1<=n;i++)
             f[i][j]=nmin(f[i][j-1],f[(1<<(j-1))+i][j-1]);
     return;
}
//查询x, y做索引开头的后缀的最长公共串就是height[rank[x]+1]:height[rank[y]]的最小值
int get_rmq(int x,int y){
    int a=rank[x],b=rank[y];
    if (a>b) {int t=a; a=b; b=t;}
    a++;//从rank[x]+1开始计算
    int t=int(log(double(b-a+1))/log(2.00));
    return nmin(f[a][t],f[b-(1<<t)+1][t]);
}
int _tmain(int argc, _TCHAR* argv[])
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	char s[maxn];
    cin >> s;
    n=strlen(s);
    int i,ans=0,k=0;
    for (i=0;i<n;i++) a[i]=int(s[i]);
    a[n]=1;
    for (i=0;i<n;i++) a[i+n+1]=int(s[n-1-i]);
    a[2*n+1]=0;
    da(a,sa,2*n+2,123);
    calheight(a,sa,2*n+1);
	rmq(rank,2*n+1);
	for (i=0;i<n;i++){
        int t=get_rmq(i,2*n-i)*2-1;//正向串的i处开始的后缀  关于n对称的是2n-i处，若2n-i开始的后缀与i开始的有公共前缀 说明原正向串i处有回文
        if (t>ans) 
        {
                   ans=t;
                   k=i;
        }
        if (i>0) 
        {
                 t=get_rmq(i,2*n-i+1)*2;
                 if (t>ans) 
                 {
                            ans=t;
                            k=i;
                 }
        }
    }
    if (ans%2!=0) for (i=k-ans/2;i<=k+ans/2;i++) cout<<s[i];
    else for (i=k-ans/2;i<k+ans/2;i++) cout<<s[i];
    cout<<endl;
	return 0;
}

