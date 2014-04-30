#include <stdio.h>
#include <stdlib.h>


/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    // basic rules :
    // if x and y share a sign - no overflow
    // overflow occurs if :
    // x is negative, y is positive and the sign bit of the sum is 0 
    // x is positive, ys is negative and sign bit of the sum is 1

    int xSign;
    int ySign;
    int sum;
    int sumSign;
    int negY;

    // basic setup 
    negY = ~y + 1;
    sum = x + negY;

    xSign = x >> 31;
    ySign = y >> 31;
    sumSign = sum >> 31;
    // case 1 - x negative, y positive, sum positive
    int x1 = xSign ^ ySign; //eval to 1 if either x or y is negative
    printbits(x1);
    int x2 = xSign ^ sumSign; // eval to 1 if either x or sumsign is negative
    printbits(x2);
    int result = x1 & x2;
    printbits(result);

    result = !result;
    printf("%i\n", result);
    return result;
}

void printbits(unsigned long int v) {
  int i;

  for(i = 31; i >= 0; i--) putchar('0' + ((v >> i) & 1));
  printf("\n");
}

int main(int argv, char *argc[]){
    int a = 0x80000000;
    int b = -45;
    subOK(a,b);
}
