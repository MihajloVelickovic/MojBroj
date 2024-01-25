#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include "defs.h"
#include "func.h"
#include "stack.h"

int expired = 0;

void handler(int signum){
    expired = 1;
}

int main(){

    srand(time(NULL));

    int numbers[SIZE], i, user_value;
    char buffer[MAX_EXPRESSION_SIZE];
    int error;
    struct Stack stack;

    signal(SIGALRM, handler);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);

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

        alarm(TIME);

        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

        while(!expired){
            
            if(fgets(buffer, MAX_EXPRESSION_SIZE, stdin) != NULL){
                    buffer[strlen(buffer) - 1] = '\0';
                    alarm(0);
                    break;
            }
            
            usleep(1000);
            
        }

        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
        
        if(expired){
            expired = 0;
            fprintf(stderr, "50 Seconds expired!\n");
            if(handle_finish() < 0)
                break;
            continue;
        }

        if(remove_whitespace(buffer) < 0){
            fprintf(stderr, "Invalid character inside expression!\n");
            return EXIT_FAILURE;
        }
    
        create_stack(&stack);

        infix_to_postfix(&stack, buffer);

        user_value = evaluate_postfix(&stack, buffer, numbers, &error);
        if(error < 0){
            switch(error){
                case -1:
                    printf("The number %d is either not available or used too many times\n", user_value);
                    break;

                case -2:
                    printf("Invalid division\n");
            }
            return EXIT_FAILURE;
        }

        if(user_value == numbers[FINAL])
            printf("Correct!\n");

        else
            printf("Incorrect! You missed by: %d\n", 
                abs(numbers[FINAL] - user_value)); 

        printf("Your number: %d\n", user_value);

        if(handle_finish() < 0)
            break;

    }

    return EXIT_SUCCESS;

}