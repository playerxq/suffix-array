// �����k�εõ�ԭ��.cpp : �������̨Ӧ�ó������ڵ㡣
//����һ���ַ���s��������Ӵ�a,a�ظ�k�κ�õ�s����k�����ֵ
//���ĳ���Ӵ��ظ�k�εõ�s��������Ӵ�����x����suffix(0)��suffix(x+1)�������ǰ׺Ϊn-x �ɻ�ͼ��֤
//��λ��0ö�ٳ��� ������i+1������suffix(0)�жϵ��Ӵ�����ʼλ��Ϊi+1��suffix(i+1)�����ж�height[rank[0]]��height[rank[i+1]]�������Сֵ rmq�ж�  ע��rank[i+1]��rank[0]��С����
//rank[i]<rank[0]ʱ  ʵ�����ж�height[rank[i]+1]:height[0]�������Сֵ
//rank[i]>rank[0]ʱ  �ж�height[rank[0]+1]:height[rank[i]]����Сֵ
//����f[i]Ԥ�ȴ���

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
void rmq(int* height, int n)//f[i]Ϊ����i�ĺ�׺������rank[0]��׺��suffix(0)���Ĺ���ǰ׺  ��height[i+1]:height[rank[0]]����height[rank[0]+1]:height[i]������Сֵ
{
     int i,j=rank[0],min=n-sa[j];//jΪ0������׺������  Ҫ�����������Ϊi�ĺ�׺������rank[0]��0��������׺���ǰ׺ ��height[i]��height[rank[0]]�������Сֵ
     for (i=j;i>=1;i--){//����i:rank[0]�����ϵ���Сֵ
         f[i]=min;//����i��rank[0]����ǰ׺  ӦΪheight[i+1]:height[rank[0]]�������Сֵ ��f[i]�������ּ����height[i+1]:height[rank[0]]��Сֵ
         min=min<height[i]?min:height[i];//
     }
     for (i=j+1,min=1000000;i<=n;i++){//����rank[0]:n�����ϵ���Сֵ
         min=min<height[i]?min:height[i];//����height[rank[0]+1]:height[i]�������Сֵ  ÿ��iʱ minΪheight[rank[0]+1]:height[i-1]��Сֵ ����height[i]��������Сֵ �ٸ�ֵf[i]
         f[i]=min;
     }
     return;
}
int work(int n){
    int i;
    for (i=0;i<n;i++)
        if (n%(i+1)==0)//�Ӵ�����Ϊn��Լ��
           if (f[rank[i+1]]==n-i-1) return n/(i+1);//����Ϊi+1 ����һ����Ϊ0:i ��ڶ������Ŀ�ʼ����Ϊi+1 ����f[rank[i+1]]������rank[i+1]��׺������rank[0]��׺ǰ׺���� �༴��ʼi+1�ĺ�׺suffix(i+1)��suffix(0)����ǰ׺ ��Ϊn-i-1��Ϊ0:i�ĸ���n/(i+1)��
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

