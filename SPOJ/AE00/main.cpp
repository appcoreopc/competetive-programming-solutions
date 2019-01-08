#include <iostream>
#include <cmath>

using namespace std;

int solve_nested(int N)
{
    int Mmax = sqrt(N);
    int resCount = 0;

    for (int i = 1; i <= Mmax; ++i) {
        resCount += (N - i*i) / i + 1;
    }

    return resCount;
}

void solve(int N)
{
    int x = solve_nested(N);

    cout << x << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    
    for (; !feof(stdin); ) {
        scanf("%d", &N);
        solve(N);
    }

    return 0;
}