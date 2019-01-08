import sys

sys.stdin = open('input.txt', 'r')

def eratosthenes_sieve(n, basis):
    if (len(basis) < 2):
        return basis

    for p in basis:
        if (p > n): 
            return basis[:basis.index(p)]

        i = 2
        while (i * p <= n):
            if i*p in basis:
                basis.remove(i * p)
            i = i + 1     
    
    return basis

def extend_basis(UpperBoundNumber, nMax, basis, basic_basis, wheel_prime_numbers):
    i = 1
    while (i * nMax + 1 <= UpperBoundNumber):
        nextLine = range(i * nMax + 1, i * nMax + nMax + 1)
        filteredOut = []

        for j in range(1, len(nextLine) + 1):
            if j in wheel_prime_numbers:
                filteredOut.append(i * nMax + j)

        for j in range(2, len(nextLine) + 1):
            if not j in basic_basis and not (i * nMax + j) in filteredOut:
                filteredOut.append(i * nMax + j)

        nextLine = [ x for x in nextLine if not x in filteredOut ] 
        basis = basis + nextLine
        i = i + 1

    return basis

def calc_nMax(wheel_prime_numbers):
    nMax = 1
    for i in wheel_prime_numbers:
        nMax = nMax * i
    return nMax

def optimal_max_wheel_number(wheel_prime_numbers, n):
    wheel_prime_numbers_product = 1
    for i in range(1, len(wheel_prime_numbers) + 1):
        wheel_prime_numbers_product = wheel_prime_numbers_product * wheel_prime_numbers[i - 1]
        if (wheel_prime_numbers_product > n):
            return max(1, min(5, i - 1))

    return len(wheel_prime_numbers)

wheel_prime_numbers_known = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]

T = int(sys.stdin.readline())
for t in range(0, T):
    m, n = sys.stdin.readline().split()
    m = int(m)
    n = int(n)

    wheel_prime_numbers = wheel_prime_numbers_known[:optimal_max_wheel_number(wheel_prime_numbers_known, n)]

    nMax = calc_nMax(wheel_prime_numbers)

    basis = range(2, nMax + 1)
    basis = eratosthenes_sieve(nMax, basis)

    basic_basis = basis[:]
    basis = extend_basis(n, nMax, basis, basic_basis, wheel_prime_numbers)

    basis = eratosthenes_sieve(n, basis)

    for x in basis:
        if (x < m):
            continue
        sys.stdout.write(str(x) + "\n")

    sys.stdout.write("\n")
