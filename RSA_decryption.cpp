/*
  RSA_decryption.cpp
  Program to decrypt public-key RSA (for small keys).
  
  Step 1: Given a ciphertext (c), modulus (N) and encryption key (e).
          decompose N into two primes, p and q
  Step 2: Calculate the totient function (phiN),
          phiN = (p - 1) * (q - 1)
  Step 3: Calculate the decryption key (d) using the modular inverse,
          d = e^(-1) * mod(phiN)
  Step 4: Find the plaintext message using modular exponentiation,
          plainText = C^(n) * mod(N)
  Step 5: Convert the plaintext to hexadecimal then print as an ASCII string
  
  Inputs (hex-encoded): ciphertext (c)
						modulus (N)
						encryption key (e)
  Output: Prints decrypted output message as a string

  Sources used for RSA:
  Erickson, J. (2008). Hacking: the art of exploitation. No starch press.
  Schneier, B. (2007). Applied cryptography: protocols, algorithms, and source code in C. john wiley & sons.
  Schneier, B., Kohno, T., & Ferguson, N. (2013). Cryptography engineering: design principles and practical applications. Wiley.
  
  Author: Zack Costello
  Email: costellozd@outlook.com
  Created: v1.0 10/03/2020
  
  v1.0: Fulfills criteria for BAE challenge.
        Removed "using namespace std".
*/

// Header files for standard libraries
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>
// using namespace std;

long long int decomposePrime(long long int);
long long int modInv(long long int, long long int);
unsigned long long int fastExp(long long int, unsigned long long int);
long long int modExp(long long int, unsigned long long int, long long int);
std::string hexToASCII(std::string);

int main() {
  std::string line;
  
  while (getline(std::cin, line)) {
    long long int e = 0, p = 0, q = 0, plainText, c = 0, N = 0, phiN = 0, d = 0;

    // Get ciphertext c from input stream
    std::stringstream(line) >> std::hex >> c;
    // Get modulus N from input stream
    getline(std::cin, line);
    std::stringstream(line) >> std::hex >> e;
    // Get encryption key e from input stream
    getline(std::cin, line);
    std::stringstream(line) >> std::hex  >> N;
    
    /*
    // Print input values
    std::cout << "c = " << c << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "N = " << N << std::endl;
    */
    
    p = decomposePrime(N);
    q = N/p;
    
    // std::cout << std::endl << "P = " << p << std::endl;
    // std::cout << "Q = " << q << std::endl;

    phiN = (p - 1)*(q - 1);
    d = modInv(e, phiN);
    // std::cout << "d = " << d << std::endl;

    plainText = modExp(c,d,N);

    // std::cout << "decrypted = " << plainText << std::endl;
    // std::cout << "decrypted (Hex) = " << std::hex << plainText << std::endl;

    std::stringstream(plainTextConversion);
    plainTextConversion << std::hex << plainText;
    std::string messageHex = plainTextConversion.str();
    // std::cout << "message (String) = " << messageHex << std::endl;

    std::string messageASCII;
    messageASCII = hexToASCII(messageHex);
    std::cout << messageASCII << std::endl;
  }
}

// Prime decomposition using Pollard's rho algorithm
// Adapted from C code sample:
// https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#C_code_sample
long long int decomposePrime(long long int n) {
    long long int x_fixed = 2, x = 2;
    long long int size = 2, factor, count, loop = 1;
    do {
        // std::cout << "Loop: " << loop << std::endl;
        count = size;
        do {
            x = (x * x + 1) % n;
            factor = std::gcd(abs(x - x_fixed), n);
            // std::cout << "Count = " << (size-count+1) << " | x = " << x << " | Factor = " << factor << std::endl;
        }
        while (--count && (factor == 1));
        size *= 2;
        x_fixed = x;
        loop++;
    }
    while (factor == 1);
    // std::cout << "Factor is " << factor << std::endl;
    return factor;
}

// Modular inverse
// Adapted from: https://rosettacode.org/wiki/Modular_inverse#C.2B.2B
long long int modInv(long long int a, long long int b) {
    long long int b0 = b, t, q;
    long long int x0 = 0, x1 = 1;

    if (b == 1) return 1;
    while (a > 1) {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}

// Fast exponentiation algorithm using bitwise operations at the mod and divisor operators
// Adapted from: https://www.programminglogic.com/fast-exponentiation-algorithms/
unsigned long long int fastExp(long long int base, unsigned long long int exp) {
    unsigned long long int output = 1;

    while (exp) {
        if (exp & 1) {
            output *= base;
        }
        exp >>= 1;
        base *= base;
    }
    return output;
}

// Iterative Function to calculate (x^y)%p in O(log y)
// Adapted from C++ sample:
// https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
// Modified "base = ((base*base)) % mod)" to use fast exponentiation algorithm
// This allows large exponents to be used (avoiding integer overflows), such as Example 3
long long int modExp(long long int base, unsigned long long int exp, long long int mod) {
    long long int output = 1;     // Initialize result
    unsigned long long int baseSquare = 0;

    while (exp > 0) {
        if (exp % 2 == 1)
            output = (output * base) % mod;
        exp = exp >> 1;
        baseSquare = fastExp(base,2);
        base = (baseSquare % mod);
    }
    return output;
}

// Convert hex string to ASCII string
std::string hexToASCII(std::string inputStr) {
    int strLen = inputStr.length();
    std::string outputStr;
    for (int i = 0; i < strLen; i += 2) {
        std::string byte = inputStr.substr(i,2);
        char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
        outputStr.push_back(chr);
    }
    return outputStr;
}