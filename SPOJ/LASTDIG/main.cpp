#include <bits/stdc++.h>

using namespace std;

int solve(int a, long long b)
{
    static const int periods[10][5] = {
        {0,0,0,0,0},
        {1,0,0,0,0},
        {2,4,8,6,0},
        {3,9,7,1,0},
        {4,6,0,0,0},
        {5,0,0,0,0},
        {6,0,0,0,0},
        {7,9,3,1,0},
        {8,4,2,6,0},
        {9,1,0,0,0}
    };

    if (a != 0 && b == 0) return 1;
    a = a % 10;

    const int* period = periods[a];
    int periodLength = 0;
    for (;period[periodLength];++periodLength);

    if (periodLength == 0) return 0;
    int modulo = (b - 1) % periodLength;
    return period[modulo];
}

int main()
{
    int T, a;
    long long b;
    scanf("%d\n", &T);

    for (int i = 0; i < T; ++i) {
        scanf("%d %lld", &a, &b);
        cout << solve(a,b) << endl;
    }
    return 0;
}
