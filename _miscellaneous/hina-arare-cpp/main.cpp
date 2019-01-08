#include <bits/stdc++.h>

#pragma GCC optimize ("O3")

using namespace std;

int readln(char* buf, int max)
{ 
   int len = 0;
   while ((max-- > 0) &&
          ((buf[len] = fgetc(stdin)) != '\n') &&
          (buf[len] != EOF)) ++len;
   buf[len] = 0;
   return len;
}

int N;
char S[401];

void solve()
{
    for (int i = 1; i <= N; ++i) {
        if (S[i] == 'Y') {
            cout << "Four" << endl;
            return;
        }
    }

    cout << "Three" << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d\n", &N);

        readln(S, 400);

    solve();

    return 0;
}
