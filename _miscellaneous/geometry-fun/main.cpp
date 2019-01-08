#include <bits/stdc++.h>
#include <unistd.h>

// #pragma GCC optimize ("O3")

#define REP(i, s, e) for (lli i = s, iend = e; i <= iend; ++i)
#define REPR(i, s, e) for (lli i = s, iend = e; i >= iend; --i)
#define FOR(i, s, e) for (lli i = s, iend = e; i != iend; ++i)
#define FORR(i, s, e) for (lli i = s, iend = e; i != iend; --i)

using namespace std;

typedef long long int lli;
typedef double ld;
typedef string str;
template<typename T> using vec = vector<T>;

struct point_t { ld x, y; };

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int turnKind(const point_t& p, const point_t& q, const point_t& r)
{
    // -1 - counter-clockwise
    //  1 - clockwise
    //  0 - on same line

    double zCoordOfNormal = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
    return sgn(zCoordOfNormal);
}

int positionRelativeToLine(const point_t& toCheck, const point_t& lineA, const point_t& lineB)
{
    // -1 - to the left of the line (toCheck is found if to traverse counter clockwise)
    //  1 - to the right of the line (toCheck is found if to traverse clockwise)
    //  0 - on same line

    if (lineB.x - lineA.x == 0) {
        return sgn(toCheck.x);
    }

    return sgn(lineB.x - lineA.x) * sgn((lineB.y - lineA.y) * (toCheck.x - lineA.x) + (lineA.y - toCheck.y) * (lineB.x - lineA.x));
}

int main()
{
    int N;
    point_t a,b,c;

    scanf("%d\n", &N);
    FOR(i,0,N) {
        scanf("%lf %lf %lf %lf %lf %lf", &c.x, &c.y, &a.x, &a.y, &b.x, &b.y);
        int pos = positionRelativeToLine({c.x, c.y}, {a.x, a.y}, {b.x, b.y});
        printf("%d\n", pos);
    }

    return 0;
}
