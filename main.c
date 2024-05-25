#include <stdio.h>
#include "calculator.h"

int main() {
    int type;
    double op2;
    char s[MAXOP];

    printf("Please enter Polish Notation or ^d to quit.\n");
    while ((type = getOp(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(asciiToFloat(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor!\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            printf("Please enter Polish Notation or ^d to quit.\n");
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;   
