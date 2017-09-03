import sys
i = 0
for l in sys.stdin:
    i += 1
    line = sorted(map(int, l.split()[1:]))
    print("Case " + str(i) + ":", min(line), max(line), max(line) - min(line))