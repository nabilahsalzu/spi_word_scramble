#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void display_menu(int *user_entry)
{
    printf("\n==========================================\n");
    printf("\n      WELCOME TO WORD SCRAMBLE GAME!\n");
    printf("\n==========================================\n\n");
    printf("\t1. New Game\n");
    printf("\t2. Help\n");
    printf("\t3. Exit\n\n");

    printf("\tChoose : ");
    scanf(" %d", user_entry);
}

void show_help()
{
    printf("================== Help ==================\n\n");
    printf("> Use keyboard to play the game\n");
    printf("> Follow the instruction shown in game New\n");
    printf("> Try to get the highest score");
}

void exit_game()
{
    printf("================== Exit ==================\n\n");
    printf("> Thank you for playing\n");
    printf("> The game will Close\n\n");
    exit(0);
}

