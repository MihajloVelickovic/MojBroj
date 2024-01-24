#include <stdlib.h>

#include "stack.h"

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

int evaluate_postfix(struct Stack* stack, char* expression, bool* error){
    
    empty(stack);
    int i;
    struct Stack helper;
    create_stack(&helper);

    for(i = 0; expression[i] != '\0'; ++i){

        int multiplier = 1;
        if(expression[i] >= 48 && expression[i] <= 57)
            push(&helper, expression[i] - 48);

        else if(expression[i] == ' '){
            int number = 0;
            while(helper.m_Size != 0){
                number += pop(&helper) * multiplier;
                multiplier *= 10;
            }
            push(stack, number);
        }

        else if(expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/')
            *error = true;
        
        else{

            int first = pop(stack);
            int second = pop(stack);

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
                    push(stack, second / first);
                    break;
            }
        }
    }

    *error = false;
    int value = pop(stack);
    return value;

}
