#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstring>

typedef long long int num_type;
using namespace std;

void simpleSieve(num_type limit, num_type m, vector<num_type> &prime)
{
    // Create a boolean array "mark[0..n-1]" and initialize
    // all entries of it as true. A value in mark[p] will
    // finally be false if 'p' is Not a prime, else true.
    bool mark[limit+1];
    memset(mark, true, sizeof(mark));
 
    for (num_type p=2; p*p<limit; p++)
    {
        // If p is not changed, then it is a prime
        if (mark[p] == true)
        {
            // Update all multiples of p
            for (num_type i=p*2; i<limit; i+=p)
                mark[i] = false;
        }
    }
 
    // Prnum_type all prime numbers and store them in prime
    for (num_type p=2; p<limit; p++)
    {
        if (mark[p] == true)
        {
            prime.push_back(p);

            if (p >= m) {
                cout << p << endl;
            }
        }
    }
}
 
// Prints all prime numbers smaller than 'n'
void segmentedSieve(num_type n, num_type m)
{
    // Compute all primes smaller than or equal
    // to square root of n using simple sieve
    vector<num_type> prime;
    num_type limit = floor(sqrt(n))+1; 
    simpleSieve(limit, m, prime); 
 
    // Divide the range [0..n-1] in different segments
    // We have chosen segment size as sqrt(n).
    num_type low = limit;
    num_type high = 2*limit;
 
    // While all segments of range [0..n-1] are not processed,
    // process one segment at a time
    while (low < n)
    {
        if (high >= n) 
           high = n;
         
        // To mark primes in current range. A value in mark[i]
        // will finally be false if 'i-low' is Not a prime,
        // else true.
        bool mark[limit+1];
        memset(mark, true, sizeof(mark));
 
        // Use the found primes by simpleSieve() to find
        // primes in current range
        for (num_type i = 0; i < prime.size(); i++)
        {
            // Find the minimum number in [low..high] that is
            // a multiple of prime[i] (divisible by prime[i])
            // For example, if low is 31 and prime[i] is 3,
            // we start with 33.
            num_type loLim = floor(low/prime[i]) * prime[i];
            if (loLim < low)
                loLim += prime[i];
 
            /* Mark multiples of prime[i] in [low..high]:
                We are marking j - low for j, i.e. each number
                in range [low, high] is mapped to [0, high-low]
                so if range is [50, 100] marking 50 corresponds
                to marking 0, marking 51 corresponds to 1 and
                so on. In this way we need to allocate space only
                for range */
            for (num_type j=loLim; j<high; j+=prime[i])
                mark[j-low] = false;
        }
 
        // Numbers which are not marked as false are prime
        for (num_type i = low; i<high; i++)
            if (mark[i - low] == true)
                if (i >= m) cout << i << endl;
 
        // Update low and high for next segment
        low = low + limit;
        high = high + limit;
    }
}

bool isprime2(num_type n) {
    for(num_type i = 2; i <= sqrt(n); ++i)
    {
      if(n % i == 0)
      {
          return false;
      }
    }

    return true;
}

bool isprime(num_type x) {
    switch (x) {
        case 2:
        case 3:
            return true;
    }

    if (x % 2 == 0) {
        return false;
    } else if (x % 3 == 0) {
        return false;
    }

    num_type i = 5;
    num_type w = 2;

    while (i*i <= x) {
        if (x % i == 0) { 
            return false;
        }
        
        i += w;
        w = 6 - w;
    }

    return true;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
	scanf("%d", &N);

    num_type m, n; 

    for (int i = 0; i < N; ++i) {
    	scanf("%lld %lld", &m, &n);

        for (num_type x = m; x <= n; ++x) {
            if (isprime2(x)) {
                cout << x << endl;
            }
        }

        cout << endl;
    }

    return 0;
}