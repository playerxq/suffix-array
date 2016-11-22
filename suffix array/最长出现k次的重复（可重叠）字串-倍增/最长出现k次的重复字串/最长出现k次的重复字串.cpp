// 最长出现k次的重复字串.cpp : 定义控制台应用程序的入口点。
//先二分答案，再查找，转化为判定性问题
//分组height  若某个分组内height数目大于要求的值，则为解

#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxn=20010;
int wss[maxn*2],wa[maxn],wb[maxn],wv[maxn],sa[maxn],rank[maxn],height[maxn],a[maxn];
int n,m,k;
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
	for(i=n-1;i>=0;i--)
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
			wss[i]=0;
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
	for(i=1;i<=n;i++)
	{
		height[i]=0;
		rank[sa[i]]=i;
	}
	for(i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);

}
int check(int x){//查看在限定长度为x时每个分组数目是否大于k
    int i,cnt;
   for (i=1;i<=n;i++)
        if (height[i]<x) cnt=1;//相邻后缀公共前缀长度小于x 进入不同分组 重置数目
        else
            if (++cnt>=k) return 1;
    if (cnt>=k) return 1;
    return 0;        
} 
int bin_search(int l,int r){
    int mid;
    for (mid=(r+l)>>1;l<=r;mid=(r+l)>>1)
        if (check(mid)) l=mid+1; else r=mid-1;
    return mid;
}
int _tmain(int argc, _TCHAR* argv[])
{
	 int i;
    while (scanf("%d %d",&n,&k)!=EOF){
          m=0;
          for (i=0;i<n;i++) 
          {
              scanf("%d",&a[i]);
              a[i]++;
              m=m>a[i]?m:a[i];
          }
          a[n]=0;
          m++;
          da(a,sa,n+1,m);
          calheight(a,sa,n);
          int k=bin_search(0,n);
          printf("%d\n",k);
    }
	return 0;
}

