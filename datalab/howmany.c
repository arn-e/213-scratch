#include <stdio.h>
#include <stdlib.h>

void printbits(unsigned long int v) {
  int i;

  for(i = 31; i >= 0; i--) putchar('0' + ((v >> i) & 1));
  printf("\n");
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits2(int x) {
  int temp, mask1, mask2, mask4, mask8, mask16;
  mask1 = 0x55;
  mask1 += mask1 << 8;
  mask1 += mask1 << 16;
  // printbits(mask1);
 
  mask2 = 0x33;
  mask2 += mask2 << 8;
  mask2 += mask2 << 16;
  // printbits(mask2);
 
  mask4 = 0x0f;
  mask4 += mask4 << 8;
  mask4 += mask4 << 16;
  // printbits(mask4);
 
  temp = 0xff;
  mask8 = temp + (temp << 16);
  mask16 = temp + (temp << 8);
  // printbits(mask8);
  // printbits(mask16); 
  int bar = x >> 31;
  // printbits(bar);
  int baz = ~x;
  // printbits(baz);
  // int foo = x >> 31;
  x = x ^ (x >> 31);
  x|=(x>>1);
  x|=(x>>2);
  x|=(x>>4);
  x|=(x>>8);
  x|=(x>>16);
  printbits(x);
  printf("%i\n", x);
  printf("\n");
  int a, b;    

  printbits(mask1);
  a = x & mask1;
  printbits(a);
  printf("%i\n", a);
  b = (x >> 1) & mask1;
  printbits(b);
  printf("%i\n", b);
  x = a + b;
  printbits(x);
  printf("%i\n", x);
  printf("\n");
  // x = (x & mask1) + ((x >> 1) & mask1);
  // printbits(x);

  printbits(mask2);
  a = x & mask2;
  printbits(a);
  printf("%i\n", a);
  b = (x >> 2) & mask2;
  printbits(b);
  printf("%i\n", b);
  x = a + b;// x = (x & mask2) + ((x >> 2) & mask2);
  printbits(x);
  printf("%i\n", x);
  printf("\n");
  // printbits(x);

  printbits(mask4);
  a = x & mask4;
  printbits(a);
  printf("%i\n", a);
  b = (x >> 4) & mask4;
  printbits(b);
  printf("%i\n", b);
  x = a + b;// x = (x & mask4) + ((x >> 4) & mask4);
  printbits(x);
  printf("%i\n", x);
  printf("\n");
  // printbits(x);

  printbits(mask8);
  a = x & mask8;
  printbits(a);
  b = (x >> 8) & mask8;
  printbits(b);
  x = a + b;// x = (x & mask8) + ((x >> 8) & mask8);
  printbits(x);
  printf("%i\n", x);
  printf("\n");
  // printbits(x);

  printbits(mask16);
  a = x & mask16;
  printbits(a);
  b = (x >> 16) & mask1;
  printbits(b);
  x = a + b;// x = (x & mask16) + ((x >> 16) & mask16);
  printbits(x);
  printf("\n");
  // printbits(x);

  int res = x + 1;
  printf("%i\n\n", res);
  return res;
}
// int howManyBits(int x) 
// {
//    int sign = (x>>31) & 1;
//    int signChain =~sign+1;
//    int placeHolder = 0; /*throwaway variable for various operations*/
//    int count = 2; /*counter to increment to count the bits*/
//    int copy = x; /*to be used for checking if power of 2*/
//    int copy2 = x; /*to be used for checking zero*/
//    int tminCheck =  x ^ (1 << 31);
//    tminCheck = !tminCheck;
//    tminCheck = ~tminCheck+1; /*all ones if x was tmin*/

//    x = (x & ~signChain) | ((~x +1) & signChain);/*now a positive value*/
//    x = x + ~0;
//    x = (x | x >> 1);
//    x = (x | x >> 2);
//    x = (x | x >> 4);
//    x = (x | x >> 8);
//    x = (x | x >> 16);
//    x = (x + 1); /*x is rounded up to the next power of 2*/
//    printbits(x);

//    /*the following chunks of code follow an algorithm that
//      does five different checks, incrementing the counter
//      for each check so that the result is the bit position
//      of the rounded up value of x*/
//    int a;
//    int b;
//    int c;
//    int d;     
//    int e;

//    a = 0xFF << 8;
//    printbits(a);
//    printf("%i\n", a);
//    b = 0xFF | a;
//    printbits(b);
//    printf("%i\n", b);   
//    c = x & b;
//    printbits(c);
//    printf("%i\n", c); 
//    d = ~c + 1;
//    printbits(d);
//    printf("%i\n", d); 

//    placeHolder = !(x & (0xFF | 0xFF << 8));
//    placeHolder = ~placeHolder+1; 
//    count += (placeHolder & 16);
//    printf("%i\n", count);

//    placeHolder = !(x & (0xFF | 0xFF << 16));
//    placeHolder = ~placeHolder + 1;
//    count += (placeHolder & 8);
//    printf("%i\n", count);

//    placeHolder = 0x0F | 0x0F <<8;
//    placeHolder = placeHolder | placeHolder <<16;
//    placeHolder = !(x & placeHolder);
//    placeHolder = ~placeHolder+1;  
//    count += (placeHolder & 4);
//    printf("%i\n", count);

//    placeHolder = 0x33 | 0x33 << 8;
//    placeHolder = placeHolder | placeHolder << 16;
//    placeHolder = !(x & placeHolder);
//    placeHolder = ~placeHolder+1;
//    count += (placeHolder & 2);
//    printf("%i\n", count);

//    placeHolder = 0x55 | 0x55 << 8;
//    placeHolder = placeHolder | placeHolder << 16;
//    placeHolder = !(x & placeHolder);
//    placeHolder = ~placeHolder+1;
//    count += (placeHolder & 1);
//    printf("%i\n", count);

//    /*determines if x is 0. if so, you want to return 1.*/
//    copy2 = !copy2;
//    copy2 = ~copy2+1;   

//    count += ~((tminCheck)&1);

//    /*add one to the count if x is a power of 2*/
//    copy = copy & (copy+~0);
//    count += !copy;
//    int res = (count & ~copy2) | (copy2 & 1);
//    printf("%i\n", res);
//    return res;
// }
  
int howManyBits(int x) {
    // initializing our valiant counter, i
    int i = 1;
    int tmax;
    // first, we convert negative values to positive
    // specifically, if x is negative, x = ~x
    // we only care about the most significant non-zero bit

    x = x ^ (x >> 31);
    x|=(x>>1);
    x|=(x>>2);
    x|=(x>>4);
    x|=(x>>8);
    x|=(x>>16);
    // x == 2^n - 1

    // create our tmax / 0xFFFFFFFF mask
    tmax = ~(1<<31);
    tmax = 0xFFFFFFFF;

    // continuously divide x by 2, each time
    // incrementing the counter
    
    x = tmax & x;
    i = i + (1 & x); 
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x); 
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    x = tmax & (x >> 1);
    i = i + (1 & x);
    printbits(x);

    printf("%i\n", i);

    return x;

} 
int main(int argv, char *argc[]){
    int x = 122342;
    int y = 5;
    int a = 0x80000000;
    int z = 0x7FFFFFFF;
    int b = 0;
    // int x = -5;
    // int x = 123;
    // int x = 0x7FFFFFFF; 
    // howManyBits(x);
    howManyBits(b);
    howManyBits2(b);
    // howManyBits(a);
    // howManyBits(z);
}


