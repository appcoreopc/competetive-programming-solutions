#include <bits/stdc++.h>
#include <unistd.h>

// #pragma GCC optimize ("O3")

#define REP(i, s, e) for (lli i = s, i##end = e; i <= i##end; ++i)
#define REPR(i, s, e) for (lli i = s, i##end = e; i >= i##end; --i)
#define FOR(i, s, e) for (lli i = s, i##end = e; i != i##end; ++i)
#define FORR(i, s, e) for (lli i = s, i##end = e; i != i##end; --i)

using namespace std;

typedef long long int lli;
typedef long double ld;
typedef string str;
template<typename T> using vec = vector<T>;
typedef pair<lli, lli> pi;

const int maxD = 21;
int T, M, N;
bool maze[maxD][maxD];
bool visited[maxD][maxD];

void pushpt(deque<pi>& points, int m, int n) {
    if (m < 0 || n < 0 || m >= M || n >= N) return;
    if (!visited[m][n] && maze[m][n]) {
        points.push_back(make_pair(m,n));
        visited[m][n] = true;
    }
}

bool solve()
{
    deque<pi> exits;

    FOR (m,0,M) {
        if (1 == maze[m][0]) pushpt(exits, m, 0);        
        if (1 == maze[m][N-1]) pushpt(exits, m, N-1);        
    }

    FOR (n,0,N) {
        if (1 == maze[0][n]) pushpt(exits, 0, n);
        if (1 == maze[M-1][n]) pushpt(exits, M-1, n);
    }

    if (exits.size() != 2) {
        return false;
    }

    deque<pi> points;
    points.push_back(exits[0]);

    visited[exits[1].first][exits[1].second] = 0;

    while (!points.empty()) {
        pi lastP = points.back();

        if (lastP == exits[1]) {
            return true;
        }

        points.pop_back();

        pushpt(points, lastP.first - 1, lastP.second);
        pushpt(points, lastP.first + 1, lastP.second);
        pushpt(points, lastP.first, lastP.second - 1);
        pushpt(points, lastP.first, lastP.second + 1);
    }

    return false;
}

int main()
{
    char c;
    scanf("%d\n", &T);

    FOR(t, 0, T) {
        scanf("%d %d\n", &M, &N);

        memset(visited, 0, sizeof(visited));

        FOR(m, 0, M) {
            FOR(n, 0, N) {
                scanf("%c", &c);
                maze[m][n] = (c == '.');
            }

            scanf("%c", &c); // new line symbol
        }

        if (solve()) printf("valid\n");
        else printf("invalid\n");
    }

    return 0;
}
