// �����.cpp : �������̨Ӧ�ó������ڵ㡣
//���ַ�����ת��ƴ�ӵ�ԭ�ַ���֮���м��ò�Ӱ���׺����Ĳ�Ϊ0���ַ�����������1������ճ����Ԫ��0
//ת��Ϊ��һ����׺��һ������д�ĺ�׺�������ǰ׺
//������׺�������ǰ׺Ϊ������׺����֮������֮��Ĵ���heightֵ����Сֵ����������Լ��ٸ��������Ӻú���ᡣ��st�㷨���rmq���⼴�ɡ�
////��A[i]��Ҫ��������ֵ�����У�F[i, j]��ʾ�ӵ�i����������2^j�����е����ֵ����DP��״̬��F[i,0]�͵���A[i]
//F[i, j]=max��F[i��j-1], F[i + 2^(j-1)��j-1]��
//��ѯ������Ϊ(i,j)  k=log2( j - i + 1)�����У�RMQ(A, i, j)=max{F[i , k], F[ j - 2 ^ k + 1, k]}
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
//��ѯx, y��������ͷ�ĺ�׺�������������height[rank[x]+1]:height[rank[y]]����Сֵ
int get_rmq(int x,int y){
    int a=rank[x],b=rank[y];
    if (a>b) {int t=a; a=b; b=t;}
    a++;//��rank[x]+1��ʼ����
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
        int t=get_rmq(i,2*n-i)*2-1;//���򴮵�i����ʼ�ĺ�׺  ����n�ԳƵ���2n-i������2n-i��ʼ�ĺ�׺��i��ʼ���й���ǰ׺ ˵��ԭ����i���л���
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

