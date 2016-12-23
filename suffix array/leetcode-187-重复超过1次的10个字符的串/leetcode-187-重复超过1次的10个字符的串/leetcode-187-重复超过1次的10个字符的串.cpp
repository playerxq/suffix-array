// leetcode-187-重复超过1次的10个字符的串.cpp : 定义控制台应用程序的入口点。
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
#define F(x) ((x)/3+((x)%3==1?0:tb))//原串索引x对应rn中索引F(x)
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)//求F(x)的逆  即rn中索引x对应原串中索引G(x)
class Solution{
public:
	int* wa,*wb,*wss,*wv,*rankx,*height;
	int* r,*sa;
	void init(int len)
	{
		r = new int[len*3];
		sa = new int[len*3];
		wa = new int[len];
		wb = new int[len];
		wv = new int[len];
		wss = new int[len];
		rankx = new int[len];
		height = new int[len];
	}
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
	void sort(int* r, int* a, int* b, int n, int m)//计数排序 r为rankx数组 a为索引数组 a[i]对应原串的索引位置 r[a[i]]即rankx[a[i]]为以a[i]开头的后缀之前计算的排名 对此排名做关键字计数排序得到sa[--wss[r[a[i]]]]为a[i]开头的后缀的排名在当前串中的名次对应的起始位置 即sa[--wss[r[a[i]]]]=a[i]
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
		sort(r+2,wa,wb,tbc,m);// 
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
	void check(vector<string>& res,int n,string s)
	{
		int flag = 0;
		for(int i = 1;i<=n;i++)
		{
			if((height[i]>=10)&&flag==0)
			{
				res.push_back(s.substr(sa[i],10));
				flag = 1;
			}
			else if(height[i]<10)
				flag = 0;
			else
				continue;
		}
	}
    vector<string> findRepeatedDnaSequences(string s) {
		int n = s.length();
		vector<string> res;
		if(!n)
			return res;
		init(n+2);
		for(int i=0;i<n;i++) r[i]=s[i]-'A'+1;
		r[n]=0;
		dc3(r,sa,n+1,30);
		calheight(r,sa,n);
		delete r;
		//delete sa;
		delete wa;
		delete wb;
		//delete wss;
		//delete wv;
		//delete rankx;
		
		check(res,n,s);
		return res;
    }
};
//使用正常方法
//A CGT每个数字可以用二进制表示的最后3位来表示
//A is 0x41, C is 0x43, G is 0x47, T is 0x54. Still don't see it? Let me write it in octal.

//A is 0101, C is 0103, G is 0107, T is 0124. The last digit in octal are different for all four letters. That's all we need!
//开始先取s的前9个字符  一共3*9=27位 放到int t里面 之后每次t左移3位 取出最后30位  即相当于t原来代表的字符串去掉开头一个字符  右边加一个字符 保存到map里
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
		unordered_map<int, int> m;
		vector<string> r;
		int t = 0, i = 0, ss = s.size();
		while (i < 9)
			t = t << 3 | s[i++] & 7;
		while (i < ss)
			if (m[t = t << 3 & 0x3FFFFFFF | s[i++] & 7]++ == 1)
				r.push_back(s.substr(i - 10, 10));
		return r;
	}
};
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	Solution s;
	s.findRepeatedDnaSequences("CCGGCCGGCCGGCCGG");
}

