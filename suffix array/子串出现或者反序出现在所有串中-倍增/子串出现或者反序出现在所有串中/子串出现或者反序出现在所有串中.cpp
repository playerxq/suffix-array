// �Ӵ����ֻ��߷�����������д���.cpp : �������̨Ӧ�ó������ڵ㡣
//����n��������һ����Ĵ�x�����������ķ������������еĴ��С�
//�����еĴ��Լ����ǵķ��������������м���û���ֹ��Ĳ�ͬ���ַ��ָ�����Ȼ����ִ𰸺����
//��ĳ���׺���������еĴ��������ǵķ�����˵���н�

#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxl=110;
const int maxn=210;
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
int get(int x){//�鿴x�����������ĸ��Ӵ���
    int i,j;
    for (i=1,j=a[0];x>j;j+=a[i]+1,i++);//j��Ǵ����ַ�
    if (x==j) return 0;
    else return i%2==0?i/2:i/2+1;//����ԭ�����������Ӵ��ĺ��� ��ǰiΪ���������ĺ��� 
}
int check(int k){
    int v[maxn]={0},i,d,x;
    v[0]=1;
    for (i=1;i<=len;i++){
        if (height[i]<k){//���� ����
            d=0;
            memset(v,0,sizeof(v));
            v[0]=1;
        }
        x=get(sa[i]);//�ҵ��������Ӵ�����
        if (v[x]==0) d++;//δʹ�ù�  ����  �������и��Ӵ�ֻ�����һ�μ��� v[i]=1˵��ԭʼi���Ӵ��������������������У�����һ��������ǰ���ǵ���Ĺ���ǰ׺
        if (d==n) return 1;
        v[x]=1;
    }
    return 0;
}
void print(int k){//��ӡ����Ϊk���Ӵ�
    if (k==0) {printf("?\n"); return;} 
    int v[maxn]={0},i,d,x;
    v[0]=1;
    for (i=1;i<=len;i++){//��height�Ŀ�ʼ�������  ÿ�������Ӵ�����������֮ǰ����ķ������ �������ֵ���
        if (height[i]<k){//����֮��
            if (d==n) {//��һ�����õ���ĳ��ǰ׺�������� ���
               for (int j=sa[i-1];j<sa[i-1]+k;j++) printf("%c",char(r[j]));//�ϴε�i-1�ź�׺���ڵ�����k���ȵ�ǰ׺����ֱ�����n��ԭʼ�Ӵ� ֻ�����sa[i-1]��ͷ�ĳ�k���Ӵ�����
               printf("\n");
            }
            d=0;
            memset(v,0,sizeof(v));
            v[0]=1;
        }
        x=get(sa[i]);
        if (v[x]==0) d++;
        v[x]=1;
    }
    return;
}
void solve(){
    if (n==1) {printf("%d",a[0]); return;}
    int l=0,r=len,mid;
    for (mid=(r+l)>>1;l+1<r;mid=(r+l)>>1){
        if (check(mid)) l=mid;
        else r=mid-1;
        }
    if (check(r)) l=r;
    printf("%d",l);
}
int _tmain(int argc, _TCHAR* argv[])
{
	int i,testcase;
    scanf("%d",&testcase);
    while (testcase--){
          scanf("%d",&n);
          char x[maxl];
          int k=0;
          len=0;
          for (i=0;i<n;i++){
              scanf("%s",&x);
              a[k++]=strlen(x);//k�Ŵ�����
              for (int j=0;j<a[k-1];j++){
                  r[len++]=x[j];
              }
              r[len++]=k+300;//�����ַ�
              a[k++]=strlen(x);//����������
              for (int j=0;j<a[k-1];j++){
                  r[len++]=x[a[k-1]-j-1];
              }
              r[len++]=k+300;
          }
          r[len]=0;
          da(r,sa,len+1,650);
          cal(r,sa,len);
          solve();
          printf("\n");
    }
	return 0;
}

