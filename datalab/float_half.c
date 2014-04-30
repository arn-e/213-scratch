#include <stdio.h>
#include <stdlib.h>

/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

void printbits(unsigned long int v) {
  int i;

  for(i = 31; i >= 0; i--) putchar('0' + ((v >> i) & 1));
  printf("\n");
}


unsigned float_half(unsigned uf) {

    unsigned res;
    int oddBits;
    int signPos;
    int exPos;
    int neg1;
    int fracPos;
    int sigFracBit;
    int sign;
    int expo;
    int frac;
    int isOdd;
    int dividedFrac;
    int isNaN;
    int roundFrac;
    int expoBit;
    int denorm;
    int smallNorm; 
    int exceptionCase;

    // define a few positional masks
    signPos = 1 << 31;
    fracPos = (1 << 23) - 1;
    exPos = ~(signPos | fracPos);
    neg1 = ~1 + 1;
    sigFracBit = 1 << 22;

    // capture relevant information from uf
    sign = signPos & uf;
    expo = exPos & uf;
    frac = fracPos & uf;
    oddBits = 3 & frac;

    // determine if the exponent bits are all 1's
    // set a flag indicating whether or not the current value is NaN
    if (expo == exPos){
        isNaN = 1; 
    } else {
        isNaN = 0;
    }

    // set a flag indicating whether or not the current value
    // is denormalized
    if (expo == 0){
        denorm = 1;
    } else {
        denorm = 0;
    }

    // 
    if (oddBits == 3){
        isOdd = 1;
    } else {
        isOdd = 0;
    }

    expoBit = expo >> 23;
    

    // store the least significant exponent bit

    if (expoBit == 1){
        smallNorm = 1;
    } else {
        smallNorm = 0;
    }

   // divide the frac, adjusting for rounding
    if ((frac == fracPos) && (smallNorm == 1)){
    dividedFrac = 0;
    exceptionCase = 1;
    } else {
        roundFrac = frac + isOdd;
        dividedFrac = roundFrac >> 1;
    } 

    // if NaN or infinity, return the input value
    if (isNaN == 1){
        res = uf;
    return res;
    }

    // if it's a denormalized value, we will divide the frac and
    // combine with the sign bit    

    if (denorm == 1){
        res = sign | dividedFrac;
        return res;
    } 

    // we have now determined that the value must be normalized
    // 2 conditions remain :
    // 1. small normalized value, that when divided will become denormalized
    // 2. normalized value that will lose an exponent power

    if (smallNorm == 1){
        if(exceptionCase == 1){
            res = sign | (sigFracBit << 1) | dividedFrac;
        }else {
            res = sign | sigFracBit | dividedFrac;
        } 
        // if the only exponent it is the least significant one
        // the value will need to transition from a denormalized to
        // a normalized one 
        printbits(res);
        printf("%i\n", res);
        return res;

    } else {
        // the value is normalized and will remain normalized
        // subtract 1 from the exponent and combine with sign & frac

        expo = expo - 1;
        expo = expo & exPos;

        res = sign | expo | frac;
        return res; 
    }

}


int main(int argv, char *argc[]){
    // unsigned f = 427;
    // unsigned f = 16777215;
    unsigned f = 16777215;
    // unsigned f = 0x000000;
    int foo = 8388608;
    float_half(foo);


}
