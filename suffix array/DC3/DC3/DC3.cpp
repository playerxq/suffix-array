// DC3.cpp : 定义控制台应用程序的入口点。
//
/*
后缀分为2组，一组是起始位置模3不为0 一组是模3为0
1.对suffix(1),suffix(2),suffix(4),suffix(5)...排序，先将suffix(1)和suffix(2)合并，若suffix(1)和suffix(2)的长度不为3的倍数，各自在末尾填0使之均变为3的倍数，每3个字符为1组
计数排序，这样suffix(1)与suffix(2)合并为一个新的字符串，递归求该新字符串的后缀数组，即递归得到该新串的sa[]，之后利用此sa[]计算原字符串起始位置模3不为0的后缀的sa[],其中原字符串应以未出现过的最小字符（通常0）结尾
2.利用1的结果对第二组后缀排序，每个后缀suffix(i)可以看作字符r[i]+suffix(i+1)，而suffix(i+1)在1中计算出了其rank[i+1]，只需一次计数排序，利用rank值和r[i]做两个关键字即可算出sa[rank[i]]
3.将1，2结果合并，若是suffix(3j)与suffix(3j+1)比较，可以看作r[3j]+suffix(3j+1)与r[3j+1]+suffix(3j+2)的比较，均在1中求出了rank，利用rank[3j+1] rank[3j+2]以及r[]做关键字求sa[]
若为suffix(3j)和suffix(3j+2)比较，为r[3j]+suffix(3j+1)和r[3j+2]+suffix(3(j+1)),同样由之前的结果计算
*/

#include "stdafx.h"
#include <iostream>
using namespace std;
//模3余1的放在前 0：tb-1 tb开始放tbc-tb个模3余2的
#define F(x) ((x)/3+((x)%3==1?0:tb))//原串索引x对应rn中索引F(x)
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)//求F(x)的逆  即rn中索引x对应原串中索引G(x)
const int maxn = 10010;
int wa[maxn],wb[maxn],wv[maxn],wss[maxn];
int rank[maxn],height[maxn];
inline int c0(int* r, int a, int b)
{
	return r[a]==r[b]&&(r[a+1]==r[b+1])&&(r[a+2]==r[b+2]);
}
int c12(int k, int* r,int a, int b)//a b不一定哪个是整除3的  因此用k标识当前是模3余多少的
{
	if(k==2)//suffix(3j)和suffix(3j+2)
		return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
	else//r[3j]+suffix(3j+1)与r[3j+1]+suffix(3j+2)的比较 后面两个属于模3不为0组 由wv计算
		return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];//wv[]按排名序列计算wv[wb[i]=G(san[i])]=i=wv[t]  即排名i号的模3不为0后缀在原串中索引为t,wv[t]=i为名次

}
void sort(int* r, int* a, int* b, int n, int m)//计数排序 r为rank数组 a为索引数组 a[i]对应原串的索引位置 r[a[i]]即rank[a[i]]为以a[i]开头的后缀之前计算的排名 对此排名做关键字计数排序得到sa[--wss[r[a[i]]]]为a[i]开头的后缀的排名在当前串中的名次对应的起始位置 即sa[--wss[r[a[i]]]]=a[i]
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
//ta:起始位置模3为0的后缀数目 tb为起始位置模3为1的后缀个数 tbc为起始位置模3为1或2的后缀个数
//各个参数基本同倍增算法，但r,sa数组开到3n以保证空间
//rn保存1中递归处理的字符串 san保存1中新串的sa[]
void dc3(int* r, int* sa, int n, int m)
{
	int i,j,ta=0,tb=(n+1)/3,tbc=0,p,*rn=r+n,*san=sa+n;//tb为起始位置模3余1的后缀个数 显然为(n+1)/3个
	//计数排序  每次dc3开始  都将当前r串扩充2个0，使得0:n-1开头的后缀均至少有3个元素
	r[n]=0;
	r[n+1]=0;
	for(i = 0;i<n;i++)
		if(i%3!=0)
			wa[tbc++]=i;//取出第一组的后缀起始位置  wa[]为待排序元素 为原串的一些索引  
	//将wa[]中的后缀起始位置，先按后缀起始位置的第3个元素，第二个元素，第一个元素分别排序 比如原串起始索引wa[i] 从r+2计算 则r+2+wa[i]为该后缀第三个元素 以此类推 不足补0
	sort(r+2,wa,wb,tbc,m);// 
	sort(r+1,wb,wa,tbc,m);
	sort(r,wa,wb,tbc,m);
	//排序后，wb数组保存起始位置模3不为0的后缀的起始位置索引，并按其第三，第二，第一元素的顺序计数排序后的顺序  即前3个sort就是将这些后缀按每个后缀的前3个元素排序
	//F(x)计算原串suffix(x)在新串的起始位置 前面放模3余1的 后面是模三余2的 均放在r的后面 从r[n]开始 即rn=r+n
	for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
		rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;//类似倍增算法 如果w[i-1]与w[i]索引开头的后缀，在原串r中该2个后缀的前3个字符都一样 自然排名应该一样 尽管计数排序依据稳定性将其排在不同位置 即表现为wb[]的某几个连续索引对应的值为起始位置
	//由此 模3余1，2的后缀按其前3个元素排名顺序将其起始索引放在wb[]中  rn[]保存索引wb[i]起始的后缀的rank值，放在r+n开始的串中索引F(wb[i])处 可能有重复  因为两个后缀只比较了前3个元素
	//san数组为rn数组的sa数组 即san[i]保存rn数组中排名i的后缀的起始索引
	//递归计算rn数组的san数组，由于每次最后填0，故均可保持每个后缀3个元素的比较,因此一定可以得到san数组
	//设dc3得到rn的后缀的san数组 需要证明san[i]=t对应的原串索引G(t)开头的后缀也恰好排名i，即san[i]=t=F(s)=F(sa[i])
	//首先，如果原串后缀suffix(i)在rn中对应值rn[F(i)]>rn[F(j)],说明suffix(i)前3个字符大于suffix(j)，那么在原串完全的后缀排序中，suffix(i)也排在suffix(j)后面，即sa[s1]=i sa[t1]=j且s1>t1.而rn的san计算后缀排名时，由于rn[F(i)]>rn[F(j)]，故rn[F(i)]开头的后缀排在rn[F(j)]开头后缀后，也即必有san[s]=F(i),san[t]=F(j)时s>t 故san与sa同序
	//其次，如果rn[F(i)]=rn[F(j)]，suffix(i)前3个字符等于suffix(j)，则排名取决于3个之后的字符，也即suffix(i+3)与suffix(j+3)的排名，而如果i,j模3不为0，则i+3,j+3模3不为0，也属于rn，且F(i+3)=F(i)+1,F(j+3)=F(j)+1,恰好是rn[F(i)] rn[F(j)]开始的后缀的下一个元素 以此类推
	//也即后缀suffix(i) suffix(j)的大小比较可以转化为rn[F(i)] rn[F(i)+1] .。。rn[tbc-1] rn[tbc]=0 rn[tbc+1]=0和rn[F(j)] rn[F(j)+1]...rn[tbc-1] rn[tbc]=0 rn[tbc+1]=0串的比较 即suffix(rn[F(i)])和suffix(rn[F(j)])
	//因此san与sa等价 rn[F(i)]后缀在rn中排名x，即san[x]=F(i)，必有sa[x]=i
    if(p<tbc) dc3(rn,san,tbc,p);
	//上式中，如果p=tbc，说明在上面的for循环中 任意2个连续的wb[i-1] wb[i]起始后缀都没有同样的前3元素 即排名均不同 即rn元素不同
	//当rn元素不同时，其排名与元素值大小同序，又由于rn数组为tbc个后缀的名次，即值域为0:tbc-1，与rn索引值域一样，则san数组直接为rn数组的逆
	else
		for(i = 0;i<tbc;i++)
			san[rn[i]]=i;
	//将起始位置模3为0的后缀排序 suffix(x)分解为r[x]+suffix(x+1) 并且每个模3余1的起始位置必然对应一个模3为0的后缀起点，即左移一个，而suffix(x+1)的排名为rn[F(x+1)] 可以使用san排序
	//先对第二关键字排序  扫描san
	//san[i]为排名第i的后缀的起始位置（rn的索引而非r） 则当其作为第二关键字时 在按第二关键字排序时自然也排在i位 则wb[ta++]保存此时的模3为0的起点 若F(x+1)=san[i] x=3*san[i]为r中索引位置
	for(i = 0;i<tbc;i++)
		if(san[i]<tb)
			wb[ta++]=san[i]*3;
	if(n%3==1)//余1时，r的n-1号索引为3的倍数，但是由于suffix(x)被计算当且仅当suffix(x+1)包含在san[]中时，即suffix(x+1)排名在t，而F(x+1)=h，则rank[h]=t,san[t]=h,x=3h.而suffix(n)显然没有计算到san中 故需添加一个n-1
		wb[ta++]=n-1;
	sort(r,wb,wa,ta,m);//wb[]保存按第二关键字排序的suffix(x)起始位置索引即x,按r[x]排序，即第一关键字排序 结果放入wa
	for(i = 0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;//对tbc个模3不为0组的后缀，计算G(san[i])的对应原串r的起始位置，放到wb中，wv保存相应的名次 即wv[G(san[i])]为排名i的第一组的后缀在原串中的索引G(san[i])的名次为i
	//即wv为按原串索引计算的模3不为0组的rank[]
	//合并所有后缀的排序结果  放入sa
	//wa[]保存模3为0组的按排名序的原串索引值，wb[]保存模3不为0组的按序原串索引值
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
		rank[sa[i]]=i;
	}
	for(i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);

}
int r[maxn*3],sa[maxn*3];
char s[maxn];
int _tmain(int argc, _TCHAR* argv[])
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%s",s);
	int len=strlen(s);
    for(int i=0;i<len;i++) r[i]=s[i];
	r[len]=0;
	dc3(r,sa,len+1,120);
	calheight(r,sa,len);
	return 0;
}

