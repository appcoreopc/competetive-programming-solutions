#include <bits/stdc++.h>

using namespace std;

int N, len;
char num[1000001];
char reversenum[1000001];

bool isPolyndrome()
{
    int start = 0, end = len-1;
    while (start < end) {
        if (num[start++] != num[end--]) {
            return false;
        }
    }

    return true;
}

int solve()
{
    do {
        // Add +1 to number
        ++num[0];
        for (int i = 0, iend = len; i < iend && num[i] > '9'; ++i) {
            if (i+1 == len) ++len;
            num[i] = i == 0 ? '0' : (num[i] - '9') + '0';
            ++num[i+1];
        }
    } while (!isPolyndrome());

    for (int i = len - 1; i >= 0; --i) {
        cout << num[i];
    }
    cout << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d\n", &N);

    char c;

    for (; N > 0 && !feof(stdin); --N) {
        len = 0;
        while ((c = fgetc(stdin)) != '\n' && c != EOF) reversenum[len++] = c;
        for (int i = 0; i < len; ++i) num[i] = reversenum[len-i-1];
        solve();
    }

    return 0;
}