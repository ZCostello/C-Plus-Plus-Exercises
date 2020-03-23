# RSA_decrypter

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
