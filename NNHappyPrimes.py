import sys, math

is_prime = [True] * 10000
def gen_primes(n):
    for i in range(2, int(math.sqrt(n))):
        for j in range(i*i, n, i):
            is_prime[j] = False
gen_primes(10000)

def digit_square_sum(num):
    s = 0
    for c in num:
        s += int(c) ** 2
    return str(s)

for num in map(lambda l: l.strip(), sys.stdin):
    if not is_prime[int(num)]:
        print("COMPOSITE")
        continue
        
    past_results = {}
    happy = False
    while not num in past_results:
        if num == "1":
            happy = True
            break
        past_results[num] = True
        num = digit_square_sum(num)
    if happy:
        print("HAPPY PRIME")
    else:
        print("UNHAPPY PRIME")