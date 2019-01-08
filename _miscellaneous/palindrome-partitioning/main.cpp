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

void addPalin(vector<vector<string> >& result, vector<string> subresult, const string& s, int start, int length)
{
    if (length == 0) {
        result.push_back(subresult);
        printf("  ");
        FOR(i,0,subresult.size()) printf("\"%s\" ", subresult[i].c_str());
        printf("\n");
        return;
    }

    for (int i = length; i > 0; --i) {
        if (palin(s, start, start+i-1)) {
            vector<string> subsubresult(subresult);
            subsubresult.push_back(s.substr(start, i));
            addPalin(result, subsubresult, s, start+i, length - i);
        }
    }
}

void solve()
{
    if (s.size() == 0) {
        printf("[\n]\n");
        return;
    }
    printf("[\n");

    max_length = s.size();
    ispalin.clear();
    ispalin.resize(max_length * max_length, -1);

    vector<vector<string>> result;
    addPalin(result, {}, s, 0, s.size());

    printf("]\n");
}

int main()
{
    char buf;
    while ((buf = getc(stdin)) != EOF && buf != '\n') s+=buf;
    solve();

    return 0;
}
