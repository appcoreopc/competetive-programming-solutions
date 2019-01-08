#include <bits/stdc++.h>

using namespace std;

bool isPalindrome(const char* str, int left, int right)
{
    while (left < right) {
        if (str[left++] != str[right--]) {
            return false;
        }
    }

    return true;
}

int solve(const string& input)
{
    bool** isPal = new bool*[input.length()];
    for (int i = 0, iend = input.length(); i != iend; ++i) {
        isPal[i] = new bool[input.length()];
        memset(isPal[i], 0, sizeof(bool) * input.length());
    }

    int* min_cuts = new int[input.length()];
    min_cuts[0] = 0;

    for (int i = 1, iend = input.length(); i < iend; ++i) {
        min_cuts[i] = i;
        
        for (int j = 0; j <= i; ++j) {
            if (input[i] == input[j] && (i - j < 2 || isPal[j+1][i-1])) {
                isPal[j][i] = 1;

                if (j == 0) min_cuts[i] = 0;
                else min_cuts[i] = min(min_cuts[i], min_cuts[j - 1] + 1);
            }
        }
    }

    return min_cuts[input.length() - 1];
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string input;
    cin >> input;

    cout << solve(input) << endl;

    return 0;
}