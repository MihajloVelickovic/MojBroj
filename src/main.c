#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#include "defs.h"
#include "func.h"
#include "stack.h"

bool expired = false;

void handler(int signum){
    expired = true;
}

int main(){

    srand(time(NULL));

    system("clear");

    int numbers[SIZE], i, user_value, total_score = 0;
    char buffer[MAX_EXPRESSION_SIZE];
    int error;
    struct Stack stack;

    int divisor;
    int final_helper, digit;

    signal(SIGALRM, handler);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);

    while(true){

        for(i=0; i<TFT; ++i)
            numbers[i] = generate_digit();

        numbers[TFT] = generate_tft();
        numbers[QUARTER] = generate_quarter();    
        numbers[FINAL] = generate_final();

        divisor = 100;
        final_helper = numbers[FINAL];

        for(i=0;i<3;++i){
            digit = final_helper/divisor;
            getchar();
            if(i == 0)
                system("clear");
            printf("%d", digit);
            final_helper %= divisor;
            divisor/=10;
        }

        getchar();
        system("clear");
        printf("%d\n", numbers[FINAL]);

        for(i=0; i<SIZE-3; ++i){
            getchar();
            printf("%d", numbers[i]);
        }

        for(i=SIZE-3; i<SIZE-1; ++i){
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
            fprintf(stderr, "\n%d seconds expired!\n");
            printf("Total score: %d\n", TIME, total_score);
            ungetc('\n', stdin);
            if(handle_finish() < 0)
                break;
            continue;
        }

        if(remove_whitespace(buffer) < 0){
            fprintf(stderr, "\nInvalid character inside expression!\n"); 
            printf("Total score: %d\n", total_score);
            ungetc('\n', stdin);
            if(handle_finish() < 0)
                break;
            continue;
        }
    
        create_stack(&stack);

        infix_to_postfix(&stack, buffer);

        user_value = evaluate_postfix(&stack, buffer, numbers, &error);
        if(error < 0){
            switch(error){
                case -1:
                    printf("\nThe number %d is either not available"
                           " or used too many times\n", user_value);
                    break;

                case -2:
                    printf("\nInvalid division\n");
            }
            printf("Total score: %d\n", total_score);
            ungetc('\n', stdin);
            if(handle_finish() < 0)
                break;
            continue;
        }

        if(user_value == numbers[FINAL]){
            printf("\nCorrect!\n");
            total_score += 10;
        }

        else{
            int difference = abs(numbers[FINAL] - user_value);
            printf("\nIncorrect! You missed by: %d\n", difference); 
            if(difference <= 5)
                total_score += 5;
            else if(difference <= 10)
                total_score += 2;
        }
        printf("Your number: %d\n", user_value);
        
        printf("Total score: %d\n", total_score);
        
        ungetc('\n', stdin);
        if(handle_finish() < 0)
            break;

    }

    printf("Total score: %d\n", total_score);
    return EXIT_SUCCESS;

}