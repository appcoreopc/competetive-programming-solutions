#include <bits/stdc++.h>

//#pragma GCC optimize ("O3")

using namespace std;

#define REP(i, a, b) for (int i = int(a); i <= int(b); i++)

vector<int> pset(1000); // 1000 is just an initial number, it is user-adjustable.
void initSet(int _size) { pset.resize(_size); REP (i, 0, _size - 1) pset[i] = i; }
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
void unionSet(int i, int j) { pset[findSet(i)] = findSet(j); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
int numberOfSets() { int count = 0; REP (i, 0, pset.size() - 1) if (pset[i] == i) ++count; return count; }

int N;
char lnode = 0;
char edge[2];

int main()
{
    scanf("%d\n", &N);

    for (; N-- && !feof(stdin);) {
        while (scanf("%c%c\n", &edge[0], &edge[1]) > 0) {
            if (edge[1] == '\n') {
                if (lnode != 0) printf("%d\n", numberOfSets());
                lnode = edge[0];
                pset.clear();
                initSet(lnode - 'A' + 1);
                continue;
            }

            unionSet(edge[0]-'A',edge[1]-'A');
        }

        printf("%d\n", numberOfSets());
    }

    fprintf (stderr, "%.2f\n", (double)clock () / CLOCKS_PER_SEC);

    return 0;
}
