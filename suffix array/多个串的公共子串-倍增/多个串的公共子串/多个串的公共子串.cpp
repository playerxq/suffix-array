// 多个串的公共子串.cpp : 定义控制台应用程序的入口点。
//给出n个字符串，求一个最长的串，它出现在一半的串以上。若要多个，按字典顺序输出。
//字符串连接起来，中间用不同的没出现过在串中的字符隔开，然后再求后缀数组。
//之后的做法和求两个字符串的最长公共子串类似，先二分答案，然后根据height数组将后缀进行分组。
//如果有一个串出现在一半的串以上，那么应该有一组后缀，位于不同的串的后缀的数量大于n/2。找到最长的公共串之后，再用一个类似的过程将所有满足条件的串输出即可。
#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxl=1010;
const int maxn=101;
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
    for (i=1,j=a[0];x>j;j+=a[i]+1,i++);//j从两个串联的子串之间添加的字符处向前移动  直到x<=j即x落在当前的子串上
    if (x==j) return 0;//若x正好是两串之间的串联字符  返回0
    else return i;//返回当前子串号码
}  
//若某个前缀出现在了n/2以上的子串中 则必然有一组height（按前缀大于k分组）代表的suffix(i)后缀分属于n/2个子串
int check(int k){//找长度为k的公共前缀是否满足题目
    int v[maxn]={0},i,d,x;
    v[0]=1;//子串号码从1开始 0号不用 标记为1
    for (i=1;i<=len;i++){
        if (height[i]<k){//由排名相邻后缀的相近性 若height[i]<k即i-1与i号后缀最长前缀小于k 说明i-1与i:n号后缀均不可能在有大于k的前缀 为height分组的两组之间
           d=0;//进入新的组  数目清0
           memset(v,0,sizeof(v));
           v[0]=1;
        }
        x=get(sa[i]);//第i个后缀起始位置sa[i]所在的子串号码
        if (v[x]==0) d++;//如果当前子串没有使用过 则计数+1 说明当前前缀属于某个未标记的子串
        if (d>n/2) return 1;//多于n/2个  
        v[x]=1;
    }
    return 0;
}
void print(int k){//打印长度为k的子串
    if (k==0) {printf("?\n"); return;} 
    int v[maxn]={0},i,d,x;
    v[0]=1;
    for (i=1;i<=len;i++){//从height的开始向后搜索  每个分组子串排名均大于之前输出的分组情况 故满足字典序
        if (height[i]<k){//两组之间
            if (d>n/2) {//上一组计算得到了某个前缀满足条件 输出
               for (int j=sa[i-1];j<sa[i-1]+k;j++) printf("%c",char(r[j]));//上次的i-1号后缀所在的组有k长度的前缀满足分别属于n/2个原始子串 只需输出sa[i-1]开头的长k的子串即可
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
void solve(){//二分答案  找最可能最长的公共串
    int l=0,r=len,mid;
    for (mid=(r+l)>>1;l+1<r;mid=(r+l)>>1){
        if (check(mid)) l=mid;
        else r=mid-1;
        }
    if (check(r)) l=r;
    return print(l);
}
int _tmain(int argc, _TCHAR* argv[])
{
	int i;
    while (scanf("%d",&n)){
          if (n==0) return 0;
          char x[maxl];
          len=0;
          for (i=0;i<n;i++){
              scanf("%s",x);
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

