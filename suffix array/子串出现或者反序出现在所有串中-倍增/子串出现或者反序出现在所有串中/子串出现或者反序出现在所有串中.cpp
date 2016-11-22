// 子串出现或者反序出现在所有串中.cpp : 定义控制台应用程序的入口点。
//给出n个串，求一个最长的串x，它或者它的反串出现在所有的串中。
//将所有的串以及他们的反串都连起来，中间用没出现过的不同的字符分隔开。然后二分答案后分组
//若某组后缀出现在所有的串（或它们的反串）说明有解

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
int get(int x){//查看x索引出现在哪个子串中
    int i,j;
    for (i=1,j=a[0];x>j;j+=a[i]+1,i++);//j标记串联字符
    if (x==j) return 0;
    else return i%2==0?i/2:i/2+1;//返回原来所有正序子串的号码 当前i为正反串联的号码 
}
int check(int k){
    int v[maxn]={0},i,d,x;
    v[0]=1;
    for (i=1;i<=len;i++){
        if (height[i]<k){//跨组 重置
            d=0;
            memset(v,0,sizeof(v));
            v[0]=1;
        }
        x=get(sa[i]);//找到所属的子串号码
        if (v[x]==0) d++;//未使用过  计数  正反串中改子串只需出现一次即可 v[i]=1说明原始i号子串与自身反序串联的两个串中，至少一个包含当前考虑的组的公共前缀
        if (d==n) return 1;
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
            if (d==n) {//上一组计算得到了某个前缀满足条件 输出
               for (int j=sa[i-1];j<sa[i-1]+k;j++) printf("%c",char(r[j]));//上次的i-1号后缀所在的组有k长度的前缀满足分别属于n个原始子串 只需输出sa[i-1]开头的长k的子串即可
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
              a[k++]=strlen(x);//k号串长度
              for (int j=0;j<a[k-1];j++){
                  r[len++]=x[j];
              }
              r[len++]=k+300;//串联字符
              a[k++]=strlen(x);//串联自身反序
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

