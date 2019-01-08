#include <bits/stdc++.h>

using namespace std;

bool isPalindrome(const string& str)
{
    for (int i = 0, endoff = str.length() - 1, iend = str.length() / 2; i < iend; ++i) {
        if (str[i] != str[endoff - i]) {
            return false;
        }
    }

    return true;
}

void solve_step(const string &input, vector<vector<string>>& partitions)
{
    string substrLeft;
    string substrRight;
    for (int i = 0, iend = input.length(); i < iend; ++i) {
        substrLeft = input.substr(0, i + 1);
        substrRight = input.substr(i + 1);
        if (isPalindrome(substrLeft)) {
            vector<vector<string> > step_result;

            if (substrRight.length() == 0) {
                vector<string> partition;
                partition.push_back(substrLeft);
                partitions.push_back(partition);
                continue;
            }

            solve_step(substrRight, step_result);

            for (auto resIter = step_result.begin(), resIterEnd = step_result.end(); resIter != resIterEnd; ++resIter) {
                vector<string> partition;
                partition.push_back(substrLeft);
                partition.insert(partition.end(), resIter->begin(), resIter->end());
                partitions.push_back(partition);
            }
        }
    }
}

void solve(const string& input)
{
    vector<vector<string>> result;
    result.reserve(input.length() * (input.length() - 1) / 2);
    solve_step(input, result);
    
    for_each(result.begin(), result.end(), [](vector<string>& partition) {
        for_each(partition.begin(), partition.end(), [](string& str) {
            cout << str << ' ';
        });

        cout << endl;
    });
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string input;
    cin >> input;

    solve(input);

    return 0;
}