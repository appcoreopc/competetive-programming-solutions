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
int M, C, K;
vec<int> g[21];
bool can_reach[201][21];

void solve()
{
    memset(can_reach, false, sizeof(can_reach));
    FOR(k, 0, g[1].size()) if (M - g[1][k] >= 0) can_reach[M - g[1][k]][1] = 1;

    REP(c, 2, C) {
        FOR(m, 0, M) {
            if (!can_reach[m][c-1]) continue;

            FOR(i, 0, g[c].size()) {
                if (m - g[c][i] >= 0) can_reach[m - g[c][i]][c] = 1;
            }
        }
    }

    int res;
    for (res = 0; res <= M && !can_reach[res][C]; res++);

    if (res == M + 1) {
        printf("no solution\n");
    } else {
        printf("%d\n", M - res);
    }
}

int main()
{
    int garnement;
    scanf("%d", &N);
    REP(n, 1, N) {
        scanf("%d %d", &M, &C);

        REP(c, 1, C) {
            scanf("%d", &K);
            g[c].clear();
            FOR(k, 0, K) {
                scanf("%d", &garnement);
                g[c].push_back(garnement);
            }
        }

        solve();
    }

    return 0;
}
