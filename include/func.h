#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>

#include "stack.h"
#include "defs.h"

int generate_digit();

int generate_tft(); 

int generate_quarter();

int generate_final();

int remove_whitespace(char* string);

int find(int number, int* numbers, int size);

void infix_to_postfix(struct Stack* stack, char* buffer);

int precedence(char operation);

int handle_finish();

#endif