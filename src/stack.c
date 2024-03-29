#include <stdlib.h>

#include "stack.h"
#include "func.h"

void create_stack(struct Stack* stack){
    stack->m_Top = NULL;
    stack->m_Size = 0;
}

void push(struct Stack* stack, int element){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    create_node(new_node, element, stack->m_Top);
    stack->m_Top = new_node; 
    ++stack->m_Size;
}

int pop(struct Stack* stack){
   
    struct Node* top_node = stack->m_Top;
    int top_value = top_node->m_Value;
    stack->m_Top = top_node->m_Next;
    free(top_node);
    --stack->m_Size;
    return top_value;

}

void empty(struct Stack* stack){
    while(stack->m_Size != 0)
        pop(stack);
}

int top(struct Stack* stack){
    return stack->m_Top->m_Value;
}

/**
 * @param stack Helper stack
 * @param expression Postfix expression
 * @param numbers An array of available numbers for the expression
 * @param error 0 - Success, -1 Unavailable num, -2 Indivisible nums, -3 /0
 * @return Value of postfix expression
*/
int evaluate_postfix(struct Stack* stack, char* expression, int* numbers, int* error){
    
    *error = 0;
    empty(stack);
    int i;
    struct Stack helper;
    create_stack(&helper);

    int used_numbers[SIZE-1];
    for(i = 0; i<SIZE-1; ++i)
        used_numbers[i] = numbers[i];
    
    int used_counter = SIZE-1;

    int multiplier, number;

    bool operator = false;

    for(i = 0; expression[i] != '\0'; ++i){

        multiplier = 1;
        if(expression[i] >= 48 && expression[i] <= 57){
            push(&helper, expression[i] - 48);
            operator = false;
        }

        else if(expression[i] == ' ' && operator == false){
            number = 0;
            while(helper.m_Size != 0){
                number += pop(&helper) * multiplier;
                multiplier *= 10;
            }

            int index;

            if((index = find(number, used_numbers, used_counter)) == -1){
                *error = -1;
                return number;
            }

            for(int j = index; j<used_counter-1; ++j)
                used_numbers[j] = used_numbers[j+1];
            
            --used_counter;

            push(stack, number);
        
        }

        else{

            if(operator){
                operator = false;
                continue;
            }

            int first = pop(stack);
            int second = pop(stack);

            operator = true;

            switch (expression[i]){
                case '+':
                    push(stack, first + second);
                    break;
                case '-':
                    push(stack, second - first);
                    break;
                case '*':
                    push(stack, first * second);
                    break;
                case '/':
                    if(first == 0){
                        *error = -3;
                        return -1;
                    }
                    if(second % first != 0){
                        *error = -2;
                        return -1;
                    }
                    push(stack, second / first);
                    break;
            }
        }
    }

    number = 0, multiplier = 1;
    if(stack->m_Size == 0){
        if(helper.m_Size != 0){
            while(helper.m_Size != 0){
                number += pop(&helper) * multiplier;
                multiplier *= 10;
            }
            push(stack, number);
        }

    }
    int value = pop(stack);
    return value;

}
