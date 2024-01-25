#ifndef STACK_H
#define STACK_H

#include "node.h"

struct Stack{
    struct Node* m_Top;
    unsigned int m_Size;
};

void create_stack(struct Stack* stack);

void push(struct Stack* stack, int element);

int pop(struct Stack* stack);

void empty(struct Stack* stack);

int evaluate_postfix(struct Stack* stack, char* expression, int* numbers, int* error);

int top(struct Stack* stack);

#endif