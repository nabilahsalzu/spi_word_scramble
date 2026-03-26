#ifndef GAME_H
#define GAME_H

void new_game();
void scramble_word(char word[]);
int check_answer(char user_guess[], char selected_word[]);
int input_with_timeout(char *buffer, int size, int timeout_seconds);

#endif

