#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
Notes

gcc binary.c -o binary && ./binary

  C int uses less memory than the character arrays (4 vs 8)
  32    vs  16    bit operating system (aarch64) int uses
  4     vs  2     bytes
  +-2m  vs  +-32k numbers)
  C has built in functions for lower memory binary addition.
  Internet example uses bitwise operations similar to
  Assembly AND, XOR, Left Shift:

  Using character arrays and more memory.
  The length of binary representations of decimals depends on 32 vs 64 bit OS.
  size_t i = sizeof(binaryOne) / sizeof(binaryOne[0]);
  Largest unsigned 64 bit number is 18,446,744,073,709,551,615 or 0xFFFFFFFFFFFFFFFF
  1111111111111111111111111111111111111111111111111111111111111111
  64 digits

*/

// Int structure for decimal2Binary()
struct decimal2Binary {
  int one;
  int two;
  // An improved method is int array that holds 1000 int:
  // int numbers[1000];
  // but it starts conflicting later.
};

// Input to the power of number.
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

// Converts decimal int to binary int.
struct decimal2Binary values(int decimal, int binaryLength) {
  int binary;
  int remainder;
  int i = 0;
  int shift = 1;
  printf("decimal: %d\n", decimal);
  while (binaryLength > 0) {
    remainder = decimal % 2;
    decimal = decimal / 2; // quotient
    // Internet says multiply by the remainder.
    binary = binary + (remainder * shift);
    if (decimal == 0) {
      // printf("Number of 0 after quotient is zero: %d\n", binaryLength - 1);
      break;
    }
    // Internet says to multiply 1 by 10 each iteration to store the binary or use bitwise.
    shift = shift * 10;
    // printf("%d %d  %d  %b  %d        %d\n", i, decimal, remainder, binary, shift, binaryLength);
    i++;
    binaryLength--;
  }
  int base_zero = 10;
  int zeros = power(base_zero, binaryLength); // -1
  // printf("Binary: %d  %d\n", zeros, binary);
  struct decimal2Binary output;
  output.one = zeros;
  output.two = binary;
  // printf("Binary: %d  %d\n", output.one, output.two);
  return output;
}

// Convert char[] binary to int binary.
int charBinary2Int(char binary[], int binaryLength) {
  // Internet uses bitwise left shift and OR in a loop:
  // printf("binary: %s\n", binary);
  int intBinary = 0;
  int i = 0;
  int k = 0;
  while (i < 9) {
    if (i == 1) {
      // char b = "b";
      // intBinary = b - '0';
      // intBinary = (intBinary << 1) | ('0');
      // printf("%d  b    %b\n", i, intBinary);
      i++;
      continue;
    }
    else {
      // Bitwise from google:
      intBinary = (intBinary << 1) | (binary[k] - '0');
      // printf("%d  %c    %b\n", i, binary[k], intBinary);
    }
    k++;
    i++;
  }
  // prints decimal 4 or ~binary 100.
  // printf("intBinary: %b\n", intBinary);
  return intBinary;
}

// Convert int binary to char[] binary.
char* intBinary2Char(int zeros, int binary) {

  // answer = zeros + binary
  printf("intBinary2Char: %d  %d\n", zeros, binary);
  char *charBinary;

  return charBinary;

}

char* binaryAddition(char binaryOne[], char binaryTwo[], int i) {
  /*
  // Internet example with bitwise operations.
  int binaryOne1 = 0b0000001;
  int binaryTwo2 = 0b0000011;
  while (binaryTwo2 != 0) {
    int carry = binaryOne1 & binaryTwo2;  // Finds the carry.
    binaryOne1 = binaryOne1 ^ binaryTwo2; // Adds the bits without the carry.
    binaryTwo2 = carry << 1;              // Shifts the carry left.
  }
  printf("binaryOne1 plus binaryTwo2 = %d\n", binaryOne1);
  */
  int carry = 0;
  char *binarySum = malloc(9 * sizeof(char));
  strcpy(binarySum, "aaaaaaaa");

  // Allocates memory that is later deallocated with free().
  // The length of the binary characters (1 or 0) depends on 32 or 64 bit OS (aarch64).
  int k = 7;
  // i is binaryLength (n + 1).
  while (i > 0) {
    int j = i - 1;
    if (j == 1) {
      i--;
      continue;
    }
    // Convert char arrays to int for addition.
    // Moving bits on hardware instead of 1 byte (8 bits) for each character.
    int binaryOne3 = binaryOne[j] - '0'; // " -'0' " ascii ordering
    int binaryTwo3 = binaryTwo[j] - '0'; // prevents scaling.
    int binaryAdd = binaryOne3 + binaryTwo3;
    // Convert int back to char[].
    // Calculates the carry.
    if (binaryAdd == 1 && carry == 0) {
      binarySum[k] = binaryAdd + '0';
      carry = 0;
    }
    else if (binaryAdd == 0 && carry == 1) {
      binaryAdd = 1;
      binarySum[k] = binaryAdd + '0';
      carry = 0;
    }
    else if (binaryAdd == 1 && carry == 1) {
      binaryAdd = 0;
      binarySum[k] = binaryAdd + '0';
      carry = 1;
    }
    else if (binaryAdd == 0 && carry == 0) {
      binarySum[k] = binaryAdd + '0';
      carry = 0;
    }
    else if (binaryAdd == 2 && carry == 0) {
      binaryAdd = 0;
      binarySum[k] = binaryAdd + '0';
      carry = 1;
    }
    else if (binaryAdd == 2 && carry == 1) {
      binaryAdd = 1;
      binarySum[k] = binaryAdd + '0';
      carry = 1;
    }
    // printf("%d  %d  %d  %d  %d  %d    %d        %s\n", i, j, k, binaryOne3, binaryTwo3, carry, binaryAdd, binarySum);
    k--;
    i--;
  }
  // printf("Binarysum %s\n", binarySum);
  return binarySum;
}

// Inputs int decimal, converts as int binary, outputs char array[] binary
// for binaryAddition. char * binaryFormat(int integerOne, binaryLength);
int binaryFormat(int integerOne, int binaryLength){
  struct decimal2Binary intBinary = values(integerOne, binaryLength);
  printf("struct: %d  %d\n", intBinary.one, intBinary.two);
  // Convert 'binary' to char[] for 'binaryAddition()'.
  char *binary = intBinary2Char(intBinary.one, intBinary.two); // outputs: int intBinaryOne = 0b0000001;
  return intBinary.two; // returns char binaryOne[] = "0b0000001";
}

// Convert binary to decimal int.
int binary2Decimal(int binary) {

  int decimal;

  return decimal;
}

int main() {
  // Input decimal int, output binary.
  int integerOne = 4;
  int integerTwo = 3;
  // 8 bit binary (n + 1) to include the 'b' prefix. 'const' might break other libraries.
  int binaryLength = 9;
  char binaryOne[] = "0b0000001";
  char binaryTwo[] = "0b0000011";
  int binaryOneFoo = binaryFormat(integerOne, binaryLength); // (binaryOne)
  int binaryTwoFoo = binaryFormat(integerTwo, binaryLength); // (binaryTwo)
  // int binaryTwoFoo = binaryFormat(integerTwo, binaryLength); // (binaryTwo)
  // Uses malloc() and free().
  char *binaryAdd = binaryAddition(binaryOne, binaryTwo, binaryLength);
  int intBinaryAdd = charBinary2Int(binaryAdd, binaryLength);
  // int binary2Decimal(intBinaryAdd, binaryLength);
  free(binaryAdd);
  return 0;
}
