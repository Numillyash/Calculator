//
// Created by German Fidarov on 21.11.2021.
//

#ifndef LCALC_STACK_H
#define LCALC_STACK_H

#include "stdlib.h"
#include "structure.h"

// Data structure to represent a stack_s
struct stack
{
    int maxsize;    // define max capacity of the stack_s
    int top;
    number *items;
};

// Utility function to initialize the stack_s
struct stack *newStack(int capacity)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));

    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (number*)malloc(20001 * capacity); // because of 2500 signs restriction

    return pt;
}

// Utility function to return the size of the stack_s
int size(struct stack *pt) {
    return pt->top + 1;
}

// Utility function to check if the stack_s is empty or not
int isEmpty(struct stack *pt) {
    return pt->top == -1;                   // or return size(pt) == 0;
}

// Utility function to check if the stack_s is full or not
int isFull(struct stack *pt) {
    return pt->top == pt->maxsize - 1;      // or return size(pt) == pt->maxsize;
}

// Utility function to add an element `x` to the stack_s
void push(struct stack *pt, number x)
{
    // check if the stack_s is already full. Then inserting an element would
    // lead to stack_s overflow
    if (isFull(pt))
    {
        printf("Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    // add an element and increment the top's index
    pt->items[++pt->top] = x;
}

// Utility function to return the top element of the stack_s
number peek(struct stack *pt)
{
    // check for an empty stack_s
    if (!isEmpty(pt)) {
        return pt->items[pt->top];
    }
    else {
        return empty();
    }
}

// Utility function to pop a top element from the stack_s
number pop(struct stack *pt)
{
    // check for stack_s underflow
    if (isEmpty(pt))
    {
//        printf("Underflow\nProgram Terminated\n");
//        exit(EXIT_FAILURE);
        return empty();
    }

    // decrement stack_s size by 1 and (optionally) return the popped element
    return pt->items[pt->top--];
}

#endif //LCALC_STACK_H
