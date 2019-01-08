#include <iostream>
#include <stdlib.h>

using namespace std;

void solve(char* message, int columns)
{
    int msg_size = strlen(message);
    int rows = msg_size / columns;
    int x;

    for (int j = columns; j < msg_size; j += columns * 2) {
        for (int i = 0, iend = columns / 2; i < iend; ++i) {
            x = message[j + i];
            message[j + i] = message[j + columns - i - 1];
            message[j + columns - i - 1] = x;
        }
    }

    string result = "";
    result.reserve(msg_size);
    
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            result += message[j * columns + i];
        }
    }

    cout << result << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int columns;
    char message[202];
    
    for (; !feof(stdin); ) {
        scanf("%d\n", &columns);

        if (columns == 0) {
            break;
        }

        fgets(message, sizeof(message), stdin);
        message[strlen(message) - 1] = '\0'; // Remove traling \n
        solve(message, columns);
    }

    return 0;
}