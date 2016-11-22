// 不重叠至少出现2次的公共子串.cpp : 定义控制台应用程序的入口点。
//给出n个字符串，求一个最长的串x，x在每个字符串中不重叠出现至少两次。
//对于多串问题，先将它们连起来，中间用没出现过且不相同的字符隔开，然后二分答案，判断时利用相近串相似根据height给后缀分组。
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
    else return i;//索引x所在的子串号码
} 
int check(int k){
    int v[maxn]={0},ma[maxn]={-1},min[maxn]={inf},i,x;//max[i]  min[i]标记i号子串中，在当前分组内找到的前缀的起始位置
    for (i=1;i<=len;i++){
        if (height[i]<k){//跨组 考虑上次的分组
           int j;
           for (j=1;j<=n;j++){
              if (v[j]<2) {j=0;break;}//之前组的公共前缀在某个子串内没有出现2次
              if (ma[j]-min[j]<k) {j=0;break;}//在j号子串内出现至少2次  但重叠  若上面的if满足 则当前的min max一定被更新过
           }
           if (j==n+1) return 1;
           for (j=0;j<=n;j++){//进入新组  重置min max v[]
              ma[j]=-1;
              min[j]=inf;
              v[j]=0;
           }
        }
		//组内
        x=get(sa[i]);//height[i]>=k suffix(sa[i])与suffix(sa[i-1])的后缀公共前缀长度大于k，且sa[i]在x号子串内
		//若height[i]<k  说明此时新进入一个分组 重置更新x号子串内的max min 
        ma[x]=ma[x]>sa[i]?ma[x]:sa[i];//组内更新max min
        min[x]=min[x]<sa[i]?min[x]:sa[i];
        v[x]++;//出现在了x子串内 标记
    }
    return 0;
}
void solve(){//二分找最长的子串
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

