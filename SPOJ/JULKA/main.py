import sys

sys.stdin = open('input.txt', 'r')

x = 0
for line in sys.stdin:
    if (x == 0):
        total = int(line)
        x = 1
        continue
    else:
        klaudiaMore = int(line)
        x = 0
    
    natalia = (total - klaudiaMore) / 2
    if (((total - klaudiaMore) % 2) != 0):
        natalia = natalia + 1

    klaudia = total - natalia
    sys.stdout.write(str(klaudia)+"\n")
    sys.stdout.write(str(natalia)+"\n")