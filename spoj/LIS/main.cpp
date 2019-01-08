#include <bits/stdc++.h>
#include <unistd.h>

// #pragma GCC optimize ("O3")
#define REP(i, s, e) for (lli i = s, iend = e; i <= iend; ++i)
#define REPR(i, s, e) for (lli i = s, iend = e; i >= iend; --i)
#define FOR(i, s, e) for (lli i = s, iend = e; i != iend; ++i)
#define FORR(i, s, e) for (lli i = s, iend = e; i != iend; --i)

using namespace std;

typedef long long int lli;
typedef long double ld;
typedef string str;
template<typename T> using vec = vector<T>;

int N;
int vals[100];
int subv[100], maxsubv[100];

int LIS(int x)
{
    int ans = 1, ansnew;
    
    FOR (i, x+1, N) {
        if (vals[x] < vals[i]) {
            ansnew = 1 + LIS(i);
            
            if (ansnew > ans) {
                subv[x] = i;
                ans = ansnew;
            }
        }
    }

    return ans;
}

int main()
{
    scanf("%d\n", &N);
    FOR(i, 0, N) {
        scanf("%d", &vals[i]);
    }

    int len;
    int maxlen = -1, maxsubvi = -1;

    FOR(i,0,N) {
        memset(subv, -1, sizeof subv);

        len = LIS(i);
        if (maxlen < len) {
            maxlen = len; maxsubvi = i;
            memcpy(maxsubv, subv, sizeof subv);
        }
    }

    while (maxsubvi != -1) {
        printf("%d ", vals[maxsubvi]);
        maxsubvi = maxsubv[maxsubvi];
    }

    return 0;
}
