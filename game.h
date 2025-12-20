#ifndef GAME_H
#define GAME_H

#define WORD_LEN 5
#define MAX_TRIES 6
#define MAX_WORDS 15000

typedef struct {
    char target[WORD_LEN + 1];
    int attempts;
    int won;
} Game;

void init_game(Game *g, char **dict, int dict_size);
int check_guess(Game *g, const char *guess, char *feedback);
int is_valid_guess(const char *guess, char **dict, int dict_size);

#endif