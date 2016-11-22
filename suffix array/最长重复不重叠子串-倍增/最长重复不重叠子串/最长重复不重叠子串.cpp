// ��ظ����ص��Ӵ�.cpp : �������̨Ӧ�ó������ڵ㡣
//�Ƚ�����ת�����������ڵ����Ĳ�ٰ��������鿴��һ���ַ�����������ת��Ϊ����ظ����ص��Ӵ��ĳ��ȣ��������������+1�����⣬��һ����������һ�����Ĳ���ڣ����ǿ��Խ�����Ϊһ���ܴ��ֵ��ʹ���������ս����Ӱ�졣
//�ȶ��ִ𰸣�������ת��Ϊ�ж������⣬Ȼ������height�������Ժ�׺���з��飬̰���ж�
//����Ϊ��height���ڻ���
//���ں�׺����ʱ��ǰ׺����������������ڣ��������i��i+1������׺�Ĺ���ǰ׺heightС��k����i��i+2:n�ĺ�׺���������г���k�Ĺ���ǰ׺
//��˿������Ա���height����ĳ��height����kʱ��˵������������׺��һ�����飬�п����в��ص���󹫹�ǰ׺����ʱ�ж�min��max�Ĳ�
//��heightС��k��������������׺����һ�飬ǰһ����׺Ҳ�������������ĺ�׺���Ժ�ĺ�׺�д���k��ǰ׺
//height<kʱ�����µķ��飬����max��min  height>kʱ�ڷ�����  ����max��min����
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
int check(int k){//�鿴��ǰ����Ϊk���Ӵ��Ƿ���ڲ��ص����ظ�
    int max=0,min=maxn;
    for (int i=1;i<=n;i++){
        if (height[i]<k)//����һ������ �����µķ��� ��min��max����Ϊsa[i]����� ���Һ�����ܵĺ�׺  i��׺ǰ�ĺ�׺�����迼��
		{
            max=min=sa[i];
        }
        else//����k  Ϊһ�������ڵĺ�׺ 
        {//�޸�max minΪ�÷����������޵����
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
        if (check(mid))//mid���ȵĴ��� �ı�l��ֵ���Ƿ���ڸ����� 
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
          k=Bin_search(0,n/2)+1;//���ص��������ǰ׺�ĳ���<=n/2  ʹ�ö��ֲ��ҵ�ǰ���ȵĴ��Ƿ����
          if (k<5) k=0;
          printf("%d\n",k);
          scanf("%d",&n);
    }
	return 0;
}

