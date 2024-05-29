#include <ctype.h>       // Include ctype.h for isdigit() and isspace()
#include "calculator.h"  // Include calculator.h for necessary function declarations

// Function to convert a string representation of a floating-point number to a double
double asciiToFloat(char s[]) {
    double val, power;
    int i, sign;

    // Skip whitespace characters
    for (i = 0; isspace(s[i]); i++)
        ;

    // Determine the sign of the number
    sign = (s[i] == '-') ? -1 : 1;

    // If the number has a sign, move to the next character
    if (s[i] == '+' || s[i] == '-')
        i++;

    // Convert the integer part of the string to a double
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');  // Accumulate the digit into val

    // If there's a decimal point, skip it
    if (s[i] == '.')
        i++;

    // Convert the fractional part of the string to a double
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');  // Accumulate the digit into val
        power *= 10.0;                    // Adjust the power for the fractional digit
    }

    // Return the result after adjusting for the sign and the decimal place
    return sign * val / power;
}
