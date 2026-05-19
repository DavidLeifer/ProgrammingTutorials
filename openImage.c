#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
Todo -1: Download two images from internet. /\
Todo 0: Open a jpeg image.
        a.) Find byte size. fopen -> fread -> while
            i.) Binary addition calculator.
            ii.) Binary to decimal converter.
        b.) Read color table attributes.
        c.) Huffman decoding/encoding.

Todo 1: Clip a jpeg image.
Todo 2: Insert image into another image.


Notes

gcc openImage.c -o openImage && ./openImage

BMP
https://github.com/urossss/Image-Processing/blob/master/helper_functions.c

JPEG in Python
https://yasoob.me/posts/understanding-and-writing-jpeg-decoder-in-python/#file-start--file-end
https://yasoob.me/images/decoding_jpeg/JPEGRGB_dissected.png

// image link https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fthf.bing.com%2Fth%2Fid%2FOIP.Ym5Xlh8ZQGpnhHE9EhugmQHaEK%3Fr%3D0%26cb%3Dthfc1%26pid%3DApi&f=1&ipt=f85c9e9f6b5610a46ea4a3b12e326690a94b30a6d8e3ba38560ef3caa0340dad
// 2200 x 1238 or 474 x 266
*/


int binaryAddition(char binaryOne[], char binaryTwo[]) {
  // C int uses less memory than the character arrays (4 vs 8)
  // 32    vs  16    bit operating system (aarch64) int uses
  // 4     vs  2     bytes
  // +-2m  vs  +-32k numbers)
  // C has built in functions for lower memory binary addition.
  // Internet example uses bitwise operations similar to
  // Assembly AND, XOR, Left Shift:
  int binaryOne1 = 0b0000001;
  int binaryTwo2 = 0b0000011;
  while (binaryTwo2 != 0) {
    int carry = binaryOne1 & binaryTwo2;  // Finds the carry.
    binaryOne1 = binaryOne1 ^ binaryTwo2; // Adds the bits without the carry.
    binaryTwo2 = carry << 1;              // Shifts the carry left.
  }
  printf("binaryOne1 plus binaryTwo2 = %d\n", binaryOne1);
  // Using character arrays and more memory.
  // size_t i = sizeof(binaryOne) / sizeof(binaryOne[0]);
  // Largest unsigned 64 bit number is 18,446,744,073,709,551,615 or 0xFFFFFFFFFFFFFFFF
  // 1111111111111111111111111111111111111111111111111111111111111111
  // 64 digits
  int carry = 0;
  char binarySum[8] = "aaaaaaaa";
  // The length of the binary characters (1 or 0) depends on 32 or 64 bit OS (aarch64).
  int i = 9;
  int k = 7;
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
  printf("Binarysum %s\n", binarySum);
  return 0;
}

void fileOpen(char *path) {
  printf("jpeg path: %s\n", path);
  FILE *image;
  image = fopen(path, "rb");
  // int height = 1238; (from duckduckgo)
  // int width = 2200;
  // int height = 266;
  // int width = 474;
  // int pixelCount = height * width;
  int  imageStart = 0xffd8; //  Start of Image
  int  colorTable = 0xffdb; //  Quantization Table
  int  header = 0xffe0;     //  Default Header

  // int imageMalloc = malloc(sizeof(image));
  // printf("malloc: %d\n", imageMalloc);
  int bytes = 1024;
  unsigned char buffer[bytes]; // char is one byte
  int unsignedChar = sizeof(unsigned char);
  size_t imageBytes;
  int i = 0;
  size_t elements = 0;
  while ((imageBytes = fread(buffer, unsignedChar, bytes, image)) > 0) {
    printf("line: %d   imageBytes: %b\n", i, imageBytes);
    //elements += imageBytes;
    i++;
  }
  // 10,000,000,000
  // printf("total: %s\n", elements);
  fclose(image);
}

int main() {
  char jpeg_name[] = "./test.jpg";
  // fileOpen(jpeg_name);
  char binaryOne[] = "0b0000001";
  char binaryTwo[] = "0b0000011";
  binaryAddition(binaryOne, binaryTwo);
  return 0;
}
