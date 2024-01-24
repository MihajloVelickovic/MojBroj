#include <stdlib.h>
#include <string.h>

#include "func.h"
#include "defs.h"

int generate_digit(){
    return rand() % 9 + 1;
}

int generate_tft(){
    return ((rand() % 3) + 2) * 5;
}

int generate_quarter(){
    return ((rand() % 4) + 1) * 25;
}

int generate_final(){
    return rand() % 999 + 1;
}

void remove_whitespace(char* string){    

    int size = 0;
    while(string[size] != '\0')
        ++size;
    
    int i=0, j;

    while(string[i] != '\0'){
        j = i;
        while(string[i] == ' ' && string[i] !='\0')
            ++i;

        for(int k=j, l=i; l<=size; ++l,++k)
            string[k] = string[l];       

        size -= (i-j); 

        while(string[i] != ' ' && string[i] != '\0')
            ++i;        
    }

}

void infix_to_postfix(struct Stack* stack, char* string){
    
    empty(stack);

    char postfix[MAX_EXPRESSION_SIZE];

    strcpy(postfix, "");

    int i=0;

    while(string[i] != '\0'){
        
        if(string[i] != '+' && string[i] != '-' && string[i] != '*' && string[i] != '/' && string[i] != '('){
            strncat(postfix, &string[i], 1);
        }

        else if(string[i] == ')'){
            char op;
            while((op = (char)pop(stack)) != '('){
                strncat(postfix, &op, 1);
            }
        }

        else{
            strcat(postfix, " ");
            while(stack->m_Size != 0 && precedence((char)top(stack)) >= precedence(string[i])){
                char sign = (char)pop(stack);
                strncat(postfix, &sign, 1);
            }
            push(stack, string[i]);
        }

        ++i;
        
    }

    while(stack->m_Size != 0){
        char sign = (char)pop(stack);
        strncat(postfix, &sign, 1);
    }

    strcpy(string, postfix);

}


int precedence(char operation){
    switch(operation){
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return 0;
    }
}