//
// Created by German Fidarov on 21.11.2021.
//

#ifndef LCALC_STACK_SIGNS_H
#define LCALC_STACK_SIGNS_H

#include "stdlib.h"

// Data structure to represent a stack_s
struct stack_s
{
    int maxsize;    // define max capacity of the stack_s
    int top;
    char *items;
};

// Utility function to initialize the stack_s
struct stack_s *newStackS(int capacity)
{
    struct stack_s *pt = (struct stack_s*)malloc(sizeof(struct stack_s));

    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (char *)malloc(8 * capacity); // because of 2500 signs restriction

    return pt;
}

// Utility function to return the size of the stack_s
int sizeS(struct stack_s *pt) {
    return pt->top + 1;
}

// Utility function to check if the stack_s is empty or not
int isEmptyS(struct stack_s *pt) {
    return pt->top == -1;                   // or return size(pt) == 0;
}

// Utility function to check if the stack_s is full or not
int isFullS(struct stack_s *pt) {
    return pt->top == pt->maxsize - 1;      // or return size(pt) == pt->maxsize;
}

// Utility function to add an element `x` to the stack_s
void pushS(struct stack_s *pt, char x)
{
    // check if the stack_s is already full. Then inserting an element would
    // lead to stack_s overflow
    if (isFullS(pt))
    {
        printf("Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    // add an element and increment the top's index
    pt->items[++pt->top] = x;
}

// Utility function to return the top element of the stack_s
char peekS(struct stack_s *pt)
{
    // check for an empty stack_s
    if (!isEmptyS(pt)) {
        return pt->items[pt->top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}

// Utility function to pop a top element from the stack_s
char popS(struct stack_s *pt)
{
    // check for stack_s underflow
    if (isEmptyS(pt))
    {
        printf("Underflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    // decrement stack_s size by 1 and (optionally) return the popped element
    return pt->items[pt->top--];
}

#endif //LCALC_STACK_SIGNS_H
