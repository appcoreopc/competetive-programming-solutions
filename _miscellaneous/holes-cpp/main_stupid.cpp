#include <bits/stdc++.h>

//#pragma GCC optimize ("O3")

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

const int maxcoord = 10e6;
const int Nmax = 100;
int N;
int x[Nmax+1], y[Nmax+1];
long double R = 10e7;
long long trials[Nmax+1];
long long totalTrials;

void performTrial()
{
    mt19937 gen(rand());
    uniform_real_distribution<long double> dist(-R, R);

    long double _x, _y;

    do {
        _x = dist(gen);
        _y = dist(gen);
    } while (_x*_x + _y*_y > R*R);

    long double d, min_d = numeric_limits<long double>::max();
    int k;
    for (int i = 1; i <= N; ++i) {
        d = sqrt(pow(_x - (long double)x[i], 2.0) + pow(_y - (long double)y[i], 2.0));
        if (min_d > d) {
            min_d = d;
            k = i;
        }
    }

    ++trials[k];
}

int main_bruteforce()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d\n", &N);

    for (int i = 1; i <= N && !feof(stdin); ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }

    totalTrials = 7500000;

    for (long long i = 0; i < totalTrials; ++i) {
        performTrial();
    }

    for (int i = 1; i <= N; ++i) {
        cout << (long double)trials[i] / (long double)totalTrials << endl;
    }

    return 0;
}
