#include <ctype.h>     // Include standard library for character handling functions
#include "calculator.h" // Include the header file for the calculator, which contains necessary declarations

// Function declarations for getting and un-getting characters
int getch(void);
void ungetch(int);

/* 
 * getOp: Get the next operator or numeric operand 
 * This function reads characters from the input to identify if they form an operator or a number.
 */
int getOp(char s[]) {
    int i, c;

    // Skip whitespace and tab characters
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0'; // Null-terminate the string with the first character

    // If the character is not a digit and not a decimal point, return it (it's an operator)
    if (!isdigit(c) && c != '.')
        return c;  // Return the character as an operator

    i = 0;

    // If the character is a digit, collect the integer part of the number
    if (isdigit(c)) 
        while (isdigit(s[++i] = c = getch()))
            ;

    // If the character is a decimal point, collect the fractional part of the number
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0'; // Null-terminate the string after the number

    // If we've read past the number, push the last character back to the input buffer
    if (c != EOF)
        ungetch(c);

    // Return a signal indicating that a number was found
    return NUMBER;
}
