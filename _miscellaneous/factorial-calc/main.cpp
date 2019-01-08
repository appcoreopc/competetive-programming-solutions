#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

namespace apa
{
    template <typename T>
    class ComparisonOperators
    {
        friend bool operator==(T const& lhs, T const& rhs)
        {
            return lhs.compare(rhs) == 0;
        }

        friend bool operator!=(T const& lhs, T const& rhs)
        {
            return lhs.compare(rhs) != 0;
        }

        friend bool operator<(T const& lhs, T const& rhs)
        {
            return lhs.compare(rhs) < 0;
        }

        friend bool operator>(T const& lhs, T const& rhs)
        {
            return rhs.compare(lhs) < 0;
        }

        friend bool operator<=(T const& lhs, T const& rhs)
        {
            bool result = lhs.compare(rhs) <= 0;
            return result;
        }

        friend bool operator>=(T const& lhs, T const& rhs)
        {
            return rhs.compare(lhs) <= 0;
        }
    };

    class lint : ComparisonOperators<lint>
    {
    public:
        explicit lint(std::string number);

        lint();

        lint(long long number);

        lint(int number);

        lint(double number);

        lint(vector<int> nums, bool is_neg);

        lint(const lint &obj);

        int get_length() const;

        bool is_negative_number() const;

        lint& operator*=(const lint& number2);

        explicit operator int();

        lint operator+() const;

        lint operator-() const;

        int operator[](size_t index) const;

        lint& operator=(const lint& other);

        bool cmp(lint const& rhs) const;

        int compare(lint const& rhs) const;

        bool is_zero() const;

        std::string to_string();

    private:
        bool is_negative;
        vector<int> numbers;

        lint abs(lint number) const;

        vector<int> reverse_numbers(vector<int> const& numbers) const;

        void make_equal_length(const lint& b, vector<int> & number1, vector<int> & number2) const;

        void string_to_vector(std::string const& number);

        void integer_to_vector(long long a);
    };

    lint abs(lint number);

    lint pow(lint a, int n);

    std::ostream& operator<<(std::ostream& os, const lint& obj);

    std::istream& operator>>(std::istream& is, lint& obj);

    lint operator*(const lint& lhs, const lint& rhs);
    
    lint::lint(std::string number)
    {
        string_to_vector(number);
    }

    lint::lint()
    {
        integer_to_vector(0);
    }

    lint::lint(long long number)
    {
        integer_to_vector(number);
    }

    lint::lint(int number)
    {
        integer_to_vector(static_cast<long long>(number));
    }

    lint::lint(double number)
    {
        std::string str = std::to_string(std::trunc(number));
        std::string result = str.substr(0, str.size() - 7);
        string_to_vector(result);
    }

    lint::lint(vector<int> nums, bool is_neg)
    {
        numbers = nums;
        is_negative = is_neg;
    }

    lint::lint(const lint &obj) {
        is_negative = obj.is_negative_number();

        for (int t : obj.numbers)
        {
            numbers.push_back(t);
        }
    }

    int lint::get_length() const
    {
        return numbers.size();
    }

    bool lint::is_negative_number() const
    {
        return is_negative;
    }

    lint& lint::operator*=(const lint& number2)
    {
        vector<int> a = reverse_numbers(numbers);
        vector<int> b = reverse_numbers(number2.numbers);

        vector<int> c(a.size() + b.size(), 0);

        for (size_t i = 0; i < a.size(); ++i)
        {
            int carry = 0;

            for (unsigned int j = 0; j < b.size() || carry; ++j)
            {
                long long cur = c[i + j] + a[i] * 1ll * (j < b.size() ? b[j] : 0) + carry;

                c[i + j] = int(cur % 10);
                carry = int(cur / 10);
            }
        }

        while (c.size() > 1 && c.back() == 0)
        {
            c.pop_back();
        }

        vector<int> result = reverse_numbers(c);

        numbers = result;

        if (is_negative_number() && !number2.is_negative_number())
        {
            is_negative = true;
        }
        else if (!is_negative_number() && number2.is_negative_number())
        {
            is_negative = true;
        }
        else
        {
            is_negative = false;
        }

        return *this;
    }

    lint::operator int()
    {
        return std::stoi((*this).to_string());
    }

    lint lint::operator+() const
    {
        lint temp(*this);
        return temp;
    }

    lint lint::operator-() const
    {
        lint temp(*this);

        if (is_negative_number())
        {
            temp.is_negative = false;
        }
        else
        {
            temp.is_negative = true;
        }
        
        return temp;
    }

    int lint::operator[](size_t index) const
    {
        return numbers[index];
    }

    lint& lint::operator=(const lint& other)
    {
        if (this != &other)
        {
            numbers = other.numbers;
            is_negative = other.is_negative_number();
        }
        return *this;
    }

    bool lint::cmp(lint const& rhs) const
    {
        if (is_negative_number() && !rhs.is_negative_number())
        {
            return true;
        }

        if (!is_negative_number() && rhs.is_negative_number())
        {
            return false;
        }

        if (get_length() < rhs.get_length())
        {
            return true;
        }

        if (get_length() > rhs.get_length())
        {
            return false;
        }

        for (int i = 0; i < get_length(); ++i)
        {
            if (numbers[i] < rhs[i])
            {
                if (is_negative_number())
                {
                    return false;
                }
                return true;
            }
            else if (numbers[i] > rhs[i])
            {
                if (is_negative_number())
                {
                    return true;
                }
                return false;
            }
        }

        return false;
    }

    int lint::compare(lint const& rhs) const
    {
        if ((*this).cmp(rhs))
        {
            return -1;
        }
        else if (rhs.cmp(*this))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    lint lint::abs(lint number) const
    {
        number.is_negative = false;
        return number;
    }

    bool lint::is_zero() const
    {
        if (numbers.size() == 1 && numbers[0] == 0)
        {
            return true;
        }

        return false;
    }

    std::string int_to_string(int i)
    {
        std::stringstream ss;
        std::string s;
        ss << i;
        s = ss.str();

        return s;
    }

    std::string lint::to_string()
    {
        std::string result = "";

        if (is_negative_number() && !is_zero())
        {
            result += "-";
        }

        for (int i = 0; i < get_length(); ++i)
        {
            int a = (*this)[i];
            result += int_to_string(a);
        }

        return result;
    }

    vector<int> lint::reverse_numbers(vector<int> const& numbers) const
    {
        vector<int> reverse_result;

        for (int i = numbers.size() - 1; i >= 0; --i)
        {
            reverse_result.push_back(numbers[i]);
        }

        return reverse_result;
    }

    void lint::make_equal_length(lint const& b, vector<int>& number1, vector<int>& number2) const
    {
        int diff_length = get_length() - b.get_length();

        if (diff_length > 0)
        {
            number1 = (*this).numbers;

            for (int i = 0; i < diff_length; ++i)
            {
                number2.push_back(0);
            }

            for (int i = 0; i < b.get_length(); ++i)
            {
                number2.push_back(b[i]);
            }
        }
        else if (diff_length < 0)
        {
            for (int i = 0; i < b.get_length(); ++i)
            {
                number2.push_back(b[i]);
            }

            for (int i = 0; i < (diff_length * (-1)); ++i)
            {
                number1.push_back(0);
            }

            for (int i = 0; i < get_length(); ++i)
            {
                number1.push_back((*this)[i]);
            }
        }
        else
        {
            for (int i = 0; i < b.get_length(); ++i)
            {
                number1.push_back((*this)[i]);
                number2.push_back(b[i]);
            }
        }
    }

    void lint::string_to_vector(std::string const& number)
    {
        unsigned int from = 0;

        if (number[0] == '-')
        {
            is_negative = true;
            from = 1;
        }
        else
        {
            is_negative = false;
        }

        for (unsigned int i = from; i < number.length(); ++i)
        {
            int ia = number[i] - '0';
            numbers.push_back(ia);
        }
    }

    void lint::integer_to_vector(long long a)
    {
        if (a < 0)
        {
            is_negative = true;
            a = (-1) * a;
        }
        else
        {
            is_negative = false;
        }

        if (a == 0)
        {
            numbers.push_back(0);
        }

        vector<int> temp;

        while (a)
        {
            int x = a % 10;
            a /= 10;
            temp.push_back(x);
        }

        for (int i = temp.size() - 1; i >= 0; --i)
        {
            numbers.push_back(temp[i]);
        }
    }

    lint abs(lint number)
    {
        lint n(number);
        lint zero(0);

        bool is_less = n.cmp(zero);

        if (is_less)
        {
            n *= lint(-1);
        }
        return n;
    }

    lint pow(lint a, int n) {
        lint res(1);

        while (n)
        {
            if (n & 1)
            {
                res *= a;
            }

            a *= a;
            n >>= 1;
        }

        return res;
    }

    std::ostream& operator<<(std::ostream& os, const lint& obj)
    {
        if (obj.is_negative_number())
        {
            os << "-";
        }

        for (int i = 0; i < obj.get_length(); ++i)
        {
            os << obj[i];
        }

        return os;
    }

    std::istream& operator>>(std::istream& is, lint& obj)
    {
        bool is_lead_zeros = true;
        bool is_negative = false;
        vector<int> numbers;

        while (is.good())
        {
            char c = static_cast<char>(is.get());
            int ic = c - '0';

            if (c == '\n')
            {
                break;
            }

            if (c == EOF)
            {
                break;
            }

            if (c == '\0')
            {
                break;
            }

            if (is.good())
            {
                if (c == '-')
                {
                    is_negative = true;
                }
                else if (c == '+')
                {
                    is_negative = false;
                }
                else if (ic == 0 && is_lead_zeros)
                {

                }
                else
                {
                    numbers.push_back(ic);
                    is_lead_zeros = false;
                }
            }
        }

        lint temp(numbers, is_negative);
        obj = temp;

        return is;
    }

    lint operator*(const lint& lhs, const lint& rhs)
    {
        lint temp(lhs);

        return temp *= rhs;
    }
}

using namespace apa;

lint factorial(long N)
{
    lint result = 1;

    for (int i = 2; i <= N; ++i) {
        result *= i;
    }

    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    long T;
    long N;
    scanf("%d", &T);

    for (long i = 0; i < T; ++i) {
        scanf("%ld", &N);
        cout << factorial(N) << endl;
    }
}