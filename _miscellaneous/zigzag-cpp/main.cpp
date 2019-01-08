#include <bits/stdc++.h>

using namespace std;

bool sameSign(int x, int y)
{
    bool xPlus = x > 0;
    bool yPlus = y > 0;

    return (xPlus && yPlus) || (!xPlus && !yPlus);
}

int solve(int N, int* seq)
{
    // Convert to seq of diffs
    for (int i = 0; i < N; ++i) {
        seq[i] = seq[i+1]-seq[i];
    }
    --N;

    int* sol = new int[N];
    bool** p = new bool*[N];
    for (int i = 0; i < N; ++i) {
        p[i] = new bool[N];
        memset(p[i], 0, sizeof(bool)*N);
    }
    sol[0] = 0;
    sol[1] = 1;

    for (int i = 2; i < N; ++i) {
        sol[i] = sol[i-1];

        for (int j = 0; j < i; ++j) {
            if (sameSign(seq[j], seq[i])) {
                if ((i - j < 2 || p[j+1][i-1] == 1)) {
                    p[j][i] = 1;
                    if (j == 0) sol[i] = i;
                    else sol[i] = max(sol[i], sol[j-1] + 2);
                }
            }
        }
    }

    return sol[N-1];
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int sequence[50];
    int N = 0;

    for (; !feof(stdin); ) {
        scanf("%d\n", &sequence[N++]);
    }

    cout << solve(N, sequence) << endl;

    return 0;
}