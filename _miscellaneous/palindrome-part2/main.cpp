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

string s;
vector<char> ispalin;
int max_length;

bool palin(const string& x, int i, int iend)
{
    int oi = i, oiend = iend;
    while (i < iend && ispalin[i * max_length + iend] == -1) {
        if (x[i++] != x[iend--]) { ispalin[oi * max_length + oiend] = 0; break; }
    }

    if (ispalin[oi* max_length + oiend] == -1) {
        if (ispalin[i* max_length + iend] == -1) ispalin[oi* max_length + oiend] = 1;
        else ispalin[oi* max_length + oiend] = ispalin[i* max_length + iend];
    }

    return ispalin[oi* max_length + oiend];
}

void solve()
{
    if (s.size() == 0) {
        printf("0");
        return;
    }

    max_length = s.size();
    ispalin.resize(max_length * max_length, -1);

    vector<int> dp;
    dp.reserve(s.size()+1);
    dp.push_back(0);

    for (int i = 1, iend = s.size(); i <= iend; ++i) {
        dp.push_back(dp[i-1]+1);

        for (int j = i; j >= 2; --j) {
            if (dp[i] > dp[i-j]+1 && palin(s, i-j, i-1)) dp[i] = dp[i-j]+1;
        }
    }
    
    printf("%d", dp[s.size()]-1);
}

int main()
{
    char buf;
    while ((buf = getc(stdin)) != EOF && buf != '\n') s+=buf;
    solve();

    return 0;
}
