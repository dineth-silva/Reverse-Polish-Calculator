#include <stdio.h>
#include <ctype.h>

#define MAXOP 100    /* maximum size of the operand of operator */
#define NUMBER '0'   /* signal that a number was found */
#define MAXVAL 100   /* maximum depth of value stack */
#define BUFSIZE 100  /* buffer size for ungetch */

int getOp(char []);
void push(double);
double pop(void);
double asciiToFloat(char []);

/* Stack operations */
int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

/* Buffer for ungetch */
char buf[BUFSIZE];
int bufp = 0;

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack Underflow\n");
        return 0.0;
    }
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

double asciiToFloat(char s[]) {
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

int getOp(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

int main() {
    int type;
    double op2;
    char s[MAXOP];
    int error_flag = 0;

    printf("Enter the Polish Notation:\n");
    while ((type = getOp(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(asciiToFloat(s));
                break;
            case '+':
                if (sp < 2) {
                    printf("error: stack Underflow\n");
                    error_flag = 1;
                    break;
                }
                push(pop() + pop());
                break;
            case '*':
                if (sp < 2) {
                    printf("error: stack Underflow\n");
                    error_flag = 1;
                    break;
                }
                push(pop() * pop());
                break;
            case '-':
                if (sp < 2) {
                    printf("error: stack Underflow\n");
                    error_flag = 1;
                    break;
                }
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                if (sp < 2) {
                    printf("error: stack Underflow\n");
                    error_flag = 1;
                    break;
                }
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else {
                    printf("error: zero divisor!\n");
                    error_flag = 1;
                }
                break;
            case '=':
                // Ignore the '=' character
                break;
            case '\n':
                if (!error_flag) {
                    printf("Answer:\n\t%.2f\n", pop());
                }
                error_flag = 0;  // Reset error flag for next input
                printf("Enter the Polish Notation:\n");
                break;
            default:
                printf("error: Invalid input %s.\n", s);
                error_flag = 1;
                break;
        }
    }
    return 0;
}
