#include <iostream>

using namespace std;

void solve(int N)
{
    unsigned long long sum = 0;

    for (int i = 1; i <= N; ++i) {
        sum += i*i;
    }

    cout << sum << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;

    for (;;) {
        scanf("%d", &N);

        if (N == 0) {
            break;
        }

        solve(N);
    }
}