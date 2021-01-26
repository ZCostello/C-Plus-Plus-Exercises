/*
  Program to check if input numbers are 'magic numbers'.
  
  There are 2 conditions for a magic number:
    1. No digits repeat.
    2. Beginning with the leftmost digit, take the value of the digit and move that number of digits to the right.
       Repeat the process again using the value of the current digit to move right again. 
       Wrap back to the leftmost digit as necessary. 
       A magic number will visit every digit exactly once and end at the leftmost digit. 
  Inputs: Two integers on a line, separated by spaces.
          Each integer A and B is 1 <= A <= B <= 10000.
  Output: Prints each magic number between A and B, inclusive.
          If there is no magic number between A and B, print -1.
  Author: Zack Costello
  Created: v1.0 10/03/2020
  
  v1.0: Fulfills criteria.
        Removed "using namespace std".
*/

// Header files for standard libraries
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

// using namespace std;

std::vector<int> createVector(int);
bool checkRepeats(std::vector<int>);
bool checkVisits(std::vector<int>);

int main() {
  std::string line;
  std::vector<int> currentVector;
  int inputA = 0, inputB = 0;
  // int inputASize = 0, inputBSize = 0; // Initialise size check integers
  bool invalidNum;
  
  while (getline(std::cin, line,' ')) {
    int isMagicCount = 0;
    
    // --- Step 1: Read input, get integers from input ---
    std::stringstream(line) >> inputA; // Get inputA (type int) from "line"
    // inputASize = stringstream(line).str().size(); // Get number of digits of inputA
    
    std::getline(std::cin,line); // Next input
    std::stringstream(line) >> inputB;  // Get inputB (type int) from "line"
    // inputBSize = stringstream(line).str().size(); // Get number of digits of inputB
    
    /*
    // *** Debugging checks if limited IDE: Print variables ***
    // Print inputA and inputB
    cout << "inputA: " << inputA << "\n"
      << "inputB: " << inputB << "\n\n";
    // Print inputAsize and inputBsize
    cout << "inputAsize: " << inputASize << "\n"
      << "inputBsize: " << inputBSize << "\n";
    */
    
    // Check inputs 1 <= A <= B <= 10000
    if ((inputA < 1) || (inputB > 10000) || (inputB < inputA)) {
      std::cout << "ERROR: Inputs must be 1 <= A <= B <= 10000" << std::endl;
    }
    
    // Increment through numbers A <= B
    for (int currentNum = inputA; currentNum <= inputB; currentNum++) {
      std::vector<int> currentVector;
      bool invalidNum, isMagic;
      
      // *** Step 2: Create vector storing digits ***
      currentVector = createVector(currentNum); // Create vector of current number
      invalidNum = checkRepeats(currentVector); // Check if number is valid (magic number characteristic 1)

      if (!invalidNum) {  // If number has no zeros or repeats
        isMagic = checkVisits(currentVector); // Check if condition 2 is fulfilled
      }
      else {
        isMagic = false;  // Necessary otherwise will give false positives
                          // (isMagic == true can carry over into next number)
      }
      
      // If current number is a magic number, print on a separate line
      if (isMagic)    {
        isMagicCount++;
        std::cout << currentNum << std::endl;
      }
    }
    // If there is no magic number between A and B, print -1
    if (isMagicCount == 0) {
      std::cout << "-1" << std::endl;
    }
  }
}

// Creates a vector containing the digits of the current number
std::vector<int> createVector(int initialInput)  {
  std::vector<int> initialVector;
  // initialVector.reserve(initialSize); // Reserve size of starting integer for vector (could improve performance)
  for (; initialInput > 0; initialInput /= 10)  { // Create vector with each digit stored in an individual element
    initialVector.push_back(initialInput%10);
  }
  std::reverse(initialVector.begin(),initialVector.end()); // Created vector is in reverse order, so need to reverse it back
  
  return initialVector;
}

// Checks for repeated digits and zeros
bool checkRepeats(std::vector<int> inputVector)  {
  bool invalidNum;
  
  std::sort(inputVector.begin(),inputVector.end()); // Sort input vector for efficient check
  if (count(inputVector.begin(),inputVector.end(),0))   {  // Check if contains zero
    invalidNum = true;
  }
  else {  // If not, check if contains repeated digits
    invalidNum = std::adjacent_find(inputVector.begin(),inputVector.end()) != inputVector.end();
  }
  return invalidNum;
}

// Check if visits every digit exactly once and ends at the leftmost digit
bool checkVisits(std::vector<int> inputVector) {
    int vectorSize, iterCount = 0, currentLoc = 0;
    bool loopingDigit = false, isMagic;

    vectorSize = inputVector.size();
    while (iterCount < vectorSize) {  // If valid, the number of iterations will equal number of digits
        for (int currentDigit = inputVector.at(currentLoc); currentDigit > 0; currentDigit--) {  // Take value of digit at current element
            currentLoc++;
            if (currentLoc > (vectorSize - 1)) {  // If current element reaches end of vector, wrap back to first element
                currentLoc -= vectorSize;
            }
        }
        iterCount++;
      
        // Error check: If first digit equals a multiple of the vector size, it will loop back to the first element.
        // This will give a false positive. Introduced a boolean check for this.
        if ((iterCount < vectorSize) && (currentLoc == 0))    {
            loopingDigit = true;
        }
    }
    isMagic = ((currentLoc == 0) && (!loopingDigit));  // Check if magic number
    return isMagic;
}