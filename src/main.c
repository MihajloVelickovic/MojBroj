#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "func.h"
#include "stack.h"

int main(){

    srand(time(NULL));

    int numbers[SIZE], i;
        
    for(i=0; i<TFT; ++i)
        numbers[i] = generate_digit();

    numbers[TFT] = generate_tft();
    numbers[QUARTER] = generate_quarter();    
    numbers[FINAL] = generate_final();

    for(i=0; i<SIZE; ++i){
        getchar();
        printf("%d", numbers[i]);
    }

    printf("\n\n");

    char buffer[MAX_EXPRESSION_SIZE];
    fgets(buffer, MAX_EXPRESSION_SIZE, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    bool error;
    remove_whitespace(buffer, &error);
    if(error){
        fprintf(stderr, "Invalid character inside expression!\n");
        return EXIT_FAILURE;
    }
    
    struct Stack stack;
    create_stack(&stack);

    infix_to_postfix(&stack, buffer);

    int user_value = evaluate_postfix(&stack, buffer, numbers, &error);
    if(error){
        fprintf(stderr, "One of the numbers used is either not "
                        "available, or already used!\n");
        return EXIT_FAILURE;
    }

    if(user_value == numbers[FINAL])
        printf("Correct!\n");

    else
        printf("Incorrect! You missed by: %d\n", 
               abs(numbers[FINAL] - user_value)); 

    printf("Your number: %d\n", user_value);

    return EXIT_SUCCESS;

}