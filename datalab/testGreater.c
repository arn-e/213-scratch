#include <stdio.h>
#include <stdlib.h>

void printbits(unsigned long int v) {
  int i;

  for(i = 31; i >= 0; i--) putchar('0' + ((v >> i) & 1));
  printf("\n");
}



int isGreater(int x, int y) {
	// Boolean value indicating sign of x
	// 1 = Negative
	// 0 = Non-Negative

	int sign_x = x >> 31;
	// printbits(sign_x);
	// Boolean value indicating sign of y
	// 1 = Negative
	// 0 = Non-Negative
	int sign_y = y >> 31;
	// printbits(sign_y);
	int i = -5;
	i = ~i;
	// printbits(i);
	// if the signs are equal, then
	// if x is larger, sign bit of (~y + x) is 0
	// if y is larger, sign bit of (~y + x) is 1
	int a = sign_x ^ sign_y;
	// printbits(a);
	a = !a;
	// a is set to 1 if the signs match, and 0 if they don't
	// 
	printbits(a);


	// b 
	int b = ~y + x;
	// printbits(b);
	b = b >> 31;
	printbits(b);

	int equal = a & b;
	printbits(equal);

	// if signs are not equal, these principles are reversed.
	int notEqual = sign_x & !sign_y;
	// printbits(notEqual);

	// this | returns 0 when it is x is greater, so you have to negate it.
	int res = !(equal | notEqual);
	printf("%i\n", res);
	return !( equal | notEqual);
}

int main(int argv, char *argc[]){
	int a = 777;
	int b = -776;
	isGreater(a,b);
}



int isGreater2(int x, int y) {
	int res;
	int y_sign;
	int x_sign;
	int res_sign;
	int res_is_zero;
	int rval;
	int t1;
	int t2;

	// x - y
        res = x + (~y + 1);//x-y
	// printbits(res);
	// getting the signs?
	// if x is positive, the sign bit will be 0
	// if x is negative, the sign bit will be 1 (and the right shift)
	// will cause the entire word to be filled with 1's, with the exception
	// of the last bit
        x_sign = (x >> 31);
	//printbits(x_sign);
	x_sign = x_sign & 0x00000001;
	//printbits(x_sign);
        y_sign = (y >> 31);
	//printbits(y_sign);
	y_sign = y_sign & 0x00000001;
	//printbits(y_sign);
	
	// same principle, gets the sign of a-b	
        res_sign = (res >> 31) & 0x00000001;
	// res_is_zero is set to 1 if zero, 0 if not
        res_is_zero = res ^ 0x0;
	//printbits(res_is_zero);
	res_is_zero = !res_is_zero;
	//printbits(res_is_zero);
	res_is_zero = !res_is_zero;
	//printbits(res_is_zero);
	
	// x_sign ^ y_sign will return 0 if the signs match, 1 otherwise
	int matching_signs = x_sign ^ y_sign;
	// printbits(matching_signs);	
	// matching_signs is now set to 1 if the signs match, 0 otherwise
	matching_signs = !matching_signs;
	// printbits(matching_signs);
	// res_is_zero will now be set to 1 if the result is 0, 1 if not
	res_is_zero = !res_is_zero;
	printbits(res_is_zero);
	res_sign = !res_sign;
	printbits(res_sign);

        rval = ((matching_signs & res_is_zero) & res_sign) | ((x_sign ^ y_sign) & y_sign);
	printf("%i\n", rval);
	return rval;

}
