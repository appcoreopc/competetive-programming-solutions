#include <bits/stdc++.h>

using namespace std;

long long solve(int K, int M, int* bagsw, int* bagsv)
{
    int sol[51][1001]={};

    int bestSolutionJ, bestSolutionT;

    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= K; ++j) {
            sol[i][j] = sol[i-1][j];
            if (j >= bagsw[i]) {
                sol[i][j] = max(sol[i][j], max(sol[i-1][j-bagsw[i]] + bagsv[i], sol[i][j-bagsw[i]] + bagsv[i]));
            }
        }
    }

    return sol[M][K];
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, K, M;
    scanf("%d", &N);
    int bagsw[51]={};
    int bagsv[51]={};
    int A, B;

    for (; N > 0 && !feof(stdin); --N) {
        scanf("%d %d\n", &K, &M);
        
        for (int i = 1; i <= M; ++i) {
            scanf("%d %d\n", &A, &B);
            bagsw[i] = A;
            bagsv[i] = B;
        }
        
        cout << "Hey stupid robber, you can get " << solve(K, M, bagsw, bagsv) << "." << endl;
    }

    return 0;
}