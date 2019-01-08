#include <bits/stdc++.h>

//#pragma GCC optimize ("O3")
#pragma GCC optimize ("O0")

using namespace std;

template<typename T>
int orderDesc(const void* p1, const void* p2)
{
    const T& a = *static_cast<const T*>(p1);
    const T& b = *static_cast<const T*>(p2);
    return (a < b);
}

template<typename T>
int orderAsc(const void* p1, const void* p2)
{
    const T& a = *static_cast<const T*>(p1);
    const T& b = *static_cast<const T*>(p2);
    return (a > b);
}

char S[15];

int calcpos(char c) {
    switch (c) {
        case 'M':
            return 0;
        case 'A':
            return 1;
        case 'R':
            return 2;
        case 'C':
            return 3;
        case 'H':
            return 4;
    }

    return -1;
}

int main()
{
    long long counts[5] = {0,0,0,0,0};
    int pos;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N && !feof(stdin); ++i) {
        scanf("%s", S);

        pos = calcpos(S[0]);
        if (pos != -1) ++counts[pos];
    }

    long long res = 0;
    for (int i = 0; i <= 2; ++i) {
        for (int j = i + 1; j <= 3; ++j) {
            for (int x = j + 1; x <= 4; ++x) {
                res += counts[i] * counts[j] * counts[x];
            }
        }
    }

    printf("%lld", res);

    return 0;
}
