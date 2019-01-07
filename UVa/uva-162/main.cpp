#include <bits/stdc++.h>
#include <unistd.h>

// #pragma GCC optimize ("O3")

#define REP(i, s, e) for (lli i = s, iend = e; i <= iend; ++i)
#define REPR(i, s, e) for (lli i = s, iend = e; i >= iend; --i)
#define FOR(i, s, e) for (lli i = s, iend = e; i != iend; ++i)
#define FORR(i, s, e) for (lli i = s, iend = e; i != iend; --i)

using namespace std;

typedef long long int lli;
typedef long double ld;
typedef string str;
template<typename T> using vec = vector<T>;

char deck[52][2];

deque<string> decks[2];
deque<string> heap;
int turn, winner;

int drawCards(int player, int cardsToDraw)
{
    // Returns 0 if J, Q, K or A were not drawn.
    // Returns -1 if impossible to draw card.
    // Returns 1..4 if J, Q, K or A accordingly were drawn.

    deque<string>* deckToDraw = &decks[player % 2];
    int drawNext = 0;
    
    FOR(i, 0, cardsToDraw) {
        if (deckToDraw->empty()) return -1;

        switch (deckToDraw->back()[1]) {
            case 'A': drawNext = 4; break;
            case 'Q': drawNext = 2; break;
            case 'J': drawNext = 1; break;
            case 'K': drawNext = 3; break;
        }

        heap.push_back(deckToDraw->back());
        deckToDraw->pop_back();

        if (drawNext != 0) {
            break;
        }
    }

    return drawNext;
}

void solve()
{
    decks[0].clear();
    decks[1].clear();
    heap.clear();

    FOR(i,0,52){
        decks[i % 2].push_back(string(deck[i], 2));
    }

    turn = 2;
    int cardsToDraw = 1;
    int whoExposedLastFaceCard = -1;

    for(;;) {
        cardsToDraw = drawCards(turn, cardsToDraw);

        if (cardsToDraw == -1) {
            winner = (turn == 1 ? 2 : 1);
            return;
        } else if (cardsToDraw == 0) {
            if (whoExposedLastFaceCard != -1) {
                decks[whoExposedLastFaceCard % 2].insert(
                    decks[whoExposedLastFaceCard % 2].begin(),
                    heap.rbegin(),
                    heap.rend()
                );
                heap.clear();
                whoExposedLastFaceCard = -1;
            }

            cardsToDraw = 1;
        } else {
            whoExposedLastFaceCard = turn;
        }

        turn = (turn == 1 ? 2 : 1);
    }
}

int main()
{
    char buf[3] = {};
    int cardN = 0;

    for (;;) {
        scanf("%s", buf);
        if (strncmp(buf, "#", 1) == 0) break;
        strncpy(deck[cardN], buf, 2);
        
        if (++cardN == 52) {
            cardN = 0;
            solve();
            printf("%d%3d\n", winner, decks[winner % 2].size());
        }
    }

    return 0;
}

