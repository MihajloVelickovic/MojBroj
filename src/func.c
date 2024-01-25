#include <stdio.h>
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

int remove_whitespace(char* string){    

    int size = 0;
    while(string[size] != '\0'){
        if((string[size] < 48 || string[size] > 57) && string[size] != '+' &&
            string[size] != '-' && string[size] != '*' && string[size] != '/'&&
            string[size] != '(' && string[size] != ')' && string[size] != ' '){
                return -1;
            }
        else
            ++size;
    }
    
    int i=0, j;

    while(string[i] != '\0'){
     
        j = i;
        while(string[i] == ' ' && string[i] !='\0')
            ++i;

        if(i != j)
            for(int k=j, l=i; l<=size; ++l,++k)
                string[k] = string[l];       

        size -= (i-j); 

        i = j;

        while(string[i] != ' ' && string[i] != '\0')
            ++i;        
    }

    return 0;

}

int find(int number, int* numbers, int size){
    for(int i=0; i<size;++i)
        if(number == numbers[i])
            return i;
    return -1;
}

void infix_to_postfix(struct Stack* stack, char* string){
    
    empty(stack);

    char postfix[MAX_EXPRESSION_SIZE];

    strcpy(postfix, "");

    int i=0;

    while(string[i] != '\0'){
        
        if(string[i]    != '+' && string[i] != '-' && string[i] != '*' 
           && string[i] != '/' && string[i] != '(' && string[i] != ')')
            strncat(postfix, &string[i], 1);

        else if(string[i] == ')'){
            char op;
            while((op = (char)pop(stack)) != '('){
                strcat(postfix, " ");
                strncat(postfix, &op, 1);
            }
        }

        else{
            if(postfix[0] != '\0' && postfix[strlen(postfix)-1] != ' ')
                strcat(postfix, " ");
            while(stack->m_Size != 0 && (char)top(stack) != '(' && 
                  precedence((char)top(stack)) >= precedence(string[i])){
                    char sign = (char)pop(stack);
                    strncat(postfix, &sign, 1);
                    strcat(postfix, " ");
            }
            push(stack, string[i]);
        }

        ++i;
        
    }

    while(stack->m_Size != 0){
        strcat(postfix, " ");
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
        case '(':
            return 3;
        default:
            return 0;
    }
}

int handle_finish(){

    printf("Press any button (q to quit)!\n");
    char flush = getchar();
    char buff[MAX_EXPRESSION_SIZE];
    fgets(buff, MAX_EXPRESSION_SIZE, stdin);

    char input;
    if(buff[strlen(buff)-1] == '\n' && buff[0] != '\n')
        input = buff[strlen(buff)-2];
    else
        input = buff[strlen(buff)-1];

    if(input == 'q' || input == 'Q')
        return -1;

    system("clear");
    return 0;

}