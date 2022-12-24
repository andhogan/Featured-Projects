import random
def Convert_Text(_string):
    """
    Define this function such that it takes in a simple 
    string such as "hello" and outputs the corresponding
    standard list of integers (ascii) for each letter in the word hello.
    For example:
    _string = hello
    integer_list = [104, 101, 108, 108, 111]
    """
    integer_list = []
    for character in _string:
        integer_list.append(ord(character)) # ord('s') method returns Unicode/ASCII code of the passed string.
                                            # however, it only accepts strings of length '1'/a single character, making it the perfect tool to use for iterating through strings.
                                            # The for loop allows us to iterate over each character in the string.
                                            # Then we append each character's UNICODE value to the integer list as it is converted.
    
    return integer_list

#print(Convert_Text("hello"))

#-------------------------------------------------

def Convert_Num(_list):
    """
    Do the opposite of what you did in the Convert_Text
    function defined above.
    
    Define this function such that it takes in a list of integers
    and outputs the corresponding string (ascii).
    
    For example:
    _list = [104, 101, 108, 108, 111]
    _string = hello
    """
    _string = ''
    for i in _list:
        _string += chr(i) # chr() method accepts an integer respective of UNICODE and returns a corresponding character (a string). 
                          # The opposite of ord() method.
    return _string

#print(Convert_Num([104, 101, 108, 108, 111]))

#----------------------------------------------

def Convert_Binary_String(_int):
    """
    Here, you need to define a function that converts an integer to
    a string of its binary expansion.
    
    For example:
    _int = 345
    bits = 101011001
    """
    n = _int
    bits = ''
    while n > 0:
        k = n % 2  # this calculates the rightmost bit
        n = n // 2 # this brings n down to zero as we proceed through the loops, // indicates integer division and rounds down, a type of floor function
        bits = str(k) + bits # Since we calculate the rightmost bit first through each loop, we want to insert it at the front.
    
    return bits # we are returning bits as a STRING here

#print(Convert_Binary_String(345))
#print(Convert_Binary_String(345)[::-1])

#-----------------------------------------------------

def FME(b, n, m): # b: integer, n: exponent, m: modulus
    """
    1. Using the fast modular exponentiation algorithm,
    the below function should return b**n mod m.
    As described on page 254. (however, you may input the exponent and 
    then convert it to a string - the book verison imports the binary expansion)  
    2. You should use the function defined above
    Convert_Binary_String()
    3. Use this string to test which components are used in the calculation.
    4. Yes, there are many other ways to do this. 
***UPDATE*** You may use the function you developed in your problem set - but be sure it is your own work, commented, etc.. and change inputs as needed.
    """  
    x = 1 # Houses the total modulations, and is the total value that will be returned
    p = b % m # start with the initial base. This is symbolic of base**0
    bin_n = Convert_Binary_String(n) # convert the exponent n to a binary string for iteration
    for i in bin_n[::-1]: # we only run through the length of the bin, we are comfortable leaving it as a string here
                          # it's also easier to reverse the string so that we begin with the rightmost digit on the left.
        if i == '1':      # checks to see if the bit is 'on'/1. If so, we multiply our modular exponentiation to x
            
            
            x = (x*p) % m # multiply this mod to our result
        p = (p*p)%m       # regardless of 1 or 0, we are iterating through the digits and adjust our base as we go along.
                          # This is the magic piece of FME, as we calculate each b, b**2 ... b**(2**j) onward for as many iterations as there are digits in the binary exponent.
            
    return x # we are returnig (b**n mod m)

#print(FME(7, 644, 645))

#------------------------------------

def Euclidean_Alg(a, b):
    """
    1. Calculate the Greatest Common Divisor of a and b.
    
    2. Unless b==0, the result will have the same sign as b (so that when
    b is divided by it, the result comes out positive).
    The function must return a single integer 'x' which is
    the gcd of a and b.
    """
    
    m = max(abs(a), abs(b)) # takes the larger of the two numbers and assigns it
    n = min(abs(a), abs(b)) # takes the smaller
        # These two variables keep the algorithm moving in a downward direction towards the base case.
        # By definition, GCD is a positive integer. We ensure a and b are positive by making them absolute values.
        # Depending on user input, we don't want the smaller number modded by the larger. To keep things organized, we set the maximum value of the two to m, and the other to n.
            
    if n == 0:    # We cannot modulo by 0. But if this ever occurs, we should have our GCD.
        return abs(m)  # this is the GCD of a and b, since we are returning the other variable that is not 0.
    r = m % n
    
    return Euclidean_Alg(n, r) # n should be larger than our remainder. r is "the new jug"

#print(Euclidean_Alg(224, 47))
#print(Euclidean_Alg(36, -18))
#print(Euclidean_Alg(100, 10))
#print(Euclidean_Alg(10, 100))

#----------------------------------

def EEA(a, b):
    m = max(abs(a), abs(b)) # takes the larger of the two numbers and assigns it
    n = min(abs(a), abs(b)) # takes the smaller
                            # By definition, GCD is a positive integer. We ensure a and b are positive by making them absolute values.
                            # Depending on user input, we don't want the smaller number modded by the larger. 
                            # To keep things organized, we set the maximum value of the two to m, and the other to n.
                            # this time, we're going to keep track of the initial values of these two
        
    m0, n0 = m, n # these values keep track of our initial m and n, since we will be expressing the GCD in terms of these two
    # Bezout's theorem: GCD = s*m + t*n
    s1, t1 = 1, 0
    s2, t2 = 0, 1 # these initialize our Bezout coefficients
                  # m' = s1*m0 + t1*n0 = 1*m0 + 0*n0
                  # n' = s2*m0 + t2*n0 = 0*m0 + 1*n0
    while n > 0:
        k = m % n # the remainder, becomes the new n after the iteration is complete
        q = m // n # the quotient, used to calculate the next Bezout coefficients in the series
        
        m = n 
        n = k
        
        s1_hat, t1_hat = s2, t2                    # 's1_hat, t1_hat are placeholders/pointers for the old s2, t2 values before they are changed'
        s2_hat, t2_hat = (s1 - q*s2), (t1 - q*t2)  # 's2_hat, t2_hat acquire the new calculated values and holds them'
        s1, t1 = s1_hat, t1_hat                    # 's1, t1 acquires s2, t2 via s1_hat, t1_hat'
        s2, t2 = s2_hat, t2_hat                    # 's2, t2 are assigned s2_hat, t2_hat, readying them for the next iteration'
        
    return m, (s1, t1) # After the loop is complete, n = 0, and m will be the GCD in lowest terms
                       # s1 and t1 will also be in terms that when multiplied with their respective integers will yield the GCD.
                       # When using this algorithm, it's important to know that s1 corresponds to the Bezout coefficient of the LARGER INTEGER, and vice versa for t1 to the SMALLER
        
#-----------------------------

def EEA_debug(a, b):
    m = max(abs(a), abs(b)) # takes the larger of the two numbers and assigns it
    n = min(abs(a), abs(b)) # takes the smaller
                            # this time, we're going to keep track of the initial values of these two
        
    m0, n0 = m, n # these values keep track of our initial m and n, since we will be expressing the GCD in terms of these two
    # Bezout's theorem: GCD = s*m + t*n
    s1, t1 = 1, 0
    s2, t2 = 0, 1 # these initialize our Bezout coefficients
                  # m' = s1*m0 + t1*n0 = 1*m0 + 0*n0
                  # n' = s2*m0 + t2*n0 = 0*m0 + 1*n0
    loop = 0
    print(f'To begin: a, b = {m}, {n} | (s1,t1) = ({s1},{t1}) | (s2,t2) = ({s2},{t2})')
    print('_________________________________')
    while n > 0:
        loop += 1
        print(f'Loop: {loop}')
        k = m % n # 
        print(f'Our remainder, k = a % b = {m} % {n} = {k}')
        q = m // n
        print(f'Our quotient , q =a // b ={m} // {n} = {q}')
        
        m = n
        n = k
        print(f'Our new a, b = {m}, {n}')
        s1_hat, t1_hat = s2, t2
        print('s1_hat, t1_hat are placeholders/pointers for the old s2, t2 values before they are changed')
        print(f's1_hat, t1_hat = (s2, t2) = ({s2}, {t2})\n')
        s2_hat, t2_hat = (s1 - q*s2), (t1 - q*t2)
        print('s2_hat, t2_hat acquire the new calculated values and holds them')
        print(f's2_hat, t2_hat = (s1 - q*s2), (t1 - q*t2) = ({s1 - q*s2}, {t1 - q*t2})\n')
        s1, t1 = s1_hat, t1_hat
        print('s1, t1 acquires s2, t2')
        print(f's1, t1 = (s1_hat, t1_hat) = ({s1_hat}, {t1_hat})\n')
        s2, t2 = s2_hat, t2_hat
        print('s2, t2 are assigned s2_hat, t2_hat, readying them for the next iteration')
        print(f's2, t2 = (s2_hat, t2_hat) = ({s2_hat}, {t2_hat})\n')
        print('-----------------------------')
    
    print(f'GCD({m0},{n0}) = {m}, Bezout Coefficients: s1, t1 = ({s1},{t1})')
    print('The Bezout Theorem for our GCD can be written as:')
    print(f'{m} = {s1} * {m0} + {t1} * {n0}')
    return m, (s1, t1) # When using this algorithm, it's important to know that s1 corresponds to the Bezout coefficient of the LARGER INTEGER, and vice versa for t1 to the SMALLER

#print(EEA_debug(77, 14))

#-----------------------------

def Find_Public_Key_e(p, q):
    """
    Implement this function such that
    it takes 2 primes p and q.
    
    Use the gcd function that you have 
    defined before.
    
    The function should return 2 elements as follows:
    public key: n
    public key: e
    
    
    HINT: this function will run a loop to find e such 
    that e is relatively prime to (p - 1) (q - 1) 
    and not equal to p or q.
    """
    import random # module will be used to randomly select an e to return from a soon to be populated list
    
    n = p*q
    list_all = []
    list_e_rel_prime_to_fi = []
    
    for i in range(2, (p-1)*(q-1)):
        if i != p and i != q:  # we don't want an e that equals p or q
            list_all.append(i) # populates a list of numbers 1 < e < (p-1)(q-1), not including p and q
                               # we don't want e to equal 1, and we need it to be less than (p-1)(q-1) for the EEA later.
    
    for num in list_all:
        if Euclidean_Alg(num, (p-1)*(q-1)) == 1: # we only want to select an e that is rel prime to (p-1)(q-1)
            list_e_rel_prime_to_fi.append(num)   # we populate a list of potential e's to use
            
                                                 #print(list_e_rel_prime_to_fi) # potential e's
    
    e = random.choice(list_e_rel_prime_to_fi) # randomly select a choice from our list of e's
    #e = list_e_rel_prime_to_fi[-2]
    
    print(f'n, e = {n}, {e}')
    return n, e

#n, e = Find_Public_Key_e(53, 67)

#------------------------------

def Find_Private_Key_d(e, p, q):
    """
    Implement this method
    to find the decryption exponent d such that
    d is the modular inverse of e. 
    
    This will use the Extended Euclidean Algorithm
    
    This function should return the following:
    d: the decryption component.
    """
    
    m, Bezout = EEA(e, (p-1)*(q-1))
    print(f'm, Bezout = {m}, {Bezout} ')
    d = Bezout[1] # e is smaller than our quantity (p-1)(q-1). 
                  # Given how the algorithm is designed, we want to assign it the second Bezout Coefficient since the first one corresponds to the larger int.
    while d < 0: # we do not want a negative inverse.
                 # If the inverse is negative, we get a non-integer result that cannot be modded
                 # To fix this, we keep adding the modulus, (p-1)(q-1), to d until it is positive
                 # de = 1 mod ((p-1)(q-1))
        d += ((p-1)*(q-1))
            
    print(f'The inverse, d = {d}')
    return d

#d = Find_Private_Key_d(e, p=53, q=67)

#------------------------------------------------

def Encode(n, e, message):
    """
    Here, the message will be a string of characters.
    Use the function Convert_Text from 
    the basic tool set and get a list of numbers.
    
    Encode each of those numbers using n and e and
    return the encoded cipher_text.
    """
    int_list = Convert_Text(message)
    cipher_text = []
    
    #print(int_list)
    for M in int_list:
        C = FME(M, e, n)
        cipher_text.append(C)
    
    return cipher_text

#test_message = Encode(n, e, 'hello')

#------------------------------------------------

def Decode(n, d, cipher_text):
    """
    Here, the cipher_text will be a list of integers.
    First, you will decrypt each of those integers using 
    n and d.
    Later, you will need to use the function Convert_Num, that converts the integers to a string, 
    from the basic toolset to recover the original message as a string. 
    
    """
    message_list = []
    for C in cipher_text:
        D = FME(C, d, n)
        message_list.append(D)
    
    message = Convert_Num(message_list)
    return message

#message = Decode(n, d, test_message)
#print(message)

#------------------------------------------------

## Brute Force Factoring
def factorize(n):
    # n is a number, return the smallest factor of n
    for i in range(2, n):
        if n % i == 0:
            return i
        else:
            continue
    return False
# this function returns only one factor, p
# q = n // p

#-----------------------------------------------

from itertools import count

#n, x = 122, 2

def pollard_rho(n, x):
    for cycle in count(1):
        y = x
        for i in range(2 ** cycle):
            x = (x * x + 1) % n
            factor = Euclidean_Alg(x - y, n)
            if factor > 1:
                print("factor is", factor)
                return factor

p = pollard_rho(n, x)
print(p)