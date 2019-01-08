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

int LIS(int x, deque<int>& v)
{
    int ans = 1;
    deque<int> subv, maxsubv;
    
    FOR (i, x+1, N) {
        if (vals[x] < vals[i]) {
            subv.clear();
            ans = max(ans, 1 + LIS(i, subv));
            if (subv.size() > maxsubv.size()) {
                maxsubv = subv;
            }
        }
    }

    v.push_front(vals[x]);
    v.insert(v.end(), maxsubv.begin(), maxsubv.end());

    return ans;
}

int LISr(int x)
{
    int ans = 1;
    REPR (i, x-1, 0) {
        if (vals[x] > vals[i]) {
            ans = max(ans, 1 + LISr(i));
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

    deque<int> v;
    deque<int> vmax;
    FOR(i,0,N) {
        v.clear();
        LIS(i, v);
        if (v.size() > vmax.size()) {
            vmax = v;
        }
    }

    for_each(vmax.begin(), vmax.end(), [](int val) { printf("%d ", val); });

    return 0;
}
