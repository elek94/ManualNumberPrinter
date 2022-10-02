#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

void _display_reverse(int,unsigned int, unsigned int, int); // display_reverse declared.


// define mintf(...) variadic function as the implementation function of hw05.
void mintf(const char *format, ...) {

    va_list list_args;
	va_start(list_args, format);
    const char* one_c_or_s = format; // one char or strings are our format variable.

	for(int i = 0; one_c_or_s[i] != '\0'; i++) {
		if((one_c_or_s[i] == '%') && (one_c_or_s[i + 1] == one_c_or_s[i])) { // display characters when % sign repeatedly exists and even number of times.
			fputc(one_c_or_s[i], stdout);
			i += 1;
		}
		else if((one_c_or_s[i] == '%') && (one_c_or_s[i + 1] == 'd')) { // decimal
			int nxt_dec = va_arg(list_args, int);   // argument received.
			print_integer(nxt_dec, 10, "");         // call print_integer to display decimals.
			i += 1; // accelerate i count to neglect specifier display.
		}
		else if((one_c_or_s[i] == '%') && (one_c_or_s[i + 1] == 's')) { // string	
			char* nxt_strng = va_arg(list_args, char*);
			for(int a = 0; nxt_strng[a] != '\0'; a++) {   // display each character consecutively for string argument.
				fputc(nxt_strng[a], stdout);
			}
			i += 1; 
		}	
		else if((one_c_or_s[i] == '%') && (one_c_or_s[i + 1] == 'x')) { // hexa	
			int nxt_hex = va_arg(list_args, int);
			print_integer(nxt_hex, 16, "0x"); // call print_integer to display hexadecimal(16 base case) with "0x" prefix.
			i += 1;
		}
		else if((one_c_or_s[i] == '%') && (one_c_or_s[i + 1] == 'b')) { // binary	
			int nxt_bin = va_arg(list_args, int);
			print_integer(nxt_bin, 2, "0b");      // call print_integer to display with binary(2 base case) with "0b" prefix.
			i += 1; 
		}
		else if((one_c_or_s[i] == '%') && (one_c_or_s[i + 1] == '$')) { // dollar currency: $	
			
			int nxt_curr = va_arg(list_args, int);
			int actual_curr = nxt_curr / 100; // get the number before decimal points.
			if ((nxt_curr < 0) && (actual_curr == 0)) {
				print_integer(actual_curr, 10, "-$");
			}
			else {	
				print_integer(actual_curr, 10, "$");
			}
			
			if(nxt_curr % 100 != 0) {	// if two decimal points aren't double 0.
				if (nxt_curr > 0) {
					if (nxt_curr % 100 < 10) {
						print_integer(nxt_curr % 100, 10, ".0");   // call the print_integer casually for two decimal point and less than 10.
					}
					else {
						print_integer(nxt_curr % 100, 10, "."); 
					}
				}
				else {
					if (-1*(nxt_curr % 100) < 10) {
						print_integer(-1*(nxt_curr % 100), 10, ".0");	// if the value of argument negative and decimal less than 10.
					}
					else {
						print_integer(-1*(nxt_curr % 100), 10, ".");	// if the value of argument negative.
					}
				}
			}
			else {
				if(nxt_curr > 0) {
					print_integer((nxt_curr / 10) % 10, 10, ".");  // get the first digit of decimal point.
					print_integer(nxt_curr % 10, 10, "");          // get the last digit of decimal point.
				}
				else {
					print_integer(-1*((nxt_curr / 10) % 10), 10, ".");	// if the value of argument negative.
					print_integer(-1*(nxt_curr % 10), 10, ""); 
				}
			}
			i += 1;
		}
		else if((i > 0) && (one_c_or_s[i] == '%') && (one_c_or_s[i + 1] != one_c_or_s[i])) { // display % character when % sign is not consecutive.
			fputc(one_c_or_s[i], stdout);
		}
		else {   //  >>  if and only casual characters entered as format.
			fputc(one_c_or_s[i], stdout);
		}
	}
}


// print_integer function.
void print_integer(int n, int radix, char* prefix) {
    
    unsigned int n_abs = -n; // initially declare unsigned int n_abs to negative n to make absolute value and prevent overflow.

    if(n < 0) {
		fputc('-', stdout); // if negative display minus since it already converted absolute value in declaration.
	}
	else {
		n_abs *= -1; // if positive multiply again by -1 to make it positive again.
    }
    
	// loop for prefix.
    for(int idx_in_s = 0; prefix[idx_in_s] != '\0'; idx_in_s++) {
		fputc(prefix[idx_in_s], stdout);
	}
    
	int counter = 0;
    unsigned int old_n = n_abs; // initialize and store very first n value before too late.

	if(n_abs == 0) {
		counter += 1; // if n_abs already 0, one display would be enough.
	}
    
	while(n_abs != 0) {
		
		n_abs /= radix; // divide very first n value by radix until 0.
  
		counter += 1; // count hoe many time divided until 0.

	}
    
	_display_reverse(radix, old_n, n_abs, counter);

}

// helper display_reverse function for print_integer function.
void _display_reverse(int radix,unsigned int old_n, unsigned int n_abs, int counter) {
	
	int remainder = 0; // final requested base version.
	long int rad_div = 1; // declare rad div to gather all divisors of n. long int type only solved INT_MAX & INT_MIN.
	int i = counter; // define i for counter for secon use.
	double f; // declare double f to find the last value after last divison by radix.
	
	for(; i > 0; i--) {
		rad_div *= radix; // multiply by radix counter times to find total divisor.
	}

	while(counter > 0) {

		f = (double)old_n / rad_div; // get the last value in one step like all divisons implemented.
		n_abs = f * radix; // now start multipying last value n by radix again to go down to up instead of up to down.
		remainder = n_abs % radix; // modulo of down to up values helps us to display characters from down to up.

		if(remainder >= 0 && remainder <= 9) {
			fputc('0' + remainder, stdout);
		}
		else {
			fputc('a'+ (remainder - 10), stdout);
		}

		rad_div /= radix; // decrease the large divisor each time with dividing it by radix again.
		counter -= 1; // remember these all happens number of digit times, so decrement loop's counter each time.

    }
}
