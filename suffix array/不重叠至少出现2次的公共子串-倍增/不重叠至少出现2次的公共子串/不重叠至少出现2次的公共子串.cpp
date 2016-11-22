// ���ص����ٳ���2�εĹ����Ӵ�.cpp : �������̨Ӧ�ó������ڵ㡣
//����n���ַ�������һ����Ĵ�x��x��ÿ���ַ����в��ص������������Ρ�
//���ڶമ���⣬�Ƚ��������������м���û���ֹ��Ҳ���ͬ���ַ�������Ȼ����ִ𰸣��ж�ʱ������������Ƹ���height����׺���顣
//
#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxl=10010;
const int maxn=11;
const int inf=100000000;
#define max maxl*maxn
int w[max],wa[max],wb[max],wv[max];
int sa[max],height[max],rank[max];
int r[max],n,len,a[maxn];
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
         for (t=x,x=y,y=t,x[sa[0]]=0,p=1,i=1;i<n;i++){
             x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
         }
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
int get(int x){
    int i,j;
    for (i=1,j=a[0];x>j;j+=a[i]+1,i++);
    if (x==j) return 0;
    else return i;//����x���ڵ��Ӵ�����
} 
int check(int k){
    int v[maxn]={0},ma[maxn]={-1},min[maxn]={inf},i,x;//max[i]  min[i]���i���Ӵ��У��ڵ�ǰ�������ҵ���ǰ׺����ʼλ��
    for (i=1;i<=len;i++){
        if (height[i]<k){//���� �����ϴεķ���
           int j;
           for (j=1;j<=n;j++){
              if (v[j]<2) {j=0;break;}//֮ǰ��Ĺ���ǰ׺��ĳ���Ӵ���û�г���2��
              if (ma[j]-min[j]<k) {j=0;break;}//��j���Ӵ��ڳ�������2��  ���ص�  �������if���� ��ǰ��min maxһ�������¹�
           }
           if (j==n+1) return 1;
           for (j=0;j<=n;j++){//��������  ����min max v[]
              ma[j]=-1;
              min[j]=inf;
              v[j]=0;
           }
        }
		//����
        x=get(sa[i]);//height[i]>=k suffix(sa[i])��suffix(sa[i-1])�ĺ�׺����ǰ׺���ȴ���k����sa[i]��x���Ӵ���
		//��height[i]<k  ˵����ʱ�½���һ������ ���ø���x���Ӵ��ڵ�max min 
        ma[x]=ma[x]>sa[i]?ma[x]:sa[i];//���ڸ���max min
        min[x]=min[x]<sa[i]?min[x]:sa[i];
        v[x]++;//��������x�Ӵ��� ���
    }
    return 0;
}
void solve(){//����������Ӵ�
    int l=0,r=len,mid;
    for (mid=(r+l)>>1;l+1<r;mid=(r+l)>>1){
        if (check(mid)) l=mid;
        else r=mid-1;
    }
    if (check(r)) l=r;
    printf("%d",l);
    return;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int i,testcase;
    scanf("%d",&testcase);
    while (testcase--){
          scanf("%d",&n);
          char x[maxl];
          len=0;
          for (i=0;i<n;i++){
              scanf("%s",&x);
              a[i]=strlen(x);
              for (int j=0;j<a[i];j++){
                  r[len++]=x[j];
              }
              r[len++]=i+200;
          }
          r[len]=0;
          da(r,sa,len+1,350);
          cal(r,sa,len);
          solve();
          printf("\n");
    }
	return 0;
}

