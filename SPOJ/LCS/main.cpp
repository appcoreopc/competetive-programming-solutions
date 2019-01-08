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

const int MAX_SIZE = 100;
string str1, str2;
int v[MAX_SIZE][MAX_SIZE];
const int INF = MAX_SIZE * 5;
const int MODIFICATION_COST = 0;
const int MISMATCH_COST = -INF;
const int MATCH_PRIZE = 1;

int score(char c1, char c2)
{
    if (c1 == c2) return MATCH_PRIZE;
    else return MISMATCH_COST;
}

void traceback_LCS(int n, stack<pair<int, int> >& result)
{
    if (n == 0) {
        return;
    }

    int maxLtZero = -INF;
    int maxLtZeroM;
    FOR(i,0,MAX_SIZE) {
        if (v[n][i] > 0) {
            if (v[n][i] > maxLtZero) {
                maxLtZeroM = i;
                maxLtZero = v[n][i];
            }
        }
    }

    if (maxLtZero == -INF) {
        if (n == 0) {
            return; // No common subsequence
        }

        traceback_LCS(n-1, result);
        return;
    }

    result.push(make_pair(n, maxLtZeroM));
    traceback_LCS(n-1, result);
}

void solve_LCS()
{
    v[0][0] = 0;
    REP(j,1,str2.length()) {
        v[0][j] = -j;
    }
    REP(i,1,str1.length()) {
        v[i][0] = -i;
    }

    REP(i,1,str1.length()) {
        REP(j,1,str2.length()) {
            v[i][j] = max(max(v[i-1][j-1] + score(str1[i-1], str2[j-1]), v[i][j-1] + MODIFICATION_COST), v[i-1][j] + MODIFICATION_COST);
        }
    }

    stack<pair<int, int> > result;
    traceback_LCS(str1.length(), result);
    while (!result.empty()) {
        const pair<int,int>& x = result.top(); result.pop();
        if (x.first == x.second) cout << "(" << x.first << ";" << x.second << "), ";
    }
    cout << endl;
}

void traceback_needleman_wunsch(int n, int m, stack<pair<int, int> >& result)
{
    if (n == 0 && m == 0) {
        return;
    }

    result.push(make_pair(n, m));

    pair<int, int> x;
    int maxx = -INF;

    if (n > 0 && m > 0) {
        if (v[n-1][m-1] > maxx) {
            maxx = v[n-1][m-1];
            x = make_pair(n-1, m-1);
        }
    }

    if (n > 0) {
        if (v[n-1][m] > maxx) {
            maxx = v[n-1][m];
            x = make_pair(n-1, m);
        }
    }

    if (m > 0) {
        if (v[n][m-1] > maxx) {
            maxx = v[n][m-1];
            x = make_pair(n, m-1);
        }
    }

    if (x.first == n && x.second == m-1) {
        str1.insert(n, "_");
    }

    if (x.first == n-1 && x.second == m) {
        str2.insert(m, "_");
    }

    traceback_needleman_wunsch(x.first, x.second, result);
}

void solve_needleman_wunsch()
{
    v[0][0] = 0;
    REP(j,1,str2.length()) {
        v[0][j] = -j;
    }
    REP(i,1,str1.length()) {
        v[i][0] = -i;
    }

    REP(i,1,str1.length()) {
        REP(j,1,str2.length()) {
            v[i][j] = max(max(v[i-1][j-1] + score(str1[i-1], str2[j-1]), v[i][j-1] + MODIFICATION_COST), v[i-1][j] + MODIFICATION_COST);
        }
    }

    stack<pair<int, int> > result;
    traceback_needleman_wunsch(str1.length(), str2.length(), result);
    while (!result.empty()) {
        const pair<int,int>& x = result.top(); result.pop();
        cout << "(" << x.first << ";" << x.second << "), ";
    }
    cout << endl;
}

int main()
{
    char bufs[255];
    scanf("%s\n", bufs);
    str1 = bufs;
    scanf("%s\n", bufs);
    str2 = bufs;

    solve_LCS();

    printf("%s\n", str1.c_str());
    printf("%s\n", str2.c_str());

    return 0;
}
