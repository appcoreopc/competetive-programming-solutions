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

int N;

char origBoard[9][9];
char board[9][9];

void copyBoard(char dest[][9], char from[][9])
{
    FOR(i,0,9) FOR(j,0,9) dest[i][j] = from[i][j];
}

void loadBoard()
{
    char buf[10];
    FOR(i,0,9) {
        scanf("%s", buf);
        FOR(j,0,9) {
            board[i][j] = buf[j];
        }
    }
}

void print(char board[][9])
{
    FOR(i,0,9) {
        FOR(j,0,9){
            if (j % 3 == 0) putc('|', stdout);
            putc(board[i][j], stdout);
        }
        printf("|\n");
        if ((i+1)%3 == 0) {
            FOR(j,0,13)putc('_',stdout);
            printf("\n");
        }
    }
    printf("\n");
}

void emptyBoard(char board[][9])
{
    FOR(i,0,9) FOR(j,0,9) board[i][j] = '.';
}

pair<int, int> closestSquare(int i, int j)
{
    pair<int, int> mapping[] = {
        {1, 1},
        {4, 1},
        {7, 1},
        {1, 4},
        {4, 4},
        {7, 4},
        {1, 7},
        {4, 7},
        {7, 7}
    };

    int closest = 0, distanceSquare = (i-1)*(i-1) + (j-1)*(j-1);
    int tempDistanceSquare;
    FOR(x,1,9) {
        tempDistanceSquare = (i-mapping[x].first)*(i-mapping[x].first) + (j-mapping[x].second)*(j-mapping[x].second);
        if (tempDistanceSquare < distanceSquare) {
            distanceSquare = tempDistanceSquare;
            closest = x;
        }
    }

    return mapping[closest];
}

void maskSquare(int i, int j, char board[][9]) 
{
    pair<int,int> closest = closestSquare(i, j);

    REP(i,closest.first-1,closest.first+1)
        REP(j,closest.second-1,closest.second+1)
            board[i][j] = 'x';
}

bool isSolved(char board[][9])
{
    FOR(i,0,9) FOR(j,0,9) if(board[i][j] == '.') return false;
    return true;
}

int countUnchecked(char board[][9])
{
    int count = 0;
    FOR(i,0,9) FOR(j,0,9) if(board[i][j] == '.') ++count;
    return count;
}

int countPlaced(char num, char board[][9])
{
    int count = 0;
    FOR(i,0,9) FOR(j,0,9) if(board[i][j] == num) ++count;
    return count;
}

bool makeObviousMove(char num, char board[][9], char maskBoard[][9])
{
    pair<int, int> mapping[] = {
        {1, 1},
        {4, 1},
        {7, 1},
        {1, 4},
        {4, 4},
        {7, 4},
        {1, 7},
        {4, 7},
        {7, 7}
    };

    FOR(x,0,9) {
        pair<int,int> closest = mapping[x];
        pair<int,int> emptyPoint = make_pair(-1,-1);
        bool failed = false;

        REP(i,closest.first-1,closest.first+1) {
            REP(j,closest.second-1,closest.second+1) {
                if (maskBoard[i][j] != '.') continue;
                if (emptyPoint.first == -1) {
                    emptyPoint.first = i; emptyPoint.second = j;
                } else {
                    failed = true;
                    break;
                }
            }

            if (failed) break;
        }

        if (!failed && emptyPoint.first != -1) {
            board[emptyPoint.first][emptyPoint.second] = num;
            return true;
        }
    }

    return false;
}

void recalculateMaskBoard(char num, char board[][9], char maskBoard[][9])
{
    emptyBoard(maskBoard);
    
    FOR(i,0,9) FOR(j,0,9) {
        if (board[i][j] == num) {
            FOR(k,0,9) maskBoard[k][j] = 'x';
            FOR(k,0,9) maskBoard[i][k] = 'x';
            maskSquare(i, j, maskBoard);
        } else if (board[i][j] == '.') {
            // do nothing
        } else {
            maskBoard[i][j] = 'x';
        }
    }
}

bool makeRandomMove(char num, char board[][9], int nth)
{
    char maskBoard[9][9];
    recalculateMaskBoard(num, board, maskBoard);

    FOR (i,0,9) {
        FOR (j,0,9) {
            if (maskBoard[i][j] == '.') {
                if (nth > 0) {
                    --nth; continue;
                }

                board[i][j] = num;
                return true;
            }
        }
    }

    return false;
}

bool solve(char board[][9]);

bool playRandom(char board[][9])
{
    char maskBoard[9][9];
    int minimumPossibilities = 81, minPosTemp;
    char minPosNum = -1;

    REP(x,1+'0',9+'0') {
        recalculateMaskBoard(x, board, maskBoard);

        minPosTemp = countUnchecked(maskBoard);
        if (minPosTemp == 0) continue;
        if (minimumPossibilities < minPosTemp) continue;
        minimumPossibilities = minPosTemp;
        minPosNum = x;
    }

    if (minPosNum == -1) return false;

    char boardCopy[9][9];
    FOR(i,0,minimumPossibilities) {
        copyBoard(boardCopy, board);
        makeRandomMove(minPosNum, boardCopy, i);

        if (solve(boardCopy)) {
            copyBoard(board, boardCopy);
            return true;
        }
    }

    return false;
}

bool playNormal(char board[][9])
{
    char maskBoard[9][9];
    REP(x,1+'0',9+'0') {
        recalculateMaskBoard(x, board, maskBoard);

        //printf("Mask for number %c:\n", x); print(maskBoard);
        if (makeObviousMove(x, board, maskBoard)) return true;
    }

    return false;
}

bool solve(char board[][9])
{
    print(board);
    
    while (playNormal(board)) print(board);

    if (isSolved(board)) {
        return true;
    }

    return playRandom(board);
}

int main()
{
    loadBoard();
    copyBoard(origBoard, board);
    if (solve(board)) {
        printf("Solved!\n");
        print(board);
    } else {
        printf("Impossible to solve!\n");
    }

    return 0;
}
