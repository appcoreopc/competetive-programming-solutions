#include <iostream>

using namespace std;

void solve(const int* candiesInEachPacket, int N)
{
    int sum = 0;
    for (int i = 1; i <= N; ++i) {
        sum += candiesInEachPacket[i];
    }

    int avg = sum / N;
    int avgMod = sum % N;

    if (avgMod != 0) {
        cout << -1 << endl;
        return;
    }

    int addCandiesN = 0;
    int removeCandiesN = 0;

    for (int i = 1; i <= N; ++i) {
        if (avg > candiesInEachPacket[i]) {
            addCandiesN += avg - candiesInEachPacket[i];
        }
    }

    cout << addCandiesN << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    int candiesInEachPacket[100001];

    for (; !feof(stdin) ;) {
        scanf("%d", &N);

        if (N == -1) {
            break;
        }

        for (int i = 1; i <= N; ++i) {
            scanf("%d", &candiesInEachPacket[i]);
        }

        solve(candiesInEachPacket, N);
    }

    return 0;
}