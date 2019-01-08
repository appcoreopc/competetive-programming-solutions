import sys
import math

sys.stdin = open('input.txt', 'r')
out = open('output.txt', 'w')

N = int(sys.stdin.readline())

for line in sys.stdin:
    out.write(str(math.factorial(int(line))) + "\n")