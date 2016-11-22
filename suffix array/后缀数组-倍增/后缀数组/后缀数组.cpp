// 后缀数组.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#define maxn 100
int wa[maxn];
int wb[maxn];
int wv[maxn];
int ws[maxn];
int r[maxn];
int rank[maxn];
int sa[maxn];
int height[maxn];
//r[n-1]设置为0
//由于cmp调用时，r为上一次循环计算出的rank数组 rank[i]为i索引开始的后缀排的名次 显然r[n-1]=0 即x[sa[0]]=x[n-1]=0（调用cmp前x y互换故为y[n-1]=0）
//若r[a]=r[b]即a,b索引开头的后缀排名一样 则当前循环时a，b开头的后缀一定不是到字符串最后包括0的 否则由于长度不等必然名次不同
//由于a,b开头的后缀当前长度j，则a:a+j-1与b:b+j-1均不包含0  因此a+j与b+j至多到达0处  不会出界
int cmp(int* r, int a, int b, int l)
{
	return (r[a]==r[b])&&(r[a+l]==r[b+l]);
}
/*
r: array of compared elements r[n-1]=0
n: num of elements to be compared
m: value range of element in r
sa: sa[i] is the ith suffix string's first element's index
*/
void da(int* r, int* sa, int n, int m)
{
	//first count sort
	int i,j,p,*x=wa,*y=wb,*t;
	for(int i = 0;i<m;i++)
		ws[i]=0;
	for(int i = 0;i<n;i++)
	{
		x[i]=r[i];
		ws[x[i]]++;
	}
	for(int i = 1;i<m;i++)
		ws[i]+=ws[i-1];//ws[i]即为i开头的字串的名次
	for(int i = n-1;i>=0;i--)
		sa[--ws[x[i]]]=i;//sa[--ws[x[i]]]即为x[i]开头的字串排名为ws[x[i]]，则开头索引自然为sa[--ws[x[i]]]=i
	//j is the substring's length
	//foreach loop, len doubled
	//比较上次两个相邻字串合并后的字串的排名  两个关键字分别为第一个字串排名和第二字串排名
	//每次循环开始时，x[]为rank名次数组，即x[i]为以索引i处开头的字串的名次  y[]为辅助数组
	//第二关键字排名可根据上轮循环得到的sa数组计算，sa数组保存排名i的开头索引，将sa[i]做为第二关键字，sa[i]-j为合并后第一关键字索引
	for(j=1,p=1;p<n;j*=2,m=p)
	{
		//合并上次排序相邻两个字串并排序 2个2^(j)长度合并为2^(j+1)长度
		for(p=0,i=n-j;i<n;i++)//从n-j到n-1做字串开头时合并后字串长度不足j，故第二关键字为0
			y[p++]=i;//保存合并后的开头字符的索引
		//sa[i]为上轮循环后，排名i的字串开头索引，此时应该作为第二关键字排序
		for(int i = 0;i<n;i++)
		{
			if(sa[i]>=j)//对排名i的字串的开头索引sa[i]>=j时
				y[p++]=sa[i]-j;//合并后字串的开头字符索引为sa[i]-j，按排名i的顺序放入y[]
		}
		//此时y数组保存了合并后字串按第二关键字排序后的开头字符索引，也即第一关键字索引，之后按第一关键字排序  依据的是上轮循环的rank即x[]
		for(int i = 0;i<n;i++)
			wv[i]=x[y[i]];//x[y[i]]为第一关键字索引下的字串的名次  即rank
		for(int i = 0;i<m;i++)
			ws[i]=0;
		for(int i = 0;i<n;i++)
			ws[wv[i]]++;//计数
		for(int i = 1;i<m;i++)
			ws[i]+=ws[i-1];
		for(int i = n-1;i>=0;i--)
			sa[--ws[wv[i]]]=y[i];//索引y[i]处开头的字串，排名为ws[wv[i]]，sa[--ws[wv[i]]]保存此排名下的开头字符索引，显然就是y[i]
		//
		//互换x,y，此时x为合并后字串按第二关键字排名下的字符索引  y为上次字串名次 sa[]为合并后排名第i位的字串开头索引
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;//第i个字串开头字符索引为sa[i]，则x[sa[i]]保存此开头字符索引的字串的名次，按理应该
		//是i，但由于有并列名词，用p来计数，y[sa[i-1]]为上次排名时，i-1名次的字串开头字符索引下的真实名次
		//cmp为真时，本次i-1位的字串开头索引与i位字串开头索引在上轮合并时的名次相同，即本次合并的第一关键字相同，同理第二关键字相同
		//故在rank即x[]中，sa[i-1]与sa[i]字符的名次应相同，为p-1。
	}
	return;
}
//height[i]为suffix(sa[i-1])和suffix(sa[i])最长公共前缀
//h[i]=height[rank[i]] 即原字符串中，索引i处开始的后缀suffix(i)与排名在其前面的后缀suffix(k)的最长公共前缀 rank[k]=rank[i]-1
//显然suffix(i)与suffix(k)的最长公共前缀h[i]至少大于suffix(i-1)与suffix(k-1)的最长公共前缀h[i-1]去掉一个头即h[i-1]-1
//即h[i]>=h[i-1]-1
//按h[1..n]计算  h[]不需显示实现
void call_height(int* r, int* sa, int n)
{
	int i,j,k=0;
	for(int i = 1;i<=n;i++)
		rank[sa[i]]=i;//互逆
	for(int i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);//j为suffix(i)前一个后缀的开头索引  将其与suffix(i)比较最长公共前缀
	//当不相等时，height[rank[i]]=k为长度  即h[i]=k
	//下一轮时，由于h[i]>=h[i-1]-1,即下一轮的长度至少大于等于k-1，故从k--开始
}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

