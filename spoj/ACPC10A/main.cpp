#include <iostream>

using namespace std;

void solve(int x, int y, int z)
{
    if (z - y == y - x) {
        cout << "AP " << z + (z - y) << endl;
    } else {
        cout << "GP " << z * (z / y) << endl; 
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int x, y, z;

    for (; !feof(stdin) ;) {
        scanf("%d %d %d", &x, &y, &z);

        if (x == 0 && y == 0 && z == 0) {
            break;
        }

        solve(x, y, z);
    }

    return 0;
}