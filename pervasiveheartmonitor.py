import sys

for line in sys.stdin:
    total = 0
    numbers = 0
    name = ""
    for v in line.split(" "):
        try:
            num = float(v)
            total += num
            numbers += 1
        except ValueError:
            name += v + " "
    print("%.6f %s" % ((total / numbers), name[:-1]))