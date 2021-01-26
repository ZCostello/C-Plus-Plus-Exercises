# C++ Coding Exercises

## RSA_decrypter

Program to decrypt public-key RSA (for small keys). Created for a programming challenge.
  
- Step 1: Given a ciphertext (c), modulus (N) and encryption key (e), decompose N into two primes, p and q
          
- Step 2: Calculate the totient function (phiN), `phiN = (p - 1) * (q - 1)`

- Step 3: Calculate the decryption key (d) using the modular inverse, `d = e^(-1) * mod(phiN)`

- Step 4: Find the plaintext message using modular exponentiation, `plainText = C^(n) * mod(N)`

- Step 5: Convert the plaintext to hexadecimal then print as an ASCII string


**Inputs (hex-encoded):**
    
>ciphertext (c) <br />
>modulus (N) <br />
>encryption key (e) <br />

**Output:**
>Prints decrypted output message as a string

Sources used for RSA:
```
  Erickson, J. (2008). Hacking: the art of exploitation. No starch press.
  Schneier, B. (2007). Applied cryptography: protocols, algorithms, and source code in C. john wiley & sons.
  Schneier, B., Kohno, T., & Ferguson, N. (2013). Cryptography engineering: design principles and practical applications. Wiley.
```
## Magic Numbers

Program to check if input numbers are 'magic numbers'.

There are 2 conditions for a magic number:
```
    No digits repeat.
    Beginning with the leftmost digit, take the value of the digit and move that number of digits to the right. Repeat the process again using the value of the current digit to move right again. Wrap back to the leftmost digit as necessary. A magic number will visit every digit exactly once and end at the leftmost digit.
```

**Inputs:**

Two integers on a line, separated by spaces. Each integer A and B is 1 <= A <= B <= 10000.

**Output:**

Prints each magic number between A and B, inclusive. If there is no magic number between A and B, print -1.
