#include <stdlib.h>
#include "mintf.h"
#include <limits.h>

int main(int argc, char *argv[]) {

	// Test 00: empty test
	// Expect: ""
	
	// Test 01: empty string
	mintf("");
	// Expect: ""

	// Test 02: triple percent
	mintf("%%%\n");
	// Expect: "%%"

	// Test 03: string with single character
	mintf("?\n");
	// Expect: ?

	// Test 04: string with any number of characters
	mintf("Hello\n");
	// Expect: Hello
	
	// Test 05: single percent
    mintf("Your chance is %%70\n");
    // Expect: Your chance is %70

    // Test 06: no format displays itself
	mintf("Completed percent homework: %50\n");
	// Expect: Completed percent of homework: %50

	// Test 07: integer
	mintf("He is %d years old.\n", 19);
	// Expect: He is 19 years old.
	
	// Test 08: formatted string
	mintf("%s stole my book!\n", "Albert");
	// Expect: Albert stole my book!
	
    // Test 09: hexadecimal
	mintf("Hexadecimal of %d is %x.\n", 1400, 1400);
	// Expect: Hexadecimal of 1400 is 0x578.
	
	// Test 10: binary
	mintf("%d would be written as %b in binary.\n", 650, 650);
	// Expect: 650 would be written as 0b1010001010 in binary.
	
	// Test 11: excess parameters
	mintf("No excess parameters needed >> %d.\n", 6350, 6350, 6350);
	// Expect: No excess parameters needed >> 6350.

	// Test 12: negative integer
	mintf("%d is a negative value.\n", -7);
    // Expect: -7 is a negative value.

	// Test 13: currency
	mintf("It cost me %$\n", 500);
	// Expect: It cost me $5.00

	// Test 14: currency & negative integer
	mintf("Your new balance is %$\n", -5600);
	// Expect: Your new balance is -$56.00
	
	// Test 15: currency & negative integer as INT_MIN
	mintf("Your new balance is %$\n", INT_MIN);
	// Expect: Your new balance is -$21474836.48

    // Test 16: hexadecimal INT_MAX & INT_MIN
	mintf("Hexadecimal of %d is %x and %d is %x.\n", INT_MAX, INT_MAX, INT_MIN, INT_MIN);
	// Expect: Hexadecimal of 2147483647 is 0x7fffffff and -2147483648 is -0x80000000.

	// Test 17: negative dollar
	mintf("%$\n", -3);
	// Expect: -$0.03
	
	// Test 18: one digit currency.
	mintf("%$\n", 1);
	// Expect: $0.01

	// Test 19: one digit decimal integer when % 100.
	mintf("%$\n", 1002);
	// Expect: $10.02

	return EXIT_SUCCESS;
}
