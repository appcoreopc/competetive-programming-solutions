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
typedef vector<char> str;
template<typename T> using vec = vector<T>;

int N;
str number[2];
char op;

void printNumber(str number, int strWidth, char op = 0, int offsetRight = 0)
{
    int widthDiff = strWidth - number.size();
    if (op != 0) widthDiff--;
    FOR (i, offsetRight, widthDiff) putc(' ', stdout);
    if (op != 0) putc(op, stdout);
    REPR (i, number.size()-1, 0) {
        if (number[i] == '-') putc('-', stdout);
        else putc(number[i]+'0', stdout);
    }
}

str sum(str number1, str number2, bool quiet = false)
{
    int carry = 0, temp;
    str result;

    for (int i = 0, iend = max(number1.size(), number2.size()); i != iend; ++i) {
        temp = carry;
        if (number1.size() > i) temp += number1[i];
        if (number2.size() > i) temp += number2[i];

        if (temp >= 10) { carry = 1; temp -= 10; }
        else { carry = 0; }

        result.push_back(temp);
    }

    if (carry == 1) result.push_back(1);

    if (!quiet) {
    int strWidth = max(result.size(), max(number1.size(), number2.size()+1));
    printNumber(number1, strWidth);
    printf("\n");
    printNumber(number2, strWidth, '+');
    printf("\n");
    FOR (i, max(result.size(), number2.size()+1), strWidth) putc(' ', stdout);
    FOR (i, 0, max(result.size(), number2.size()+1)) putc('-', stdout);
    printf("\n");
    printNumber(result, strWidth);
    printf("\n");
    }

    return result;
}

bool firstSmaller(const str& num1, const str& num2)
{
    if (num1.size() > num2.size()) {
        return false;
    }

    if (num1.size() < num2.size()) {
        return true;
    }

    REPR(i, num1.size()-1, 0) {
        if (num1[i] < num2[i]) return true;
        else if (num1[i] > num2[i]) return false;
    }

    //equal
    return false;
}

void sub(str number1_orig, str number2_orig)
{
    int carry = 0, temp;
    str result, number1, number2;

    int swapped = 0;
    if (firstSmaller(number1_orig, number2_orig)) {
        swapped = 1;
        number1 = number2_orig;
        number2 = number1_orig;
    } else {
        number1 = number1_orig;
        number2 = number2_orig;
    }

    for (int i = 0, iend = number1.size(); i != iend; ++i) {
        temp = carry;

        if (number1.size() > i && number2.size() > i) {
            if (number1[i]+carry < number2[i]) {
                carry = -1;
                temp += 10;
            } else {
                carry = 0;
            }

            temp += number1[i] - number2[i];
        } else {
            if (carry == -1 && number1[i] == 0) {
                temp = 9;
            } else {
                temp += number1[i];
                carry = 0;
            }
        }

        result.push_back(temp);
    }

    REPR (i, result.size()-1, 0) {
        if (result[i] == 0) result.pop_back();
        else break;
    }

    if (swapped) result.push_back('-');

    int strWidth = max(result.size(), max(number1_orig.size(), number2_orig.size()+1));
    printNumber(number1_orig, strWidth);
    printf("\n");
    printNumber(number2_orig, strWidth, '-');
    printf("\n");
    FOR (i, max(result.size(), number2_orig.size()+1), strWidth) putc(' ', stdout);
    FOR (i, 0, max(result.size(), number2_orig.size()+1)) putc('-', stdout);
    printf("\n");
    printNumber(result, strWidth);
    printf("\n");
}

str mul_solve(const str& number1, const str& number2, bool quiet, int longwidth = -1, int shortwidth = -1)
{
    int temp;
    str result_curline;
    str result;

    for (int i = 0, iend = number2.size(); i != iend; ++i) {
        result_curline.clear();
        temp = 0;

        for (int j = 0, jend = number1.size(); j != jend; ++j) {
            temp += number1[j]*number2[i];
            result_curline.push_back(temp % 10);
            temp = temp / 10;
        }

        while (temp > 0) {
            result_curline.push_back(temp % 10);
            temp = temp / 10;
        }

        REPR (j, result_curline.size()-1, 1) {
            if (result_curline[j] == 0) result_curline.pop_back();
            else break;
        }

        if (!quiet) {
            if (i == 0) {
                shortwidth = max(shortwidth, (int)result_curline.size());
                FOR (i, 0, longwidth - shortwidth) putc(' ', stdout);
                FOR (i, longwidth - shortwidth, longwidth) putc('-', stdout);
                printf("\n");
            }

            printNumber(result_curline, longwidth, 0, i);
            printf("\n");
        }

        FOR(j,0,i) result_curline.insert(result_curline.begin(), 0);
        result = sum(result, result_curline, true);
    }

    return result;
}

void mul(str number1, str number2)
{
    str result = mul_solve(number1, number2, true);

    int longwidth = max(result.size(), number2.size()+1);
    int shortwidth = number2.size()+1; 

    printNumber(number1, longwidth);
    printf("\n");
    printNumber(number2, longwidth, '*');
    printf("\n");

    if (number2.size() > 1) {
        mul_solve(number1, number2, false, longwidth, shortwidth);
    }

    FOR (i, 0, longwidth-result.size()) putc(' ', stdout);
    FOR (i, 0, result.size()) putc('-', stdout);
    printf("\n");
    printNumber(result, longwidth);
    printf("\n");
}

void solve()
{
    reverse(number[0].begin(), number[0].end());
    reverse(number[1].begin(), number[1].end());

    switch (op) {
        case '+':
            sum(number[0], number[1]);
            break;
        case '-':
            sub(number[0], number[1]);
            break;
        case '*':
            mul(number[0], number[1]);
            break;
    }

    printf("\n");
}

int main()
{
    char buf;
    int state;
    scanf("%d\n", &N);

    number[0].reserve(500);
    number[1].reserve(500);

    FOR(i,0,N) {
        state = 0;
        number[0].clear();
        number[1].clear();
        while ((buf = getc(stdin)) != EOF && buf != '\n') {
            switch (buf) {
                case '+':
                case '-':
                case '*':
                    op = buf;
                    state = 1;
                break;
                default:
                    number[state].push_back(buf-'0');
                break;
            }
        }
        solve();
    }

    return 0;
}
