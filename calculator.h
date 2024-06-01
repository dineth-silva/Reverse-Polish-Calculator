#ifndef CALCULATOR_H
#define CALCULATOR_H

#define MAXOP 100    /* maximum size of the operand or operator */
#define NUMBER '0'   /* signal that a number was found */
#define MAXVAL 100   /* maximum depth of value stack */
#define BUFSIZE 100  /* buffer size for ungetch */

/* Function declarations */
int getOp(char []);
void push(double);
double pop(void);
double asciiToFloat(char []);
int getch(void);
void ungetch(int);

/* External variables */
extern int sp;             /* next free stack position */
extern double val[MAXVAL]; /* value stack */
extern char buf[BUFSIZE];  /* buffer for ungetch */
extern int bufp;           /* next free position in buffer */

#endif // CALCULATOR_H
