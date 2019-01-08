//#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <limits>
#include <map>
#include <cmath>
#include <vector>
#include <queue> 
#define LL long long
#define db double 
#define ft first
#define sd second
#define mp(x,y) make_pair(x,y)
//#define int LL
using namespace std;
const int N   = 233;
//const int mod = ;
const int INF =numeric_limits<int >::max();

#define rep(i,x,y) for (int i=x;i<=y;++i)
void read(int &x)
{
	x=0;
	char ch=getchar();
	int f=1;
	while (!isdigit(ch)) (ch=='-'?f=-1:0),ch=getchar();
	while ( isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	x*=f;
}
int n,x[N],y[N];
db st[N];
int tp ;
const double pi=acos(-1.);
signed main(int argc, char** argv)
{
	read(n);
	rep(i,1,n) read(x[i]),read(y[i]);
	rep(i,1,n)
	{
		tp=0;
		rep(j,1,n) if (i != j) st[++tp]=atan2(x[j]-x[i],y[j]-y[i]);
		sort(st+1,st+1+tp);
		st[0]=st[tp]-2.*pi;
		db ans=0;
		rep(i,1,n) ans=max(ans,st[i]-st[i-1]-pi);
		printf("%.18f\n",ans/2./pi);
	}
	return 0;
}
