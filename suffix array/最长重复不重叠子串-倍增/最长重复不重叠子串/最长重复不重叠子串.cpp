// 最长重复不重叠子串.cpp : 定义控制台应用程序的入口点。
//先将输入转化成两两相邻的数的差，再把整个数组看做一个字符串，则问题转化为求最长重复不重叠子串的长度，而答案是这个长度+1。另外，第一个数字与上一个数的差不存在，我们可以将它设为一个很大的值，使得它对最终结果不影响。
//先二分答案，将问题转化为判定性问题，然后利用height数组来对后缀进行分组，贪心判断
//分组为将height相邻划分
//由于后缀排序时，前缀最相近的两个会相邻，故如果第i与i+1两个后缀的公共前缀height小于k，则i与i+2:n的后缀都不可能有长于k的公共前缀
//因此可以线性遍历height，当某个height大于k时，说明相邻两个后缀在一个分组，有可能有不重叠最大公共前缀，此时判断min与max的差
//若height小于k，则相邻两个后缀不在一组，前一个后缀也不可能再与后面的后缀及以后的后缀有大于k的前缀
//height<k时进入新的分组，重置max与min  height>k时在分组内  更新max与min即可
#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxn=20010;
int wss[maxn],wa[maxn],wb[maxn],wv[maxn],a[maxn],x[maxn],sa[maxn],rank[maxn],height[maxn],n;
char r[maxn];
int cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void output_sa(int n)
{
	for(int i = 0;i<n;i++)
		printf("%d ",sa[i]);
	printf("\n");
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
	{
		sa[--wss[x[i]]]=i;
	}
	for(p = 1,j=1;p<n;j*=2,m=p)
	{
		for(p=0,i = n-j;i<n;i++)
			y[p++]=i;
		for(i = 0;i<n;i++)
		{
			if(sa[i]>=j)
				y[p++]=sa[i]-j;
		}
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
	for(i = 1;i<=n;i++)
	{
		height[i]=0;
		rank[sa[i]]=i;
	}
	for(i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int check(int k){//查看当前长度为k的子串是否存在不重叠的重复
    int max=0,min=maxn;
    for (int i=1;i<=n;i++){
        if (height[i]<k)//不在一个分组 进入新的分组 将min与max重置为sa[i]的起点 查找后面可能的后缀  i后缀前的后缀均不需考虑
		{
            max=min=sa[i];
        }
        else//大于k  为一个分组内的后缀 
        {//修改max min为该分组内上下限的起点
            max=max>sa[i]?max:sa[i]; 
            min=min<sa[i]?min:sa[i];
            if (max-min>=k) 
				return 1;
        }
    }
    if (max-min>=k) return 1; else return 0;
}
int Bin_search(int l,int r){
    int mid;
    for (mid=(l+r)>>1;l<=r;mid=(l+r)>>1){
        if (check(mid))//mid长度的存在 改变l的值求是否存在更长的 
			l=mid+1; 
		else r=mid-1;
    }
    if (check(mid)) 
		return mid; 
	else return 0;
} 
int _tmain(int argc, _TCHAR* argv[])
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
    while (n){
          int i,k;
          for (i=0;i<n;i++) scanf("%d",&x[i]);
          a[0]=500;
          for (i=1;i<n;i++) a[i]=x[i]-x[i-1]+100;
          a[n]=0;
          da(a,sa,n+1,501);
          cal(a,sa,n);
          k=Bin_search(0,n/2)+1;//不重叠的最长公共前缀的长度<=n/2  使用二分查找当前长度的串是否存在
          if (k<5) k=0;
          printf("%d\n",k);
          scanf("%d",&n);
    }
	return 0;
}

