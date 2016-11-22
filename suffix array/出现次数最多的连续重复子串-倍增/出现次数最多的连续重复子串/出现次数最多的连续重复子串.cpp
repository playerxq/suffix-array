// ���ִ������������ظ��Ӵ�.cpp : �������̨Ӧ�ó������ڵ㡣
//����һ���ַ���������ַ����г��ִ������������ظ��Ӵ�
//�����ظ� ��˱�Ȼ��������׺ �乫��ǰ׺Ϊ�ظ��Ӵ����ظ���+1
/*
����һ������Ϊl���Ӵ��ظ����֣�����s[i]��s[i+l]�Ĺ���ǰ׺L����L>l�����s[i]��ʼL��Ӧ����s[i+l]��ͷ��l������L���ٰ���2��l������
//���ԣ����ǿ���ö��һ��i������ÿ��i*l��λ�ã����ú�׺��������������ǰ׺��k/l+1��i*l..(i+1)*l��һ���ظ����ֵĴ���
���ڼ���suffix(i)��suffix(i+l)�г���K�Ĺ���ǰ׺��������k%l+1����ǰl��
��ͼ֪x=k%lӦΪ��ǰl����ǰ�벿�� l-xΪ��벿�� �ҹ���ǰ׺k������x���� 
��i��i+l������Ǩ��l-x����λ  ��ԭ����l����Ϊl-x:x�ķ�l�� 
����i��i+lֻ��l��Ԫ�أ���i+l����l-x��ǰl-x��Ԫ��ǡΪԭl���ĺ�l-x���֣���Ǩ�ƺ��������׺�Ĺ���ǰ׺����K��˵��i��׺����l-x����Ҳ��ԭl��l-x����
�ɴ˷�l�����Թ��ɱ�ԭl����һ���������� ��ǡ�ý�֮ǰkǰ׺��β��x������������
*/
#include "stdafx.h"
#include <iostream>
#include "math.h"
using namespace std;
const int maxn=50010;
const int inf=5000000;
int w[maxn],wa[maxn],wb[maxn],wv[maxn];
int sa[maxn],rank[maxn],height[maxn];
int a[maxn],f[maxn][20],n,ft[maxn];
int cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m){
     int i,j,p,*x=wa,*y=wb,*t;
     for (i=0;i<m;i++) w[i]=0;
     for (i=0;i<n;i++) w[x[i]=r[i]]++;
     for (i=1;i<m;i++) w[i]+=w[i-1];
     for (i=n-1;i>=0;i--) sa[--w[x[i]]]=i;
     for (p=1,j=1;p<n;m=p,j*=2){
         for (p=0,i=n-j;i<n;i++) y[p++]=i;
         for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;
         for (i=0;i<m;i++) w[i]=0;
         for (i=0;i<n;i++) w[wv[i]=x[y[i]]]++;
         for (i=1;i<m;i++) w[i]+=w[i-1];
         for (i=n-1;i>=0;i--) sa[--w[wv[i]]]=y[i];
         for (t=x,x=y,y=t,x[sa[0]]=0,p=1,i=1;i<n;i++)
         x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
     }
     return;
}
void cal(int *r,int *sa,int n){
     int i,j,k=0;
     for (i=1;i<=n;i++) rank[sa[i]]=i;
     for (i=0;i<n;height[rank[i++]]=k)
         for (k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
     return;
}
int nmin(int a,int b){
    return a<b?a:b;
}
void rmq(int n){
     int i,j;
     for (i=1;i<=n;i++) 
       f[i][0]=height[i];
     for (j=1;j<20;j++)
         for (i=1;i+(1<<j)-1<=n;i++)
         f[i][j]=nmin(f[i][j-1],f[i+(1<<j-1)][j-1]);
     return;
}
int lcp(int a,int b){//rmq ����a b��ͷ�ĺ�׺��height�������Сֵ  ������ǰ׺
    int x=rank[a],y=rank[b];
    if (x>y) {int t=x; x=y; y=t;}
    x++;//rank[a]+1��ʼ
    int t=ft[y-x+1];//log(y-x+1)
    return nmin(f[x][t],f[y-(1<<t)+1][t]);
}
void solve(){
     int l,i,k,max=0,r=0,t;
     for (l=1;l<n;l++)
         for (i=0;i+l<n;i+=l){
             k=lcp(i,i+l);//�鿴s[i]��s[i+l]�Ĺ���ǰ׺k 
             r=k/l+1;//rΪ��ǰl���ȵ��Ӵ������ظ����ִ���
             t=i-(l-k%l);//��x=k%l ԭl��Ϊx:l-x ���ڷ�תΪl-x:x ��t������ ǡ�ö�һ��
             if (t>=0)
                if (lcp(t,t+l)>=k) r++;
             if (r>max)
               max=r;
         }
     printf("%d\n",max);
     return;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int i,testcase=0;
    char x;
    for (i=0;i<maxn;i++) ft[i]=int(double(log((double)i))/log((double)2.00));
    scanf("%d\n",&testcase);
    while (testcase--){
          scanf("%d\n",&n);
          for (i=0;i<n;i++) {
              scanf("%c\n",&x);
              a[i]=x;
          }
          a[n]=0;
          da(a,sa,n+1,128);
          cal(a,sa,n);
          rmq(n);
          solve();
          }
    return 0;
}

