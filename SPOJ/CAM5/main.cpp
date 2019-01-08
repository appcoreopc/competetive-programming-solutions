#include <bits/stdc++.h>

using namespace std;

int dfs(vector<int>* friends, int i, int N, bool* visited)
{
    if (visited[i]) {
        return 0;
    }

    visited[i] = true;

    for (auto j = friends[i].begin(), jend = friends[i].end(); j < jend; ++j) {
        dfs(friends, *j, N, visited);
    }

    return 1;
}

void solve(int N, int e, vector<int>* friends, bool* visited)
{
    int times = 0;
    for (int i = 0; i < N; ++i) {
        if (dfs(friends, i, N, visited) != 0) {
            ++times;
        }
    }

    cout << times << endl;
}

bool visited[100000];
vector<int> friends[100000];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T, N, e;
    int who, with;
    scanf("%d", &T);

    for (long j = 0; j < T; ++j) {
        scanf("%d", &N);

        for (int i = 0; i < N; ++i) {
            friends[i].clear();
        }

        memset(visited, 0, sizeof(bool) * N);

        scanf("%d", &e);
        for (int i = 0; i < e; ++i) {
            scanf("%d %d", &who, &with);
            friends[who].push_back(with);
        }
        
        for (int i = 0; i < N; ++i) {
            friends[i].push_back(i);
        }

        solve(N, e, friends, visited);
    }
}