import sys

sys.stdin = open('input.txt', 'r')

N = int(sys.stdin.readline())

def reverse(numStr):
    return numStr[::-1].strip('0')

for line in sys.stdin:
    (num1, num2) = line.split()
    num1 = int(reverse(num1))
    num2 = int(reverse(num2))
    numresult = reverse(str(num1 + num2))
    sys.stdout.write(numresult + "\n")