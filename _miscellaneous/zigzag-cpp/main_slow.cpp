#include <bits/stdc++.h>

using namespace std;

const long long minus_infinity = numeric_limits<long long>::min();

struct bag_t {
    int weight;
    int value;
};

template <typename T>
void dump(const vector<T>& x, ostream& out, char* separator = ", ")
{
    copy(x.begin(), x.end(), ostream_iterator<bag_t>(out, separator));
}

template <typename T, typename L>
void insert_in_asc_order(vector<T>& bags, T value, L compFunc)
{
    bool inserted = false;

    for (auto j = bags.begin(), jend = bags.end(); j != jend; ++j) {
        if (compFunc(*j, value) > 0) {
            bags.insert(j, value);
            inserted = true;
            break;
        }
    }
    
    if (!inserted) {
        bags.push_back(value);
    }
}

ostream &operator<<(ostream &os, const bag_t &x) { 
    return os << "(" << x.weight << "," << x.value << ")";
}

long long solve(int K, vector<bag_t>& bags)
{
    long long* sol = new long long[K+1];
    vector<vector<short> > path(K+1, vector<short>());

    memset(sol, minus_infinity, sizeof(long long)*(K+1));
    sol[0] = 0;

    int bestSolutionJ, bestSolutionT;

    for (int i = 1; i <= K; ++i) {
        sol[i] = sol[i - 1];
        bestSolutionJ = -1;
        bestSolutionT = i-1;

        for (int t = 0; t < i; ++t) {
            for (int j = 0, jend = bags.size(); j != jend; ++j) {
                if (bags[j].weight > i - t) {
                    break;
                }

                if (sol[t] + bags[j].value > sol[i]) {
                    sol[i] = sol[t] + bags[j].value;
                    bestSolutionJ = j;
                    bestSolutionT = t;
                }
            }
        }

        copy(path[bestSolutionT].begin(), path[bestSolutionT].end(), back_inserter(path[i]));
        if (bestSolutionJ != -1) {
            insert_in_asc_order(path[i], (short)bestSolutionJ, [](short L, short R) {
                return L - R;
            });
        }
    }

    long long result = sol[K];
    delete[] sol;

    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, K, M;
    scanf("%d", &N);
    vector<bag_t> bags;
    int A, B;

    for (; N > 0 && !feof(stdin); --N) {
        scanf("%d %d\n", &K, &M);
        
        bags.clear();
        bags.reserve(M);
        for (int i = 0; i < M; ++i) {
            scanf("%d %d\n", &A, &B);
            insert_in_asc_order(bags, { A, B }, [](const bag_t& L, const bag_t& R) {
                return L.weight - R.weight;
            });
        }
        
        cout << "Hey stupid robber, you can get " << solve(K, bags) << "." << endl;
    }

    return 0;
}