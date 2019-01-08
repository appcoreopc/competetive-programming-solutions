#include <iostream>
#include <stdlib.h>

using namespace std;

int comp(const void* x, const void* y)
{
    return *((int*)x) < *((int*)y);
}

void solve(int* manHotness, int* womanHotness, int N)
{
    qsort(manHotness+1, N, sizeof(int), comp);
    qsort(womanHotness+1, N, sizeof(int), comp);

    int sum = 0;
    for (int i = 1; i <= N; ++i) { 
        sum += manHotness[i] * womanHotness[i];
    }
    cout << sum << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    int T;
    int manHotness[1001], womanHotness[1001];
    
    scanf("%d", &T);

    for (int i = 0; i < T; ++i) {
        scanf("%d", &N);

        for (int i = 1; i <= N; ++i) {
            scanf("%d", &manHotness[i]);
        }
        
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &womanHotness[i]);
        }
        
        solve(manHotness, womanHotness, N);
    }

    return 0;
}