#include <bits/stdc++.h>
    
using namespace std;
    
int n,ans,a,k;
    
int sg(int n,int k)
{
    if (n<k) return 0;
    if (n%k==0) return n/k;
    int t=n/k+1,p=(n-(n/k)*k+t-1)/t;
    return sg(n-t*p,k);
}
    
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d",&n);
    for (;n--;)
    {
        scanf("%d%d",&a,&k);
        ans^=sg(a,k);
    }
    if (ans) printf("Takahashi\n");else printf("Aoki\n");
    return 0;
}