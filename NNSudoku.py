def transpose(matrix):
    return list(zip(*matrix))

def get_correct_sum(n):
    return (n * (n + 1)) // 2
    
while True:
    try:
        dimension = int(input())
    except EOFError:
        break
    
    matrix = []
    for _ in range(dimension):
        row = list(map(int, input().split()))
        matrix.append(row)
        
    matrixT = transpose(matrix)
    
    correct_sum = get_correct_sum(dimension)
    row_sums = list(map(sum, matrix))
    col_sums = list(map(sum, matrixT))
    
    done = False
    wrong = False
    for i in range(dimension):
        if done:
            break
        for j in range(dimension):
            row_sum = row_sums[i]
            col_sum = col_sums[j]
            if col_sum != row_sum and col_sum != correct_sum and row_sum != correct_sum:
                print("This puzzle has more than one problem")
                done = True
                break
            if col_sum != correct_sum or row_sum != correct_sum:
                wrong = True
    if not done:
        for i in range(dimension):
            if done:
                break
            for j in range(dimension):
                row_sum = row_sums[i]
                col_sum = col_sums[j]
                if row_sum != correct_sum and col_sum != correct_sum:
                    print("Problem exists at (" + str(i + 1) + "," + str(j + 1) + "): the " + str(matrix[i][j]) + " should be a " + str(matrix[i][j] + correct_sum - row_sum))
                    done = True
                    break
    if not done:
        if wrong:
            print("This puzzle has more than one problem")
        else:
            print("This puzzle is already solved")


# def transpose(matrix):
#     return list(zip(*matrix))
# 
# def get_correct_sum(n):
#     return (n * (n + 1)) // 2
#     
# while True:
#     try:
#         dimension = int(input())
#     except EOFError:
#         break
#     
#     matrix = []
#     for _ in range(dimension):
#         row = list(map(int, input().split()))
#         matrix.append(row)
#         
#     matrixT = transpose(matrix)
#     
#     correct_sum = get_correct_sum(dimension)
#     row_sums = list(map(sum, matrix))
#     col_sums = list(map(sum, matrixT))
#     
#     done = False
#     wrong = False
#     for i in range(dimension):
#         if done:
#             break
#         for j in range(dimension):
#             row_sum = row_sums[i]
#             col_sum = col_sums[j]
#             if col_sum != row_sum and col_sum != correct_sum and row_sum != correct_sum:
#                 print("This puzzle has more than one problem")
#                 done = True
#                 break
#             if col_sum != correct_sum or row_sum != correct_sum:
#                 wrong = True
#     if not done:
#         for i in range(dimension):
#             if done:
#                 break
#             for j in range(dimension):
#                 row_sum = row_sums[i]
#                 col_sum = col_sums[j]
#                 if row_sum != correct_sum and col_sum != correct_sum:
#                     print("Problem exists at (" + str(i + 1) + "," + str(j + 1) + "): the " + str(matrix[i][j]) + " should be a " + str(matrix[i][j] + correct_sum - row_sum))
#                     done = True
#                     break
#     if not done:
#         if wrong:
#             print("This puzzle has more than one problem")
#         else:
#             print("This puzzle is already solved")