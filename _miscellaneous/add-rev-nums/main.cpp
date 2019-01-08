#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    cin >> N;

    int num1, num2;
    
    string num1Str, num2Str;

    int numrResult;
    string resultNotTrimmedNotReversed, resultTrimmed;

    for (int i = 0; i < N; ++i) {
        cin >> num1Str >> num2Str;

        string rnum1, rnum2;

        copy(num1Str.rbegin(), num1Str.rend(), back_inserter(rnum1));
        copy(num2Str.rbegin(), num2Str.rend(), back_inserter(rnum2));

        stringstream ss1(rnum1);
        stringstream ss2(rnum2);
        ss1 >> num1;
        ss2 >> num2;

        numrResult = num1 + num2;

        stringstream resultStream;
        resultStream << numrResult;
        resultStream >> resultNotTrimmedNotReversed;

        string resultNotTrimmed;
        copy(resultNotTrimmedNotReversed.rbegin(), resultNotTrimmedNotReversed.rend(), back_inserter(resultNotTrimmed));
        
        for (int firstNotNull = 0, firstNotNullEnd = resultNotTrimmed.length(); firstNotNull < firstNotNullEnd; ++firstNotNull) {
            if (resultNotTrimmed[firstNotNull] != '0') {
                resultTrimmed = resultNotTrimmed.substr(firstNotNull);
                break;
            }
        } 

        cout << resultTrimmed << endl;
    }

    return 0;
}