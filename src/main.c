#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
#else
    #include <unistd.h>
    #define CLEAR "clear"
#endif

#include "defs.h"
#include "func.h"
#include "stack.h"

int main(){

    srand(time(NULL));

    int numbers[SIZE], i, user_value;
    char buffer[MAX_EXPRESSION_SIZE];
    bool error;
    struct Stack stack;

    while(true){

        for(i=0; i<TFT; ++i)
            numbers[i] = generate_digit();

        numbers[TFT] = generate_tft();
        numbers[QUARTER] = generate_quarter();    
        numbers[FINAL] = generate_final();

        for(i=0; i<SIZE-3; ++i){
            getchar();
            printf("%d", numbers[i]);
        }

        for(i=SIZE-3; i<SIZE; ++i){
            printf("\n");
            getchar();
            printf("%d", numbers[i]);
        }

        printf("\n\n");

        fgets(buffer, MAX_EXPRESSION_SIZE, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        remove_whitespace(buffer, &error);
        if(error){
            fprintf(stderr, "Invalid character inside expression!\n");
            return EXIT_FAILURE;
        }
    
        create_stack(&stack);

        infix_to_postfix(&stack, buffer);

        user_value = evaluate_postfix(&stack, buffer, numbers, &error);
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

        printf("Press any button (q to quit)!\n");
        char input = getchar();

        if(input == 'q' || input == 'Q')
            break;

        system(CLEAR);

    }

    return EXIT_SUCCESS;

}