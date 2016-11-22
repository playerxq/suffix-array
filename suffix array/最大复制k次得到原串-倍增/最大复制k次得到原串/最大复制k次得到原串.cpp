// 最大复制k次得到原串.cpp : 定义控制台应用程序的入口点。
//给出一个字符串s，则存在子串a,a重复k次后得到s。求k的最大值
//如果某个子串重复k次得到s，假设改子串长度x，则suffix(0)与suffix(x+1)的最长公共前缀为n-x 可画图验证
//从位置0枚举长度 若长度i+1，则与suffix(0)判断的子串的起始位置为i+1即suffix(i+1)，即判断height[rank[0]]与height[rank[i+1]]区间的最小值 rmq判断  注意rank[i+1]与rank[0]大小不定
//rank[i]<rank[0]时  实质是判断height[rank[i]+1]:height[0]区间的最小值
//rank[i]>rank[0]时  判断height[rank[0]+1]:height[rank[i]]的最小值
//利用f[i]预先处理

#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxn=10010;
int wa[maxn],wb[maxn],wv[maxn],wss[maxn],rank[maxn],sa[maxn],a[maxn],height[maxn];
int cmp(int* r, int a, int b, int l)
{
	return r[a]==r[b]&&(r[a+l]==r[b+l]);
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
		for(p=0,i=n-j;i<n;i++)
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
	for(i = 1;i<=n;i++)
	{
		height[i]=0;
		rank[sa[i]]=i;
	}
	for(i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int f[maxn];
void rmq(int* height, int n)//f[i]为排名i的后缀与排名rank[0]后缀（suffix(0)）的公共前缀  即height[i+1]:height[rank[0]]或者height[rank[0]+1]:height[i]区间最小值
{
     int i,j=rank[0],min=n-sa[j];//j为0索引后缀的排名  要计算的是排名为i的后缀与排名rank[0]的0号索引后缀的最长前缀 即height[i]与height[rank[0]]区间的最小值
     for (i=j;i>=1;i--){//搜索i:rank[0]区间上的最小值
         f[i]=min;//排名i与rank[0]公共前缀  应为height[i+1]:height[rank[0]]区间的最小值 故f[i]保存上轮计算的height[i+1]:height[rank[0]]最小值
         min=min<height[i]?min:height[i];//
     }
     for (i=j+1,min=1000000;i<=n;i++){//搜索rank[0]:n区间上的最小值
         min=min<height[i]?min:height[i];//计算height[rank[0]+1]:height[i]区间的最小值  每到i时 min为height[rank[0]+1]:height[i-1]最小值 代入height[i]计算新最小值 再赋值f[i]
         f[i]=min;
     }
     return;
}
int work(int n){
    int i;
    for (i=0;i<n;i++)
        if (n%(i+1)==0)//子串长度为n的约数
           if (f[rank[i+1]]==n-i-1) return n/(i+1);//长度为i+1 即第一个串为0:i 则第二个串的开始索引为i+1 考察f[rank[i+1]]即排名rank[i+1]后缀与排名rank[0]后缀前缀长度 亦即起始i+1的后缀suffix(i+1)与suffix(0)公共前缀 若为n-i-1则为0:i的复制n/(i+1)次
    return 0;
}
char s[maxn];
int _tmain(int argc, _TCHAR* argv[])
{
	while (scanf("%s",s)!=EOF){
       if (strcmp(s,".")==0) return 0;
       int n=strlen(s),i;
       for (i=0;i<n;i++) a[i]=static_cast<int>(s[i]);
       a[n]=0;
       da(a,sa,n+1,123);
       calheight(a,sa,n);
       rmq(height,n);
       printf("%d\n",work(n));
    }
    return 0;
}

