import sys

for people in map(int, sys.stdin):
    if people == 0:
        break
        
    ans = 1
    for i in range(people):
        ans *= (366 - i) / 366
         
    print("{:.4f}%".format(100 - 100 * ans))