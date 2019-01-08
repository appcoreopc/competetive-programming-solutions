#include <iostream>

using namespace std;

bool first_line_point(int x, int y)
{
    return (y - x) == 0;
}

bool second_line_point(int x, int y)
{
    return (y - x + 2) == 0;
}

void solve(int x, int y)
{
    if (second_line_point(x, y) || first_line_point(x, y)) {
        if ((x & 1) == 0) {
            cout << x + y << endl;
        } else {
            cout << x + y - 1 << endl;
        }
        return;
    }

    cout << "No Number" << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    int x, y;
    scanf("%d", &T);

    for (long i = 0; i < T; ++i) {
        scanf("%d %d", &x, &y);
        solve(x, y);
    }
}