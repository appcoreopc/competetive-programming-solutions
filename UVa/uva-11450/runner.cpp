#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/time.h>

#pragma GCC optimize ("O3")

#define REP(i, s, e) for (lli i = s, iend = e; i <= iend; ++i)
#define FOR(i, s, e) for (lli i = s, iend = e; i != iend; ++i)

using namespace std;

typedef long long int lli;

bool files_match(const char* path1, const char* path2)
{
    FILE* f1 = fopen(path1, "rt");
    FILE* f2 = fopen(path2, "rt");

    if (!f1 || !f2) return false;

    char buf1[4096], buf2[4096];
    int r1, r2;
    bool fail = false;
    for (;;) {
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

        r1 = fread(buf1, sizeof(char), 4096, f1);
        r2 = fread(buf2, sizeof(char), 4096, f2);

        if (r1 != r2 || strncmp(buf1, buf2, 4096) != 0) {
            fail = true; 
            break;
        }
    }

    fclose(f1);
    fclose(f2);

    return !fail;
}

int main()
{
    char ifile[100], ofile[100], efile[100];
    timeval clks, clke;
    bool match;
    int WAs = 0, total = 0, ACs = 0;
    FOR(i, 1, 100) {
        snprintf(ifile, 99, "input/i%lld.txt", i);
        snprintf(ofile, 99, "output/o%lld.txt", i);
        snprintf(efile, 99, "expected/e%lld.txt", i);

        if (access(ifile, F_OK) != -1) {
            gettimeofday(&clks, NULL);
            pclose(popen((string("./main.out < ") + ifile + string(" > ") + ofile).c_str(), "r"));
            gettimeofday(&clke, NULL);

            match = files_match(ofile, efile);
            if (match) ++ACs; else ++WAs;

            printf(
                "\"main.out < %s > %s\" = %ld.%ld %s\n",
                ifile,
                ofile,
                clke.tv_sec - clks.tv_sec,
                clke.tv_usec - clks.tv_usec,
                (match ? "AC" : "WA")
            );
        }
    }

    total = WAs + ACs;
    if (total > 0) {
        printf("\nTotal = %d | WA = %d, AC = %d\n", total, WAs, ACs);
    }

    return 0;
}
