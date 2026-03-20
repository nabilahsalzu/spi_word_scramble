#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

#define MAX_WORDS 5
#define MAX_LENGTH 20

void new_game()
{
    // OPEN FILE
    FILE *file = fopen("data/puzzle1.txt", "r");
    if (file == NULL)
    {
        printf("Could not open the file.\n");
        return;
    }

    // READ WORDS AND STORE IN ARRAY
    char words[MAX_WORDS][MAX_LENGTH];
    int count = 0;
    while (count < MAX_WORDS && fscanf(file, "%24s", words[count]) == 1)
    {
        count++;
    }

    
    // CLOSE FILE
    fclose(file);

    if (count == 0)
    {
        printf("No words found in file.\n");
        return;
    }

    // SHUFFLE WORDS (different order for each game)
    int i;
    for (i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp[MAX_LENGTH];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }

    // LOOP THROUGH ALL WORDS
    for (i = 0; i < count; i++)
    {
        char OriginalWord[MAX_LENGTH];
        strcpy(OriginalWord, words[i]);

        char ScrambledWord[MAX_LENGTH];
        strcpy(ScrambledWord, OriginalWord);

        scramble_word(ScrambledWord); // robust shuffle

        printf("\nScrambled word: %s\n", ScrambledWord);

        char PlayerGuess[MAX_LENGTH];
        printf("Your guess (type END to quit): ");
        scanf("%24s", PlayerGuess);

        if (strcmp(PlayerGuess, "END") == 0 || strcmp(PlayerGuess, "end") == 0)
        {
            printf("Exiting game...\n");
            return;
        }

        if (!check_answer(PlayerGuess, OriginalWord))
        {
            return;
        }
    }

    printf("Congratulations! You finished all the words.\n");
}

// ROBUST SCRAMBLE FUNCTION (Fisher–Yates)
void scramble_word(char word[])
{
    int length = strlen(word);
    char original[length + 1];
    strcpy(original, word);

    do
    {
        int i;
        for (i = length - 1; i > 0; i--)
        {
            int j = rand() % (i + 1);
            char temp = word[i];
            word[i] = word[j];
            word[j] = temp;
        }
    } while (strcmp(word, original) == 0); // ensure it changes
}

// CHECK ANSWER - Returns 1 if correct, 0 if wrong
int check_answer(char user_guess[], char original_word[])
{
    if (strcmp(user_guess, original_word) == 0)
    {
        printf("Correct! Well done.\n");
        return 1;
    }
    else
    {
        printf("Wrong! The correct word was: %s\n", original_word);
        printf("GAME OVER\n");
        return 0;
    }
}
