#include <iostream>
#include <deque>

using namespace std;

bool isOperator(char op)
{
    switch (op) {
        case '+':
        case '-':
        case '/':
        case '*':
        case '^':
            return true;
    }

    return false;
}

int get_operator_priority(char op) 
{
    switch (op) {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '^':
            return 4;
    }

    return -1;
}

bool is_right_associative_operator(char op)
{
    switch (op) {
        case '+':
            return false;
        case '-':
            return false;
        case '*':
            return false;
        case '/':
            return false;
        case '^':
            return true;
    }

    return false; 
}

bool operator_has_higher_priority(char op1, char op2)
{
    int op1_priority = get_operator_priority(op1), op2_priority = get_operator_priority(op2);
    return op1 > op2;
}

void push_operator(char op, deque<char>& operators)
{
    for (auto opIter = operators.begin(), opIterEnd = operators.end(); opIter != opIterEnd; ++opIter) {
        if (operator_has_higher_priority(op, *opIter)) {
            continue;
        } else {
            operators.insert(opIter, op);
            return;
        }
    }

    operators.push_back(op);
}

string reverse_polish_notation(const char * const expression, int length)
{
    if (length < 1) {
        return "";
    }

    deque<string> operands;
    deque<char> operators;

    enum read_mode { SEARCH_SUB_EXPR, TRAVERSE_FORWARD } cur_mode = TRAVERSE_FORWARD;
    int nBracket = 0;
    int openBracketStart = 0;

    for (int i = 0; i < length; ++i) {
        if (expression[i] == '(') {
            // Found opening brace

            if (nBracket == 0) { 
                openBracketStart = i + 1;
                cur_mode = SEARCH_SUB_EXPR;
            }

            ++nBracket;
        } else if (expression[i] == ')') {
            // Found closing brace

            --nBracket;
            if (nBracket == 0) {
                string subexpr = reverse_polish_notation(expression + openBracketStart, i - openBracketStart);
                operands.push_back(subexpr);
                cur_mode = TRAVERSE_FORWARD;
            }
        } else if (cur_mode == TRAVERSE_FORWARD) {
            if (isOperator(expression[i])) {
                // Found operator
                push_operator(expression[i], operators);
            } else {
                // Found operand
                operands.push_back(string(1, expression[i]));
            }
        }
    }

    string result = "";

    for_each(operands.begin(), operands.end(), [&](const string& op) {
        result += op;
    });

    for_each(operators.begin(), operators.end(), [&](const char& op) {
        result += op;
    });

    return result;
}

string shunting_yard_algo(const char * const expression, int length)
{
    string result="";
    deque<char> operators;

    for (int i = 0; i < length; ++i) {
        if (expression[i] == '(') {
            // Found opening brace
            operators.push_front('(');
        } else if (expression[i] == ')') {
            // Found closing brace
            while (!operators.empty() && operators.front() != '(')
            {
                result += operators.front();
                operators.pop_front();
            }

            if (!operators.empty()) operators.pop_front();
        } else if (isOperator(expression[i])) {
            // Found operator
            while (!operators.empty() && operators.front() != '(' && 
                operator_has_higher_priority(operators.front(), expression[i]) && 
                is_right_associative_operator(expression[i]))
            {
                result += operators.front();
                operators.pop_front();
            }

            operators.push_front(expression[i]);
        } else {
            // Found operand
            result += expression[i];
        }
    }

    for_each(operators.begin(), operators.end(), [&](const char& op) {
        result += op;
    });

    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    char expression[401];
    int length;

    scanf("%d\n", &T);

    for (long i = 0; i < T;) {
        if (!fgets(expression, sizeof(expression), stdin)) {
            continue;
        }

        length = strlen(expression) - 1;
        expression[length] = '\0'; // Removing traling \n
        cout << shunting_yard_algo(expression, length) << endl;
        ++i;
    }
}