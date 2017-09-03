import sys

while True:
    try:
        _ = input().split()[1:]
    except:
        break
    
    codomain = input().split()[1:]
    mappings = int(input())

    maps = {}
    ys = {}
    for cod in codomain:
        ys[cod] = 0
        
    not_a_function = False
    for m in range(mappings):
        words = input().split()
        x = words[0]
        y = words[2]
        if x in maps and maps[x] != y:
            not_a_function = True
        maps[x] = y
        ys[y] += 1
        
    if not_a_function:
        print("not a function")
        continue
    
    def is_injective():
        for y in ys.keys():
            if ys[y] > 1:
                return False
        return True

    def is_surjective():
        for y in ys.keys():
            if ys[y] < 1:
                return False
        return True
            
    inj = is_injective()
    sur = is_surjective()

    if inj and sur:
        print("bijective")
    elif inj:
        print("injective")
    elif sur:
        print("surjective")
    else:
        print("neither injective nor surjective")