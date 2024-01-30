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

    printf("Once all of the numbers are present, you have ");
    printf(ANSI_GREEN_BOLD"%d"ANSI_WHITE" seconds!\n", TIME);
    getchar();
    system("clear");
    
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
            printf(ANSI_GREEN"%d", digit);
            final_helper %= divisor;
            divisor/=10;
        }

        getchar();
        system("clear");
        printf(ANSI_GREEN_BOLD"%d\n", numbers[FINAL]);

        for(i=0; i<SIZE-3; ++i){
            getchar();
            printf(ANSI_YELLOW"%d", numbers[i]);
        }

        for(i=SIZE-3; i<SIZE-1; ++i){
            printf("\n");
            getchar();
            if(i == SIZE-2)
                printf(ANSI_BLUE"%d", numbers[i]);
            else
                printf(ANSI_PURPLE"%d", numbers[i]);
        }

        printf(ANSI_WHITE"\n-----------------------------------\n");

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
            fprintf(stderr, "\n%d seconds expired!\n", TIME);
            printf("Total score: %d\n", total_score);
            ungetc('\n', stdin);
            if(handle_finish() < 0)
                break;
            continue;
        }

        if(remove_whitespace(buffer) < 0){
            fprintf(stderr, "\nInvalid character inside expression!\n"); 
            printf("Total score: "ANSI_GREEN_BOLD"%d\n"ANSI_WHITE,total_score);
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
                    printf("\nThe number"ANSI_RED_BOLD" %d "ANSI_WHITE,
                                                            user_value);
                    printf("is either not available or used too many times\n");
                    break;
                case -2:
                    printf("\nInvalid division\n");
                    break;
                case -3:
                    printf("\nDivision by "ANSI_RED_BOLD"0"ANSI_WHITE);
                    printf(" is prohibited!\n");
                    break;
            }
            printf("Total score: "ANSI_GREEN_BOLD"%d\n"ANSI_WHITE,total_score);
            ungetc('\n', stdin);
            if(handle_finish() < 0)
                break;
            continue;
        }

        if(user_value == numbers[FINAL]){
            printf(ANSI_GREEN_BOLD"\nCorrect!\n"ANSI_WHITE);
            total_score += 10;
        }

        else{
            int difference = abs(numbers[FINAL] - user_value);

            printf(ANSI_RED_BOLD"\nIncorrect!");
            printf(ANSI_WHITE" You missed by: "ANSI_RED_BOLD"%d\n",difference);
            printf(ANSI_WHITE); 
            if(difference <= 5)
                total_score += 5;
            else if(difference <= 10)
                total_score += 2;
        }
        printf("Your number: %s%d\n"ANSI_WHITE, user_value == numbers[FINAL] 
                                                ? ANSI_GREEN_BOLD:ANSI_RED_BOLD
                                                , user_value);
        
        printf("Total score: "ANSI_GREEN_BOLD"%d\n"ANSI_WHITE, total_score);
        
        ungetc('\n', stdin);
        if(handle_finish() < 0)
            break;

    }

    printf("Total score: "ANSI_GREEN_BOLD"%d\n"ANSI_WHITE, total_score);
    return EXIT_SUCCESS;

}