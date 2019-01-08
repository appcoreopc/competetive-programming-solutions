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

int N, V;
int coins[100];
unsigned int dp[1000];

const unsigned int MAX_VAL = numeric_limits<unsigned int>::max() / 2;

unsigned int dpcoins_bottomup(int V)
{
    int delta;

    REP(v, 1, V) {
        FOR(c, 0, N) {
            delta = v - coins[c];
            if (delta < 0) continue;
            dp[v] = min(dp[v], 1+dp[delta]);
        }
    }

    return dp[V];
}

unsigned int dpcoins_topdown(int V)
{
    if (dp[V] < MAX_VAL) return dp[V];

    int delta;

    FOR(c, 0, N) {
        delta = V - coins[c];
        if (delta < 0) continue;
        dp[V] = min(dp[V], 1 + dpcoins_topdown(delta));
    }

    return dp[V];
}

int main()
{
    fill(dp+1, dp+1000, MAX_VAL);

    scanf("%d %d\n", &V, &N);
    FOR(i, 0, N) scanf("%d", &coins[i]);

    cout << dpcoins_topdown(V) << endl;

    return 0;
}
