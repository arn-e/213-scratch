/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  // return 1431655765;
  int a = 0x55;
  int b = a << 8;
  int c = a + b;
  int d = c << 16;
  int e = c + d;
  return e;
}

/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  int result = x ^ y;
  result = !result;
  return result;

}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
 

int byteSwap(int x, int n, int m) {

    int swappedValues;
    int swappedPos;
    int nonSwappedPos;
    int nonSwappedValues;
    int result;

    // in a word, each 'position' is a group of 8, so we need to multiply the given position values (n, m)
    // by 8 to translate them to the byte unit of measure in a word
    // multiplication by 8 is a power of 2, so we can calculate our offset by shifting by 3
    // e.g. 2 => 0000 0010 => (shifted) => 0001 0000
    int shiftCount1 = n << 3;
    int shiftCount2 = m << 3;

    // moving a set of "full" bytes to byte positions 1 & 2
    int bytePos1 = 0xFF << shiftCount1;
    int bytePos2 = 0xFF << shiftCount2;

    // tagging the positions of the bytes to be swapped, using a full byte as tracing paper
    int swapVal1 = x & bytePos1;
    int swapVal2 = x & bytePos2;

    // isolating the bytes to be swapped, removing trailing 0's
    swapVal1 = swapVal1 >> shiftCount1;
    swapVal2 = swapVal2 >> shiftCount2;

    // getting rid of the flipped fits (1's) created by the right shift of a most significant 1
    swapVal1 = 0xFF & swapVal1;
    swapVal2 = 0xFF & swapVal2;

    // moving the isolated values to the position of the other, swapping their positions
    swapVal1 = swapVal1 << shiftCount2;
    swapVal2 = swapVal2 << shiftCount1;

    // getting the position of the non-swapped values
    swappedPos = bytePos1 | bytePos2;
    nonSwappedPos = ~swappedPos;

    // combining the repositioned values
    swappedValues = swapVal1 | swapVal2;

    // isolating the non-swapped values
    nonSwappedValues = nonSwappedPos & x;

    // combining the swapped & non swapped values to form voltron
    result = swappedValues | nonSwappedValues;
    return result;
}

/* rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */


int rotateRight(int x, int n) {

    int wordLen = 32;
    int negN;
    int neg1;
    int leftOffset;
    int rightOffset;
    int leftFill;
    int rightFill;
    int leftVal;
    int rightVal;
    int result; 
   
    // first, we need both the 2's complement of 1 and n : 
    // -1 = ~1 + 1; -n = ~n + 1
    negN = ~n + 1;
    neg1 = ~1 + 1;

    // next, we will isolate the values on the left to be shifted off, first by
    // populating the range specified by n with 1's

    // since we cannot use constants greater than 0xFF (e.g. no 0xFFFFFFFF << n)
    // we will need to again exploit a property of binary arithmetic  
    // 1 << n will always == (all preceding bits / bits of lower power) +1
    // e.g. 1000 == 0111 +1
    rightOffset = 1 << n;
    // rightOffset = rightOffset <<  1;

    // since we can't subtract, we need to to once again add a negative
    // in the same manner as above, we will take the 
    // 'create' by getting the 2's complement of 1 
    // now, we can subtract 1 from rightOffset 
    rightFill = rightOffset + neg1;
    
    // now we need to determine the inverse of the offset (n) 
    // in order to properly 0-out the values on the left hand side

    // since we cannot use subtraction (e.g. word length - n), 
    // we need to add 32 (word length)  to -n
    // since : 32 - n == -n + 32
    // then, add 32 to -n :
    leftOffset = wordLen + negN;

    // before we begin shifting the values in x, we need to be prepared to deal
    // with the 1's which may be created by the right shift of a most significant 
    // bit; therefore, we will isolate the section of bits that will need to be 
    // flipped to 0 (so that the rotated bits may then be safely inserted)  
    leftFill = rightFill << leftOffset;
    leftFill = ~leftFill;

    // by taking the intersection of leftFill & (x >> n), we are left with a value 
    // with n bits set to 0 on the 'left' side     
    rightVal = x >> n;
    rightVal = rightVal & leftFill; 

    // likewise, by taking the union of x and rightFill, we have now isolated the 
    // values to be rotated to the left  
    leftVal = x & rightFill;
    leftVal = leftVal << leftOffset;

    // finally, we take the union of the left & right values
    result = rightVal | leftVal;
    return result;
}

/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    int result;
    // basically propagating 1's across the entire word
    // if any are present
    // since a point of commonality between all non-zero
    // values is the existence of at least 1 bit set to 1

    // this is probably what the writeup would characterize
    // as a "grossly inefficient" solution...

    x = x | x << 1 | x >> 1;
    x = x | x << 2 | x >> 2;
    x = x | x << 4 | x >> 4;
    x = x | x << 8 | x >> 8;
    x = x | x << 16| x >> 16;

    result = x + 1;

    return result;
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
    // tmax is 0x7FFFFFFF, the inverse of which is
    // 0x80000000, which we can create by shifting 1 << 31
    int max = ~(1<<31);
    return max;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
    // first we shift x to the right, leaving 1 potentially
    // open bit, which will be filled in by the result of
    // !!x; if 0, the double logical negation will result in 0
    // else, it will result in 1
    // the right shift of a leading sign bit set to 1
    // will cause the entire word to == -2 | -1
    // filling it in will result in the value == -1
    // if positive, x >> 1 == (0 | 1)
    // if 0, filling it in with the union of !!x will
    // result in the value == 1
    int result = x >> 31;
    result = result | !!x;
    return result;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */

int isGreater(int x, int y){
    int ySign;
    int xSign;
    int sameSign;
    int signOfSum;
    int xLessEqual;
    int xNegative;
    int res;

    // store the sign bits for both x and y
    xSign = x >> 31;
    ySign = y >> 31;

    // the basic logic is as follows :
    // x can be < than y under 2 circumstances;
    // 1. x is negative and y is positive
    // 2. x and y are both positive, and x < y

    // first case :
    // determine if x is negative and y positive :
    xNegative = xSign & !ySign;

    // second case :
    // determine if x is less than or equal to y if :
    // x is positive and y is positive OR
    // x is negative and y is negative

    // in order for this to be the case, both of the following conditions
    // must be met :
    // 1. x and y share the same sign
    // 2. x - (y-1) < 0
    // we are subtracting (-y -1) from x instead of -y, since we
    // are not distinguishing equality from <
    sameSign = xSign ^ ySign;
    sameSign = !sameSign;

    signOfSum = ~y + x;
    signOfSum = signOfSum >> 31;

    xLessEqual = sameSign & signOfSum;

    // if either xNeg or lessEqual are true, x is either
    // less than or equal to y, in which case we return 0
    // otherwise, return 1
    res = xLessEqual | xNegative;
    res = !res;

    return res;
}

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
    int compXy;
    int compXsum;
    int result;
	
    // setup : creating our basic variables and getting the 
    // sign bits for x, y and the sum of x + -y
    negY = ~y + 1;
    sum = x + negY;

    xSign = x >> 31;
    ySign = y >> 31;
    sumSign = sum >> 31;

    // enforcing the logic outlined above 
    // e.g. the sign bits of x, y and sum(x,y) have to conform to
    // one of the following patterns if overflow is to occur:
    // 1,0,0
    // 0,1,1
    compXy = xSign ^ ySign; //eval to 1 if either x or y is negative
    compXsum = xSign ^ sumSign; // eval to 1 if either x or sumsign is negative
    result = compXy & compXsum; 

    result = !result;
    return result;
}



/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum possible value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {

  // setup
  int sum = x + y;
  int xSign = (x >> 31) & 1;
  int ySign = (y >> 31) & 1;
  int sumSign = (sum >> 31) & 1;

  int compSumX = sumSign ^ xSign;
  int compSumY = sumSign ^ ySign;
  // expectation : both comparisons need to be 1
  // in order for an overflow case to be true
  // e.g. either 1, 1, 0 or 0, 0, 1
  int overflowFlag = compSumX & compSumY; // xRes should be 1, if overflow

  // the overflow mask will either be -1, or 0x0
  int overflowMask = ~overflowFlag + 1; 

  //if overflow occurred, shifting 0x80000000 << 31
  //will evaluate to tmin, otherwise 0x0
  int tminOrZero = overflowMask << 31;

  // if overflow occurred, wipe the existing sum
  // either with 0's or 1's
  // 0 in the event of negative overflow
  // 1 in the event of positive overflow 
  int shiftLen = overflowMask & 31;
  int overflowOffset = sum >> shiftLen;

  // if overflow occurred, add tmax to the sum
  // if positive overflow : sum == -1, sum + tmin == tmax 
  // if negative overflow : sum == 0, sum + tmin == tmin
  int res = overflowOffset + tminOrZero;
  return res;

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

    // continuously divide x by 2, each time
    // incrementing the counter
    
    x = tmax & x;
    i = i + (1 & x); 

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x); 

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    x = tmax & (x >> 1);
    i = i + (1 & x);

    return i;

} 
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
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return 2;
}
