#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include "game.h"

#define MAX_WORDS 70
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

    // READ WORDS
    char words[MAX_WORDS][MAX_LENGTH];
    int count = 0;
    while (count < MAX_WORDS && fscanf(file, "%24s", words[count]) == 1)
    {
        count++;
    }

    fclose(file);

    if (count == 0)
    {
        printf("No words found in file.\n");
        return;
    }

    // SHUFFLE WORDS
    int i;
    int lives = 3;
    int score = 0;

    for (i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp[MAX_LENGTH];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }

    for (i = 0; i < count; i++)
    {
        if (lives == 0)
        {
            printf("GAME OVER! You've run out of lives.\n");
            printf("Your score is %d", score);
            printf("\n==========================================\n");
            return;
        }

        // ✅ ADD THIS BLOCK HERE
        char OriginalWord[MAX_LENGTH];
        strcpy(OriginalWord, words[i]);

        char ScrambledWord[MAX_LENGTH];
        strcpy(ScrambledWord, OriginalWord);

        scramble_word(ScrambledWord);

        char PlayerGuess[MAX_LENGTH];

        printf("\nLives: ");
        for (int j = 0; j < lives; j++)
        {
            printf("❤️ ");
        }
        printf("   Score: %d\n", score);
        printf("You have 10 seconds to guess the word!\n");
        printf("------------------------------------------\n");
        printf("Scrambled word: %s\n", ScrambledWord);

        printf("Your guess (10s / type END): ");
        fflush(stdout);

        int got_input = timed_input(PlayerGuess, 10);

        if (!got_input)
        {
            lives--;
            printf("\n==========================================\n");
            continue;
        }

        if (strcmp(PlayerGuess, "END") == 0 || strcmp(PlayerGuess, "end") == 0)
        {
            printf("Exiting game...\n");
            return;
        }

        printf("\n");

        if (check_answer(PlayerGuess, OriginalWord))
        {
            score += 10;
        }
        else
        {
            lives--;
        }

        printf("\n==========================================\n");
    }
    if (lives > 0)
    {
        printf("\n🎉 Congratulations! You finished all questions!\n");
    }
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
        return 0;
    }
}

int timed_input(char input[], int time_limit)
{
    fd_set input_set;
    struct timeval timeout;
    int ready_for_reading;
    int read_bytes;

    FD_ZERO(&input_set);
    FD_SET(STDIN_FILENO, &input_set);

    timeout.tv_sec = time_limit;
    timeout.tv_usec = 0;

    // Wait for input
    ready_for_reading = select(STDIN_FILENO + 1, &input_set, NULL, NULL, &timeout);

    if (ready_for_reading == -1)
    {
        printf("Error reading input\n");
        return 0;
    }

    if (ready_for_reading)
    {
        read_bytes = read(STDIN_FILENO, input, MAX_LENGTH - 1);

        // Remove newline
        if (read_bytes > 0 && input[read_bytes - 1] == '\n')
        {
            input[read_bytes - 1] = '\0';
        }
        else
        {
            input[read_bytes] = '\0';
        }

        return 1; // success
    }
    else
    {
        printf("\n⏰ Time's up!\n");
        input[0] = '\0';
        return 0; // timeout
    }
}

