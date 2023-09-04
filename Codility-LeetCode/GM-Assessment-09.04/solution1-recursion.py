# write a function solution that , given integer N, 
# returns the smallest non negative integer whose individual digits sum to N.

# Given N = 16, the function should return 79, 
# there are many numbers whose digits sum to 16 (for example : 79, 97,808,551,22822,etc.) . the smallest such number is 79.

# 2. given N = 19, THE FUNCTION SHOULD RETURN 199 
# (the sum of digits is 1+9+9 = 19).

# 3. Given N= 7, the function should return 7.

# assume that:

# N is an interger within the range [0..50].

def solution(N):
    # Handle the erroneous case when N is a negative number (although given the assumed range, this spec is not likely)
    if N < 0:
        return 0
    
    # Base case: N is one digit, so the max_digit = N
    if N <= 9:
        return N

    # Initialize max digit (for readability and illustration), starting with the largest possible single digit: 9 to optimally subtract from N iteratively.
    max_digit = 9

    # recursively add digits to the result all while subtracting the max digit from N
    result = solution(N-max_digit) * 10 + max_digit     # solution(N-9) * 10 + 9

    return result

# My test cases

# for i in range (0, 51):
#     print(solution(i))

# print(solution(16))  # Should return 79
# print(solution(19))  # Should return 199
# print(solution(7))   # Should return 7
# print(solution(20))  # 299
# print(solution(21))  # 399, and so on...
# print(solution(22)) 
# print(solution(23)) 
# print(solution(24)) 
# print(solution(25)) 
# print(solution(26)) 
# print(solution(27)) # 999
# print(solution(28)) # 1999



