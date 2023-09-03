# write a function solution that , given integer N, 
# returns the smallest non negative integer whose individual digits sum to N.

# Given N = 16, the function should return 79, 
# there are many numbers whose digits sum to 16 (for example : 79, 97,808,551,22822,etc.) . the smallest such number is 79.

# 2. given N = 19, THE FUNCTION SHOULD RETURN 199 
# (the sum of digits is 1+9+9 = 19).

# 3. Given N= 7, the function should return 7.

# asume that:

# N is an interger within the range [0..50].

def solution(N):
    # Handle the special case when N is one digit.
    if N <= 9:
        return N
    
    # Handle the case when N is a negative number (although given the range, this spec is optional)
    if N < 0:
        return 0

    # Initialize variables to store the result and the current digit.
    mod_result = 0
    current_digit = 9  # We start with the largest possible digit.

    # While N is greater than 0, keep adding digits to the result.
    while N > 0:
        # Calculate the maximum digit to add to the result without exceeding N.
        while current_digit > N:
            current_digit -= 1
        max_digit = min(current_digit, N)
        mod_result = mod_result * 10 + max_digit
        N -= max_digit

    true_result = int(str(mod_result)[::-1])
    

    return true_result

    
print(f"solution(16) = {solution(16)}. It is {'correct' if solution(16) == 79 else 'wrong' }.")
print(f"solution(19) = {solution(19)}. It is {'correct' if solution(19) == 199 else 'wrong' }.")
print(f"solution(7) = {solution(7)}. It is {'correct' if solution(7) == 7 else 'wrong' }.")

#My test cases
print(f"solution(20) = {solution(20)}. It is {'correct' if solution(20) == 299 else 'wrong' }.")
print(solution(21)) 
print(solution(22)) 
print(solution(23)) 
print(solution(24)) 
print(solution(25)) 
print(solution(26)) 
print(solution(27)) 
print(solution(28))


