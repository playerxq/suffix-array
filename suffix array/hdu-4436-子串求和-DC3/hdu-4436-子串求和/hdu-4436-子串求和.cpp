// hdu-4436-�Ӵ����.cpp : �������̨Ӧ�ó������ڵ㡣
//sum[]��ʾǰ׺�ͣ�һ����num[]��ʾ����
/*
sum[1] = 1                                                          num[1] = 1 
sum[2] = 1 + 12                                                     num[2] = 12
sum[3] = 1 + 12 + 123                                               num[3] = 123
...                                                                 num[4] = 1234
sum[5] = 1 + 12 + 123 + 1234 + 12345                                num[5] = 12345

�������Ƚ� sum[4] - sum[2] �õ� 123 + 1234 �� ��������Ҫ�õ��� 3 + 34
��������Ҫ��ȥ 120 �� 1200 �� num[2] * 110
*/
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
#define INF 0x3f3f3f3f 
const int maxn = 120005;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wa[maxn],wb[maxn],wv[maxn],wss[maxn];
int rankx[maxn],height[maxn];
inline int c0(int* r, int a, int b)
{
	return r[a]==r[b]&&(r[a+1]==r[b+1])&&(r[a+2]==r[b+2]);
}
int c12(int k, int* r,int a, int b)//a b��һ���ĸ�������3��  �����k��ʶ��ǰ��ģ3����ٵ�
{
	if(k==2)//suffix(3j)��suffix(3j+2)
		return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
	else//r[3j]+suffix(3j+1)��r[3j+1]+suffix(3j+2)�ıȽ� ������������ģ3��Ϊ0�� ��wv����
		return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];//wv[]���������м���wv[wb[i]=G(san[i])]=i=wv[t]  ������i�ŵ�ģ3��Ϊ0��׺��ԭ��������Ϊt,wv[t]=iΪ����

}
void sort(int* r, int* a, int* b, int n, int m)//�������� rΪrankx���� aΪ�������� a[i]��Ӧԭ��������λ�� r[a[i]]��rankx[a[i]]Ϊ��a[i]��ͷ�ĺ�׺֮ǰ��������� �Դ��������ؼ��ּ�������õ�sa[--wss[r[a[i]]]]Ϊa[i]��ͷ�ĺ�׺�������ڵ�ǰ���е����ζ�Ӧ����ʼλ�� ��sa[--wss[r[a[i]]]]=a[i]
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
int r[3*maxn] , sa[3*maxn] ;    
char str[maxn] ; 
int n ;  
int length[maxn] ;  //ÿ�����ĺ�׺�ĳ���
int sum[maxn] ;  
int num[maxn] ;  
int ten[maxn] ; 
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	ten[0] = 0 ;  
    for( int i = 1 ; i <= 120000 ; i ++ )   //10 110 1110 11110...
        ten[i] = ( ( ten[i-1] + 1 ) * 10 ) % 2012 ;
	while( scanf( "%d" , &n ) != EOF ) 
	{  
        int len = 1 ;  
        memset( length , 0 , sizeof(length) ) ;  
          
        sum[0] = num[0] = 0 ;  
  
        r[0] = '9' + 1 ;  
        for( int i = 1 ; i <= n; i ++ ) {  
            scanf( "%s" , str ) ;  
            int l = strlen( str ) ;  
            for( int j = 0 ; j < l ; j ++ ) {  //ÿ������������Ͳ��
                r[len] = str[j] ;  
                num[len] = ( num[len-1] * 10 + str[j] - '0' ) % 2012 ;  
                sum[len] = ( sum[len-1] + num[len] ) % 2012 ;  
                length[len++] = l - j ;  
            }  
            sum[len] = num[len] = 0 ;  
            r[len++] = '9' + i + 1 ;  
        }  
        sum[len] = num[len] = 0 ;  
        r[len] = 0 ;  
  
        dc3( r , sa , len + 1 , 10200 ) ;  
        calheight( r , sa , len ) ;  
        int ans = 0 ;  
        int Min = 0 ;  
		//��һ����׺
        if( r[sa[1]] >= '1' && r[sa[1]] <= '9' ) {  //��ʼ������Ч length[sa[1]]Ϊ��ʼλ���ڸú�׺���ڵ�ԭ�����ṩ�ĺ�׺���� t1ָ���ԭ�����һ������
            int s = sa[1] - 1 , t1 = s + length[sa[1]] , t2 = s + Min ;  
            ans += sum[t1] - sum[s] - num[s] * ten[t1-s] - ( sum[t2] - sum[s] - num[s] * ten[t2-s] ) ;   
            Min = INF ;  
            ans %= 2012 ;  
            ans = ( ans + 2012 ) % 2012 ;  
        }   
        for( int i = 2 ; i <= len ; i ++ ) {  
            Min = min( Min , height[i] ) ;  
            if( r[sa[i]] >= '1' && r[sa[i]] <= '9' ) {  
                int s = sa[i] - 1 , t1 = s + length[sa[i]] , t2 = s + Min ;  
                ans += sum[t1] - sum[s] - num[s] * ten[t1-s] - ( sum[t2] - sum[s] - num[s] * ten[t2-s] ) ;   
                Min = INF ;  
                ans %= 2012 ;  
                ans = ( ans + 2012 ) % 2012 ;  
            }  
        }  
        printf( "%d\n" , ans ) ;  
    }  
    return 0 ; 
}

