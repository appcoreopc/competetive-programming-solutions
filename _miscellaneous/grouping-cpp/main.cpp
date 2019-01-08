#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize ("O3")

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

void solve(int N)
{
    cout << N / 3 << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &N);
    solve(N);

    return 0;
}
