#include <bits/stdc++.h>

using namespace std;

int main()
{
    typedef long long val_t;
    const val_t val_min = 0;
    const val_t val_max = 100;
    const int N = 100;

    random_device rd;
    mt19937 reng(rd());
    uniform_int_distribution<val_t> randd(val_min, val_max);

    freopen("inputc.txt", "w", stdout);

    printf("%d\n", N);

    for (int i = 0; i < N; ++i) {
        val_t x = randd(reng);
        val_t y = randd(reng);

        printf("%d %d\n", x, y);
    }
}