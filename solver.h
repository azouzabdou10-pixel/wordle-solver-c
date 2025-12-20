#ifndef SOLVER_H
#define SOLVER_H

#include "game.h"

typedef struct {
    char **possible;
    int count;
    int capacity;
} WordList;

void init_solver(WordList *wl, char **dict, int dict_size);
char* get_next_guess(WordList *wl, int first);
void filter_words(WordList *wl, const char *guess, const char *feedback);
void free_wordlist(WordList *wl);

#endif