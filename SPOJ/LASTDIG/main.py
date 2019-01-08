import sys

N = int(sys.stdin.readline())
for i in range(0, N):
    a, b = sys.stdin.readline().split()
    a, b = int(a), int(b)
    res = pow(a, b, 10)
    sys.stdout.write(str(res) + "\n")
