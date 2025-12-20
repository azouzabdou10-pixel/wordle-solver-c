#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

void init_game(Game *g, char **dict, int dict_size) {
    srand(time(NULL));
    int idx = rand() % dict_size;
    strcpy(g->target, dict[idx]);
    g->attempts = 0;
    g->won = 0;
}

int check_guess(Game *g, const char *guess, char *feedback) {
    int i, j;
    char tmp[WORD_LEN + 1];
    strcpy(tmp, g->target);
    
    for(i = 0; i < WORD_LEN; i++) {
        feedback[i] = 'X';
    }
    feedback[WORD_LEN] = '\0';
    
    // green first
    for(i = 0; i < WORD_LEN; i++) {
        if(guess[i] == tmp[i]) {
            feedback[i] = 'G';
            tmp[i] = '*';
        }
    }
    
    for(i = 0; i < WORD_LEN; i++) {
        if(feedback[i] == 'G') continue;
        for(j = 0; j < WORD_LEN; j++) {
            if(tmp[j] == guess[i]) {
                feedback[i] = 'Y';
                tmp[j] = '*';
                break;
            }
        }
    }
    
    g->attempts++;
    
    if(strcmp(guess, g->target) == 0) {
        g->won = 1;
        return 1;
    }
    
    return 0;
}

int is_valid_guess(const char *guess, char **dict, int dict_size) {
    if(strlen(guess) != WORD_LEN) return 0;
    
    int i;
    for(i = 0; i < dict_size; i++) {
        if(strcmp(guess, dict[i]) == 0) {
            return 1;
        }
    }
    return 0;
}