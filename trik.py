l = [1, 0, 0]
for c in input():
    if c == 'A':
        l[0], l[1] = l[1], l[0]
    elif c == 'B':
        l[1], l[2] = l[2], l[1]
    else:
        l[0], l[2] = l[2], l[0]
print(l.index(1) + 1)