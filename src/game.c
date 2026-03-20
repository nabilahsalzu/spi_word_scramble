#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

#define MAX_WORDS 100
#define MAX_LENGTH 20

void new_game()
{
	// OPEN FILE
    FILE *file = fopen("data/puzzle1.txt", "r"); // reading mode

    if (file == NULL) // file doesn’t exist
    {
        printf("Could not open the file.\n");
        return;
    }


    // READ WORDS AND STORE IN ARRAY
    char words[MAX_WORDS][MAX_LENGTH];
    int count = 0;

    while (count < MAX_WORDS && fscanf(file, "%99s", words[count]) == 1)
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
    
    
    // SHUFFLE WORDS - different order for each 'NEW GAME'
    int i;
    
    for (i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        char temp[MAX_LENGTH];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }
    
    
    
    // LOOP THROUGH ALL WORDS (NO REPEAT) - using the new order
    for (i = 0; i < count; i++)
    {
        char OriginalWord[MAX_LENGTH];
        strcpy(OriginalWord, words[i]); // avoid modify the original word

        char ScrambledWord[MAX_LENGTH];
        strcpy(ScrambledWord, OriginalWord);

        scramble_word(ScrambledWord);

        printf("\nScrambled word: %s\n", ScrambledWord);

        char PlayerGuess[MAX_LENGTH];
        printf("Your guess (type END to quit): ");
        scanf("%s", PlayerGuess);

        if (strcmp(PlayerGuess, "END") == 0 || strcmp(PlayerGuess, "end") == 0)
        {
        	main();
        }

        check_answer(PlayerGuess, OriginalWord);
    }
    
    if (i=count)
    {
        printf("Congratulations !! you finish all the words\n");
        main();
    }
}


// SCRAMBLE FUNCTION
void scramble_word(char word[])
{
    int s, r;
    int length = strlen(word);

    for (s = 0; s < length; s++)
    {
        r = rand() % length;

        char temp = word[s];
        word[s] = word[r];
        word[r] = temp;
    }
}


// CHECK ANSWER
void check_answer(char user_guess[], char original_word[])
{
    if (strcmp(user_guess, original_word) == 0)
    {
        printf("Correct! Well done.\n");
    }
    else
    {
        printf("Wrong! The correct word was: %s\n", original_word);
        printf("GAME OVER\n");
        main();
    }
}
