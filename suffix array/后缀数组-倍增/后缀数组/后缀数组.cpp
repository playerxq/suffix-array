// ��׺����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#define maxn 100
int wa[maxn];
int wb[maxn];
int wv[maxn];
int ws[maxn];
int r[maxn];
int rank[maxn];
int sa[maxn];
int height[maxn];
//r[n-1]����Ϊ0
//����cmp����ʱ��rΪ��һ��ѭ���������rank���� rank[i]Ϊi������ʼ�ĺ�׺�ŵ����� ��Ȼr[n-1]=0 ��x[sa[0]]=x[n-1]=0������cmpǰx y������Ϊy[n-1]=0��
//��r[a]=r[b]��a,b������ͷ�ĺ�׺����һ�� ��ǰѭ��ʱa��b��ͷ�ĺ�׺һ�����ǵ��ַ���������0�� �������ڳ��Ȳ��ȱ�Ȼ���β�ͬ
//����a,b��ͷ�ĺ�׺��ǰ����j����a:a+j-1��b:b+j-1��������0  ���a+j��b+j���ൽ��0��  �������
int cmp(int* r, int a, int b, int l)
{
	return (r[a]==r[b])&&(r[a+l]==r[b+l]);
}
/*
r: array of compared elements r[n-1]=0
n: num of elements to be compared
m: value range of element in r
sa: sa[i] is the ith suffix string's first element's index
*/
void da(int* r, int* sa, int n, int m)
{
	//first count sort
	int i,j,p,*x=wa,*y=wb,*t;
	for(int i = 0;i<m;i++)
		ws[i]=0;
	for(int i = 0;i<n;i++)
	{
		x[i]=r[i];
		ws[x[i]]++;
	}
	for(int i = 1;i<m;i++)
		ws[i]+=ws[i-1];//ws[i]��Ϊi��ͷ���ִ�������
	for(int i = n-1;i>=0;i--)
		sa[--ws[x[i]]]=i;//sa[--ws[x[i]]]��Ϊx[i]��ͷ���ִ�����Ϊws[x[i]]����ͷ������ȻΪsa[--ws[x[i]]]=i
	//j is the substring's length
	//foreach loop, len doubled
	//�Ƚ��ϴ����������ִ��ϲ�����ִ�������  �����ؼ��ֱַ�Ϊ��һ���ִ������͵ڶ��ִ�����
	//ÿ��ѭ����ʼʱ��x[]Ϊrank�������飬��x[i]Ϊ������i����ͷ���ִ�������  y[]Ϊ��������
	//�ڶ��ؼ��������ɸ�������ѭ���õ���sa������㣬sa���鱣������i�Ŀ�ͷ��������sa[i]��Ϊ�ڶ��ؼ��֣�sa[i]-jΪ�ϲ����һ�ؼ�������
	for(j=1,p=1;p<n;j*=2,m=p)
	{
		//�ϲ��ϴ��������������ִ������� 2��2^(j)���Ⱥϲ�Ϊ2^(j+1)����
		for(p=0,i=n-j;i<n;i++)//��n-j��n-1���ִ���ͷʱ�ϲ����ִ����Ȳ���j���ʵڶ��ؼ���Ϊ0
			y[p++]=i;//����ϲ���Ŀ�ͷ�ַ�������
		//sa[i]Ϊ����ѭ��������i���ִ���ͷ��������ʱӦ����Ϊ�ڶ��ؼ�������
		for(int i = 0;i<n;i++)
		{
			if(sa[i]>=j)//������i���ִ��Ŀ�ͷ����sa[i]>=jʱ
				y[p++]=sa[i]-j;//�ϲ����ִ��Ŀ�ͷ�ַ�����Ϊsa[i]-j��������i��˳�����y[]
		}
		//��ʱy���鱣���˺ϲ����ִ����ڶ��ؼ��������Ŀ�ͷ�ַ�������Ҳ����һ�ؼ���������֮�󰴵�һ�ؼ�������  ���ݵ�������ѭ����rank��x[]
		for(int i = 0;i<n;i++)
			wv[i]=x[y[i]];//x[y[i]]Ϊ��һ�ؼ��������µ��ִ�������  ��rank
		for(int i = 0;i<m;i++)
			ws[i]=0;
		for(int i = 0;i<n;i++)
			ws[wv[i]]++;//����
		for(int i = 1;i<m;i++)
			ws[i]+=ws[i-1];
		for(int i = n-1;i>=0;i--)
			sa[--ws[wv[i]]]=y[i];//����y[i]����ͷ���ִ�������Ϊws[wv[i]]��sa[--ws[wv[i]]]����������µĿ�ͷ�ַ���������Ȼ����y[i]
		//
		//����x,y����ʱxΪ�ϲ����ִ����ڶ��ؼ��������µ��ַ�����  yΪ�ϴ��ִ����� sa[]Ϊ�ϲ���������iλ���ִ���ͷ����
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;//��i���ִ���ͷ�ַ�����Ϊsa[i]����x[sa[i]]����˿�ͷ�ַ��������ִ������Σ�����Ӧ��
		//��i���������в������ʣ���p��������y[sa[i-1]]Ϊ�ϴ�����ʱ��i-1���ε��ִ���ͷ�ַ������µ���ʵ����
		//cmpΪ��ʱ������i-1λ���ִ���ͷ������iλ�ִ���ͷ���������ֺϲ�ʱ��������ͬ�������κϲ��ĵ�һ�ؼ�����ͬ��ͬ��ڶ��ؼ�����ͬ
		//����rank��x[]�У�sa[i-1]��sa[i]�ַ�������Ӧ��ͬ��Ϊp-1��
	}
	return;
}
//height[i]Ϊsuffix(sa[i-1])��suffix(sa[i])�����ǰ׺
//h[i]=height[rank[i]] ��ԭ�ַ����У�����i����ʼ�ĺ�׺suffix(i)����������ǰ��ĺ�׺suffix(k)�������ǰ׺ rank[k]=rank[i]-1
//��Ȼsuffix(i)��suffix(k)�������ǰ׺h[i]���ٴ���suffix(i-1)��suffix(k-1)�������ǰ׺h[i-1]ȥ��һ��ͷ��h[i-1]-1
//��h[i]>=h[i-1]-1
//��h[1..n]����  h[]������ʾʵ��
void call_height(int* r, int* sa, int n)
{
	int i,j,k=0;
	for(int i = 1;i<=n;i++)
		rank[sa[i]]=i;//����
	for(int i = 0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);//jΪsuffix(i)ǰһ����׺�Ŀ�ͷ����  ������suffix(i)�Ƚ������ǰ׺
	//�������ʱ��height[rank[i]]=kΪ����  ��h[i]=k
	//��һ��ʱ������h[i]>=h[i-1]-1,����һ�ֵĳ������ٴ��ڵ���k-1���ʴ�k--��ʼ
}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

