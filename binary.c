#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
Notes

gcc binary.c -o binary && ./binary

  // The length of the binary characters (1 or 0) depends on 32 or 64 bit OS (aarch64).
  binaryLength bits (n + 1).

  Moving bits on hardware instead of 1 byte (8 bits) for each character.

  // C int uses less memory than the character arrays (4 vs 8)
  32    vs  16    bit operating system (aarch64) int uses
  4     vs  2     bytes
  +-2m  vs  +-32k numbers)
  C has built in functions for lower memory binary addition.
  Internet example uses bitwise operations similar to
  Assembly AND, XOR, Left Shift:

  // Using character arrays and more memory.
  The length of binary representations of decimals depends on 32 vs 64 bit OS.
  size_t i = sizeof(binaryOne) / sizeof(binaryOne[0]);
  Largest unsigned 64 bit number is 18,446,744,073,709,551,615 or 0xFFFFFFFFFFFFFFFF
  1111111111111111111111111111111111111111111111111111111111111111
  64 digits

  // Change or convert from or to int binary:
  Internet says to multiply 1 by 10 each iteration to store the binary or use bitwise.
  C max int on 32 bit is 2 billion and this method doesn't work to calculate
  numbers around 2000. Try and except or move to calculator.c for bitwise and int arrays.

  // Internet binary addtion example with bitwise operations.
  int binaryOne1 = 0b0000001;
  int binaryTwo2 = 0b0000011;
  while (binaryTwo2 != 0) {
    int carry = binaryOne1 & binaryTwo2;  // Finds the carry.
    binaryOne1 = binaryOne1 ^ binaryTwo2; // Adds the bits without the carry.
    binaryTwo2 = carry << 1;              // Shifts the carry left.
  }
  printf("binaryOne1 plus binaryTwo2 = %d\n", binaryOne1);

*/

// Int structure for decimal2Binary()
struct decimal2Binary {
  int one;
  int two;
};

// Input to the power of number.
// Not used right now.
int power(int input, int powerNumber) {
  int output = 1;
  int i = 1;
  while(i <= powerNumber){
    output *= input;
    // printf("%d  %d\n", i, output);
    i++;
  }
  return output;
}

// Inputs int decimal and outputs int binary and binary digit length.
struct decimal2Binary values(int decimal, int binaryLength) {
  // binary is set to a value to avoid memory issues.
  int binary = 0;
  int remainder;
  int i = binaryLength;
  int shift = 1;
  // printf("Decimal: %d\n", decimal);
  while (i > 0) {
    remainder = decimal % 2;
    decimal = decimal / 2; // quotient
    // Internet says multiply by the remainder.
    binary = binary + (remainder * shift);
    if (decimal == 0) {
      // printf("Number of 0 after quotient is zero: %d\n", binaryLength - 1);
      break;
    }
    // C max int on 32 bit is 2 billion and this method doesn't work to calculate > 2000.
    shift *= 10;
    // printf("%d %d  %d  %d  %d        %d\n", i, decimal, remainder, binary, shift);
    i--;
  }
  struct decimal2Binary output;
  // Length of int binary without prefix and '0's.
  output.one = binaryLength - (i - 1);
  // int binary.
  output.two = binary;
  // printf("Struct: %d  %d\n\n", output.one, output.two);
  return output;
}

// todo refractor - avoid converting to char.
// Convert int binary to char[] binary.
char* intBinary2Char(struct decimal2Binary intZerosBinary, int binaryLength) {
  // char pointer holds the binaryLength.
  char *charBinary = malloc(intZerosBinary.one * sizeof(char));
  strcpy(charBinary, "a");
  // i is incremented for the duration of the loop to place the prefix and '0's.
  int i = intZerosBinary.one - 1;
  while(i >= 0) {
    // Reverse intZerosBinary.two as a char.
    int intBinaryDigit = intZerosBinary.two % 10;
    charBinary[i] = intBinaryDigit + '0';
    intZerosBinary.two /= 10;
    // printf("%d  %d    %s\n", i, intBinaryDigit, charBinary);
    i--;
  }
  // printf("intBinary2Char:  %s\n", charBinary);
  return charBinary;
}



// todo
// Convert char[] binary to int binary.
int charBinary2Int(char binary[], int binaryLength) {
  // Internet uses bitwise left shift and OR in a loop:
  // printf("binary: %s\n", binary);
  int intBinary = 1;
  int i = 0;
  while (i < (binaryLength - 1)) {
    intBinary = (intBinary * 10) + (binary[i] - '0');
    i++;
  }
  intBinary = intBinary / 10;
  // printf("\nintBinary:  %d\n", intBinary);
  return intBinary;
}



// Adds two char binary. Returns the addition.
char* binaryAddition(char binaryOne[], char binaryTwo[], int intBinaryLength, int difference, int intBinaryGreater) {
  // Allocates memory that is later deallocated with free().
  char *binarySum = malloc(intBinaryLength * sizeof(char));
  strcpy(binarySum, "a");
  // 'carry' is used in binary addtion.
  int carry = 0;
  int i = intBinaryLength-1;
  int intBinary = 1;

  while (i >= 0) {
    // Convert char arrays to int for addition.
    int binaryOne3;
    int binaryTwo3;
    // Using the 'difference' in length to access the last binary digit.
    if (intBinaryGreater == 0) {
      binaryOne3 = binaryOne[i - 1] - '0'; // " -'0' " ascii ordering
      binaryTwo3 = binaryTwo[i - 1] - '0'; // prevents scaling.
    }
    else if (intBinaryGreater == 1) {
      binaryOne3 = binaryOne[i] - '0';
      binaryTwo3 = binaryTwo[i - difference] - '0';
    }
    else if (intBinaryGreater == 2) {
      binaryOne3 = binaryOne[i - difference] - '0';
      binaryTwo3 = binaryTwo[i] - '0';
    }
    // If one is longer than the other, '-48' is returned on the shorter
    // int and that binary digit is set to 0. todo function
    if ( (binaryOne3 != 1 && binaryOne3 != 0) && (binaryTwo3 != 1 && binaryTwo3 != 0) ) {
      binaryOne3 = 0;
      binaryTwo3 = 0;
    }
    else if (binaryOne3 != 1 && binaryOne3 != 0) {
      binaryOne3 = 0;
    }
    else if (binaryTwo3 != 1 && binaryTwo3 != 0) {
      binaryTwo3 = 0;
    }
    // printf("%d %d    %d %d\n", i, binaryOne3, i-difference, binaryTwo3);
    // Add the bits.
    int binaryAdd = binaryOne3 + binaryTwo3;
    // Convert int back to char[].
    // Calculates the carry.
    if (binaryAdd == 1 && carry == 0) {
      binarySum[i] = binaryAdd + '0';
      carry = 0;
    }
    else if (binaryAdd == 0 && carry == 1) {
      binaryAdd = 1;
      binarySum[i] = binaryAdd + '0';
      carry = 0;
    }
    else if (binaryAdd == 1 && carry == 1) {
      binaryAdd = 0;
      binarySum[i] = binaryAdd + '0';
      carry = 1;
    }
    else if (binaryAdd == 0 && carry == 0) {
      binarySum[i] = binaryAdd + '0';
      carry = 0;
    }
    else if (binaryAdd == 2 && carry == 0) {
      binaryAdd = 0;
      binarySum[i] = binaryAdd + '0';
      carry = 1;
    }
    else if (binaryAdd == 2 && carry == 1) {
      binaryAdd = 1;
      binarySum[i] = binaryAdd + '0';
      carry = 1;
    }
    else {
      binarySum[i] = '0';
    }
    //printf("\n%d  %d  %d    %d + %d = %d    %s\n", i, i-difference, intBinaryGreater, binaryOne3, binaryTwo3, binaryAdd, binarySum);
    i--;
  }
  printf("Binarysum %s\n", binarySum);
  return binarySum;
}

// Convert binary to decimal int.
int binary2Decimal(int binary) {

  int decimal;

  return decimal;
}

int main() {
  // Input decimal int, output binary.
  int integerOne = 4; // doesnt work sum > 2000
  int integerTwo = 3;
  // 8 bit binary (n + 1) to include the 'b' prefix. 'const' might break other libraries.
  int binaryLength = 17;
  // printf("Decimals: %d  %d\n", integerOne, integerTwo);
  struct decimal2Binary intBinaryOne = values(integerOne, binaryLength);
  struct decimal2Binary intBinaryTwo = values(integerTwo, binaryLength);
  // Convert 'binary' to char[] for 'binaryAddition()'.
  char *binaryOne = intBinary2Char(intBinaryOne, binaryLength); // outputs: char binaryOne[] = "0b0000100";
  char *binaryTwo = intBinary2Char(intBinaryTwo, binaryLength); // outputs: char binaryOne[] = "0b0000011";


  // todo function
  // Length of the longest int binary for use in addition to calculate offset.
  int intBinaryLength = 0;
  // Stays the same if int binary is the same length.
  int difference;
  int intBinaryGreater;
  if (intBinaryOne.one == intBinaryTwo.one) {
    intBinaryLength = intBinaryOne.one + 1;
    difference = 0;
    intBinaryGreater = 0;
  }
  else if (intBinaryOne.one > intBinaryTwo.one) {
    intBinaryLength = intBinaryOne.one;
    difference = intBinaryOne.one - intBinaryTwo.one;
    intBinaryGreater = 1;
  }
  else if (intBinaryOne.one < intBinaryTwo.one) {
    intBinaryLength = intBinaryTwo.one;
    difference = intBinaryTwo.one - intBinaryOne.one;
    intBinaryGreater = 2;
  }

  // Uses malloc() and free().
  char *binaryAdd = binaryAddition(binaryOne, binaryTwo, intBinaryLength, difference, intBinaryGreater);
  printf("%d + %d = %s\n", integerOne, integerTwo, binaryAdd);
  free(binaryOne);
  free(binaryTwo);
  int intBinaryAdd = charBinary2Int(binaryAdd, binaryLength);
  free(binaryAdd);
  // int binary2Decimal(intBinaryAdd, binaryLength);
  return 0;
}
