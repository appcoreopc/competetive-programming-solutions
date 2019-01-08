#include <iostream>

using namespace std;
typedef long long num_type;

num_type Z(num_type N)
{
    num_type numOf5 = 0;
    num_type fiveInPow = 5;

    while (fiveInPow <= N) {
        numOf5 += N / fiveInPow;
        fiveInPow = fiveInPow * 5; 
    }

    return numOf5;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    long T;
    num_type N;
    scanf("%d", &T);

    for (long i = 0; i < T; ++i) {
        scanf("%ld", &N);
        cout << Z(N) << endl;
    }
}