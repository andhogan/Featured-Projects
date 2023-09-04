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
    # Handle the case when N is a negative number (although given the range, this spec is optional)
    if N < 0:
        return 0
    
    # Handle the case when N is one digit.
    if N <= 9:
        return N

    # Initialize variables to store the result to be modified later and the current digit.
    mod_result = 0
    current_digit = 9  # Start with the largest possible single digit to optimally subtract from N iteratively.

    # While N is greater than 0, keep adding the current digit to the result.
    while N > 0:
        # Calculate the maximum digit to add to the result without exceeding N.
        if N <= 9:
            current_digit = N

        mod_result = mod_result * 10 + current_digit # shifts previous digits forward to place a single digit in the ones place.
        N -= current_digit

    # reverse the string of digits to achieve the lowest possible integer
    # Ex: solution(16): Digits of 97 and 79 both add up to 16, but we want to accept the smaller value.
    true_result = int(str(mod_result)[::-1]) # reverse slice
    

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


