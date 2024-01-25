#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>

#include "stack.h"
#include "defs.h"

int generate_digit();

int generate_tft(); 

int generate_quarter();

int generate_final();

void remove_whitespace(char* string, bool* error);

void check_numbers(char* string, int* numbers, bool* error);

bool find(int number, int* numbers);

void infix_to_postfix(struct Stack* stack, char* buffer);

int precedence(char operation);

#endif