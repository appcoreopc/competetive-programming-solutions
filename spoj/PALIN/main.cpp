#include <bits/stdc++.h>

using namespace std;

int N, len;
char num[1000001];
char reversenum[1000001];

bool isPalindrome(char* num)
{
    int start = 0, end = len-1;
    while (start < end) {
        if (num[start++] != num[end--]) {
            return false;
        }
    }

    return true;
}

int addOne(char* num, int len)
{
    ++num[0];
    for (int i = 0, iend = len; i < iend && num[i] > '9'; ++i) {
        num[i] = i == 0 ? '0' : (num[i] - '9') - 1 + '0';
        if (i+1 == len) {
            ++len;
            num[i+1] = '1'; 
        } else {
            ++num[i+1];
        }
    }

    return len;
}

int solve()
{
    len = addOne(num, len); // To ignore palindromes in input
    if (!isPalindrome(num)) { // Check for 999...99 case immediately, so we guarantee that len will not change
        for (int i = 0, iend = len/2; i <= iend; ++i) {
            for (;num[i] != num[len-i-1];) addOne(num + i, len - i);
        }
    }

    for (int i = len - 1; i >= 0; --i) {
        cout << num[i];
    }
    cout << endl;
}

int main()
{
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
