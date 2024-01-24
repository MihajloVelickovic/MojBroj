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

    remove_whitespace(buffer); 

    struct Stack stack;
    create_stack(&stack);

    infix_to_postfix(&stack, buffer);

    bool error;

    int user_value = evaluate_postfix(&stack, buffer, &error);

    if(error == true){
        fprintf(stderr,"Postfix evaluation error\n");
        return EXIT_FAILURE;
    } 

    if(user_value == numbers[FINAL])
        printf("Correct!\n");

    else
        printf("Incorrect!\n"); 

    return EXIT_SUCCESS;
}