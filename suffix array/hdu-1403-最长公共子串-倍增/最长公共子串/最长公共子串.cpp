// ������Ӵ�.cpp : �������̨Ӧ�ó������ڵ㡣
//�����ַ����������ǵ�������Ӵ��ĳ���
//��lcs���𣺱�����������
//�Ƚ������ַ�����������Ϊs������sa��rankx��height������ע�⵽�������ַ����Ĺ����Ӵ���Ȼ��s��ĳ������׺�Ĺ���ǰ׺����ô��Ĺ����Ӵ���Ӧ����lcp�е����ֵ����Ϊlcp��ȡֵ��һ��height�����ڵ���Сֵ���������ֵΪheight�����ֵ��
//��height�����ֵ��Ҫ�������ж�  ֻ�зֱ������������ĺ�׺�Ĺ���ǰ׺����������

#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxn=1000010  ;
int n1,n2,wss[maxn],wa[maxn],wb[maxn],wv[maxn],sa[maxn],rankx[maxn],height[maxn],r[maxn];
char str[maxn*2]; 
int cmp(int *r,int a,int b,int l){
    return (r[a]==r[b]&&r[a+l]==r[b+l]);
}
void da(int *r,int *sa,int n,int m){
     int i,j,p,*x=wa,*y=wb,*t;
     for (i=0;i<m;i++) wss[i]=0;
     for (i=0;i<n;i++) wss[x[i]=r[i]]++;
     for (i=1;i<m;i++) wss[i]+=wss[i-1];
     for (i=n-1;i>=0;i--) sa[--wss[x[i]]]=i;
     for (j=1,p=1;p<n;j*=2,m=p){
         for (p=0,i=n-j;i<n;i++) y[p++]=i;
         for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;
         for (i=0;i<m;i++) wss[i]=0;
         for (i=0;i<n;i++) wss[wv[i]=x[y[i]]]++;
         for (i=1;i<m;i++) wss[i]+=wss[i-1];
         for (i=n-1;i>=0;i--) sa[--wss[wv[i]]]=y[i];
         for (t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
         x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
         }
     return;
}
void cal(int *r,int *sa,int n){
     int i,j,k=0;
     for (i=1;i<=n;i++) rankx[sa[i]]=i;
     for (i=0;i<n;height[rankx[i++]]=k){
         for (k?k--:0,j=sa[rankx[i]-1];r[i+k]==r[j+k];k++);
         }
     return;
} 
int len,len1;
int check(int a,int b){
    if (a>b) return check(b,a);
    if (a<len1&&b>len1) return 1;//ö����������λ��  �ֱ����������ִ�
    else return 0;
}
void solve(){
     int i,maxx=0;
	 int k;
     for (i=2;i<len;i++)
	 {
         if (check(sa[i-1],sa[i])) //���ڵĲ���ͬһ���Ӵ�
		 {	
			 if (maxx<height[i])
			 {//������������� ��i-1��iλ����������������ǰ׺  ��i-1��i+2:nҲ������
				maxx=height[i];
             }
		}
	 }
	 printf("%d\n",maxx);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	 while(scanf("%s",str)!=EOF)  
    {  
        len=strlen(str);  
        len1=len;  
        str[len]='9';  
        scanf("%s",str+len1+1);  
        len=strlen(str);  
		for(int i=0;i<len;i++)  
            r[i]=str[i];  
        r[len]=0;
        da(r,sa,len,300);  
        cal(r,sa,len);
        solve();   
    } 
	return 0;
}

