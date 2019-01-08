#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/time.h>

#pragma GCC optimize ("O3")

#define REP(i, s, e) for (lli i = s, iend = e; i <= iend; ++i)
#define FOR(i, s, e) for (lli i = s, iend = e; i != iend; ++i)

using namespace std;

typedef long long int lli;

bool files_match(const char* path1, const char* path2, int& diffLineNumber)
{
    diffLineNumber = 0;

    FILE* f1 = fopen(path1, "rt");
    FILE* f2 = fopen(path2, "rt");

    if (!f1 || !f2) {
        fclose(f1);
        fclose(f2);
        return false;
    }

    char buf1[4097], buf2[4097];
    int r1, r2;
    bool fail = false;
    for (;;) {
        ++diffLineNumber;

        if (feof(f1)) {
            if (!feof(f2)) {
                fail = true;
                break;
            } else {
                break;
            }
        } else {
            if (feof(f2)) {
                fail = true;
                break;
            }
        }

        fgets(buf1, 4096, f1);
        fgets(buf2, 4096, f2);

        r1 = strlen(buf1);
        r2 = strlen(buf2);

        if (r1 == r2 && r1 == 0) {
            break;
        }

        if (r1 != r2 || strncmp(buf1, buf2, 4096) != 0) {
            fail = true; 
            break;
        }
    }

    fclose(f1);
    fclose(f2);

    return !fail;
}

long long int sec_diff(timeval clks, timeval clke)
{
    long long int usecE = clke.tv_sec * 1000000 + clke.tv_usec;
    long long int usecS = clks.tv_sec * 1000000 + clks.tv_usec;

    return (usecE - usecS) / 1000000;
}

long long int usec_diff(timeval clks, timeval clke)
{
    long long int usecE = clke.tv_sec * 1000000 + clke.tv_usec;
    long long int usecS = clks.tv_sec * 1000000 + clks.tv_usec;

    return (usecE - usecS) % 1000000;
}

int main()
{
    char ifile[100], ofile[100], efile[100];
    timeval clks, clke;
    bool match;
    int WAs = 0, total = 0, ACs = 0;
    int diffLineNumber;

    FOR(i, 1, 100) {
        snprintf(ifile, 99, "input/i%lld.txt", i);
        snprintf(ofile, 99, "output/o%lld.txt", i);
        snprintf(efile, 99, "expected/e%lld.txt", i);

        if (access(ifile, F_OK) != -1) {
            gettimeofday(&clks, NULL);
            pclose(popen((string("./main.out < ") + ifile + string(" > ") + ofile).c_str(), "r"));
            gettimeofday(&clke, NULL);

            match = files_match(ofile, efile, diffLineNumber);
            if (match) ++ACs; else ++WAs;

            printf(
                "\"main.out < %s > %s\" = %lld.%lld %s",
                ifile,
                ofile,
                sec_diff(clks, clke),
                usec_diff(clks, clke),
                (match ? "AC" : "WA")
            );

            if (!match) {
                if (diffLineNumber > 0) printf(" (diff at line %d)", diffLineNumber);
                else printf(" (unable to e- or o- file)");
            }

            printf("\n");
        }
    }

    total = WAs + ACs;
    if (total > 0) {
        printf("\nTotal = %d | WA = %d, AC = %d\n", total, WAs, ACs);
    }

    return 0;
}
