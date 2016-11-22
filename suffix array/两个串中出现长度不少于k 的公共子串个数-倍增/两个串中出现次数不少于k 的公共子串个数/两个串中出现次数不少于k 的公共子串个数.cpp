// 两个串中出现长度不少于k 的公共子串个数.cpp : 定义控制台应用程序的入口点。
//给出两个字符串，求在这两个字符串中都出现长度不少于k的公共子串的个数（可以重复）。例如xx和xx这两个字符串，假如k=1，则有5个。（4个位置不同的“x”，和一个“xx”）
//根据k的值和height数组对后缀进行分组
//分组后，接下来要做的就是统计每组后缀中，能够产生多少个公共子串
//分开对两个串中的后缀进行处理。设第一个串为A串，第二个为B。
//当我们处理A串时，扫描一遍后缀，对于每组后缀中，每遇到一个属于B串的后缀，就统计它与之前出现过的属于A串的后缀的公共子串的和。然后再对B串这样做一次。

//单调栈：若是单调递增栈，则从栈顶到栈底的元素是严格递增的。若是单调递减栈，则从栈顶到栈底的元素是严格递减的。
//元素进栈过程：对于单调递增栈，若当前进栈元素为e，从栈顶开始遍历元素，把小于e或者等于e的元素弹出栈，直接遇到一个大于e的元素或者栈为空为止，然后再把e压入栈中。对于单调递减栈，则每次弹出的是大于e或者等于e的元素。
//本题使用单调递减栈  即栈顶-栈底递减
#include "stdafx.h"
#include <iostream>
using namespace std;
const int maxn=200010;
int w[maxn],wa[maxn],wb[maxn],wv[maxn];
int sa[maxn],rank[maxn],height[maxn],r[maxn];
int k,len1,len2,n,f[maxn];
int cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m){
     int i,j,p,*x=wa,*y=wb,*t;
     for (i=0;i<m;i++) w[i]=0;
     for (i=0;i<n;i++) w[x[i]=r[i]]++;
     for (i=1;i<m;i++) w[i]+=w[i-1];
     for (i=n-1;i>=0;i--) sa[--w[x[i]]]=i;
     for (j=1,p=1;p<n;m=p,j*=2){
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
         for (k?k--:0,j=sa[rank[i]-1];r[j+k]==r[i+k];k++);
     return;
}
int get(int x){
    if (x<len1) return 1;//A串
    if (x>len1) return 2;//B串
    return 0;
}
void init(){
     int i;
     for (i=1;i<=n;i++){//分组height  height>=k的连续i为一组 -=k-1后>=1
         height[i]-=k-1;//若height<k 则为0或小于0 统一为0
         if (height[i]<0) height[i]=0;
     }
     for (i=1;i<=n;i++) f[i]=get(sa[i]);//分别识别属于哪个串 为串联字符时为0
     return;
}
//扫描A后缀
//对A的每个后缀，遍历排名在其前面同一height分组的B的后缀(反之再来一次先扫B)，假设当前A的后缀排名为a,找到的B的后缀排名为b，b<a，则height[b+1]:height[a]的最小值就是最长公共前缀
//若height[b+1]:height[a]最小的值为height[p]，那么能够提供的公共子串为height[p]-=k-1
//正常来说，应使用rmq算法计算每个区间的最小值，即对a，枚举在a排名前的b,计算rmq(height[a],height[b])但可以利用单调减栈优化。
//假设考虑到b处的最小值为t,则继续向下考虑B的子串,排名c，c<b时，必有rmq(height[b+1]:height[a])>rmq(height[c+1]:height[a]) 即越向排名大的方向扫描 区间最小值增大
//若栈顶a[top]记录当前分组内，已扫描过的区间的最小值
//即若考虑到height[i-1]，t:i-1属于一个分组，当扫描到i时，a[]应保存height[t]:height[i];height[t+1]:height[i]...height[i-2]:height[i-1]各个区间的最小值，显然为递增的 大的在栈顶
//若当前height[i]比栈顶的若干元素小a[s]:a[top]，则这些元素代表的区间的最小值均应被更新，即弹出，以height[i]代替
//由于公共前缀为区间最小值-=k-1，又由于预处理时height经过-=k-1处理，即公共前缀数目就是height区间最小值，被加到结果上。
//那么当栈顶元素更新时，原来较大的被弹出的栈顶元素a[s]:a[top]与height[i]的差就是之前多加的部分，应该减去
//b[]记录相应a[]元素即区间最小值是几个区间的最小值，其中，若考虑到height[i]时，只有f[i]=A即第i号后缀属于A时，a[]中元素可以为区间上的最小值，这是因为A的后缀与排名在其前的B的后缀在height中的区间，即区间结尾必然是A的后缀
//若f[i-1]==B，视为区间尚未结束或区间开始，b[]+=1表示可以作为新区间开始。当到height[n]遇到A串结尾，若height[i]满足栈单调性没有弹出，则height[i]可作为i-1:n区间上的最小值。
//若f[i-1]=A，无论f[i]是谁，height[i]均不可能作为区间开始，只能作为区间的一段，只需保存height[i]到a[]中作为潜在的最小值考虑，b[]=0说明其无法作为单独区间或区间起点存在，即无法开始一个区间，只能作为某个区间的一部分，故区间计数不需+1
//扫描B后缀时同理
void solve(){
     int x,i,a[maxn],b[maxn],top;
     long long s=0,ans=0;
     a[0]=-1;
     for (x=1;x<=2;x++){//分别考虑A B串
         for (i=1;i<=n;i++){
             if (height[i]==0){//跨组
                top=1;//重置栈顶
                a[1]=maxn;
                b[1]=0;
                s=0;
                continue;//进入新组循环
             }
			 //对每个x的后缀 计算排名在其前面的!x串的后缀与其height区间的最小值，只有当f[i]=x时，说明遇到了x的后缀，可以记入结果
			 //组内  不可能是刚入组 即i-1与i号suffix属于当前同一组
             if (height[i]>a[top]){//比栈顶元素大 
                a[++top]=height[i];//满足单调性，直接入栈 a[top]成为当前区间的最小值
                if (f[i-1]!=x){//若i-1号后缀属于的串与当前考虑的串不同
                   b[top]=1;//区间计数+1 可以作为新区间开始
                   s+=height[i];//height[i]为原来的公共前缀减去k-1 则此时height[i]恰为最长公共前缀可以分出的长度>=k的前缀数目（从sa[i]起点）
				   //如abcde可以分成大于等于3的前缀有abcde abcd abc共3=5-2个 至于bcde等前缀由sa[k]=b处考虑 此处考虑从a出发的
                }
                else b[top]=0;//当前a栈顶是同一串的前缀 不能作为区间开始 只能作为某个区间的部分 故不能计入s
             }
             else{//比栈顶元素小
                  int tot=0;
                  while (top!=0&&height[i]<=a[top]) {tot+=b[top]; s-=a[top]*b[top--];}//维持单调性，弹出之前压入的区间最小值将其修正为现在的height 同时b[]计数弹出的最小值代表的区间总数 作为新最小值的区间数
                  a[++top]=height[i];
                  b[top]=tot;
                  if (f[i-1]!=x){//i-1号属于另一个串 当前新压入的height[i]可自己作为一个区间的开始
                     b[top]++;
                  }
                  s+=b[top]*height[i];//加新压入与弹出的差值  即修正区间最小值的和
             }
             if (f[i]==x) ans+=s;//若i号属于本串x  当前分组遇到一个x(A,B)，可以统计i号前面的区间段最小值，i号做为区间的结束 栈中的值均可作为区间的最小值 s记入结果
			 //若f[i]!=x 说明当前考虑的区间还无法结束  即没有遇到属于x的后缀
         }
     }
     cout << ans << endl;
     return;
}
int _tmain(int argc, _TCHAR* argv[])
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while (cin >> k){
          if (k==0) return 0;
          char s[maxn];
          int i;
          n=0;
          cin >> s;
          len1=strlen(s);
          for (i=0;i<len1;i++) r[n++]=s[i];
          r[n++]=1;//串联字符
          cin >> s;
          len2=strlen(s);
          for (i=0;i<len2;i++) r[n++]=s[i];
          r[n]=0;
          da(r,sa,n+1,128);
          cal(r,sa,n);
          init();
          solve();
    }
	return 0;
}

