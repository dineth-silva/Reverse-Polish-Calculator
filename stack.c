#include <stdio.h>
#include "calculator.h"

int sp = 0;              /* next free stack position */
double val[MAXVAL];      /* value stack */

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
        printf("error: stack underflow\n");
        return 0.0;
    }
}
