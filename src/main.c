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

    while (1) // infinite loop until exit
    {
        display_menu(&user_entry);

        switch(user_entry)
        {
            case 1:
                printf("\n\tWord Scramble Puzzle Game!\n");
                printf("==========================================\n");
                new_game(); // returns here after game ends
                break;

            case 2:
                printf("\n");
                show_help();
                printf("\n");
                break;

            case 3:
                printf("\n");
                exit_game(); // exits program
                break;

            default:
                printf("\nChoose valid selection\n\n");
                break;
        }
    }

    return 0;
}

