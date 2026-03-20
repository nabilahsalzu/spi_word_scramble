#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "game.h"

void new_game();

int main()
{
    srand(time(NULL)); // for any random generator
    
    int user_entry;

    do
    {
        display_menu(&user_entry);

        switch(user_entry)
        {
            case 1:
            	printf("\n\tWord Scramble Puzzle Game!\n");
    			printf("==========================================\n\n");
                new_game();
                break;

            case 2:
                printf("\n");
                show_help();
                printf("\n");
                break;

            case 3:
                printf("\n");
                exit_game();
                printf("\n");
                break;

            default:
                printf("\nChoose valid selection\n\n");
                break;
        }

    } while(user_entry != 3 && user_entry != 1);

    return 0;
}

