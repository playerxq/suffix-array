// 出现次数最多的连续重复子串.cpp : 定义控制台应用程序的入口点。
//给出一个字符串，求该字符串中出现次数最多的连续重复子串
//连续重复 因此必然有两个后缀 其公共前缀为重复子串的重复数+1
/*
假设一个长度为l的子串重复出现，考虑s[i]与s[i+l]的公共前缀L，若L>l，则从s[i]开始L还应包含s[i+l]开头的l串，即L至少包含2个l，类推
//所以，我们可以枚举一个i，对于每个i*l的位置，利用后缀数组可以求出公共前缀。k/l+1即i*l..(i+1)*l这一段重复出现的次数
现在假设suffix(i)与suffix(i+l)有长度K的公共前缀，即包含k%l+1个当前l串
画图知x=k%l应为当前l串的前半部分 l-x为后半部分 且公共前缀k部分以x结束 
将i与i+l均向左迁移l-x个单位  将原来的l串换为l-x:x的反l串 
由于i与i+l只差l个元素，故i+l左移l-x后，前l-x个元素恰为原l串的后l-x部分，若迁移后的两个后缀的公共前缀大于K，说明i后缀左移l-x部分也是原l串l-x部分
由此反l串可以构成比原l串多一的连续次数 且恰好将之前k前缀结尾的x部分利用起来
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
int lcp(int a,int b){//rmq 索引a b开头的后缀的height区间的最小值  即公共前缀
    int x=rank[a],y=rank[b];
    if (x>y) {int t=x; x=y; y=t;}
    x++;//rank[a]+1开始
    int t=ft[y-x+1];//log(y-x+1)
    return nmin(f[x][t],f[y-(1<<t)+1][t]);
}
void solve(){
     int l,i,k,max=0,r=0,t;
     for (l=1;l<n;l++)
         for (i=0;i+l<n;i+=l){
             k=lcp(i,i+l);//查看s[i]与s[i+l]的公共前缀k 
             r=k/l+1;//r为当前l长度的子串连续重复出现次数
             t=i-(l-k%l);//令x=k%l 原l串为x:l-x 现在反转为l-x:x 从t处考虑 恰好多一个
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

