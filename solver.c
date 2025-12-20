#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"

void init_solver(WordList *wl, char **dict, int dict_size) {
    wl->capacity = dict_size;
    wl->count = dict_size;
    wl->possible = malloc(sizeof(char*) * dict_size);
    
    int i;
    for(i = 0; i < dict_size; i++) {
        wl->possible[i] = dict[i];
    }
}

char* get_next_guess(WordList *wl, int first) {
    if(first) {
        return "soare";
    }
    
    if(wl->count == 0) return NULL;
    
    int freq[26] = {0};
    int i, j;
    
    for(i = 0; i < wl->count; i++) {
        for(j = 0; j < WORD_LEN; j++) {
            freq[wl->possible[i][j] - 'a']++;
        }
    }
    
    int best_idx = 0;
    int best_score = -1;
    
    for(i = 0; i < wl->count; i++) {
        int score = 0;
        int used[26] = {0};
        
        for(j = 0; j < WORD_LEN; j++) {
            int c = wl->possible[i][j] - 'a';
            if(!used[c]) {
                score += freq[c];
                used[c] = 1;
            }
        }
        
        if(score > best_score) {
            best_score = score;
            best_idx = i;
        }
    }
    
    return wl->possible[best_idx];
}

void filter_words(WordList *wl, const char *guess, const char *feedback) {
    int new_cnt = 0;
    int i, j;
    
    for(i = 0; i < wl->count; i++) {
        char *word = wl->possible[i];
        int valid = 1;
        char tmp[WORD_LEN + 1];
        strcpy(tmp, word);
        
        // check greens
        for(j = 0; j < WORD_LEN; j++) {
            if(feedback[j] == 'G') {
                if(word[j] != guess[j]) {
                    valid = 0;
                    break;
                }
                tmp[j] = '*';
            }
        }
        
        if(!valid) continue;
        
        // check yellows and grays
        for(j = 0; j < WORD_LEN; j++) {
            if(feedback[j] == 'Y') {
                if(word[j] == guess[j]) {
                    valid = 0;
                    break;
                }
                int k, found = 0;
                for(k = 0; k < WORD_LEN; k++) {
                    if(tmp[k] == guess[j]) {
                        found = 1;
                        tmp[k] = '*';
                        break;
                    }
                }
                if(!found) {
                    valid = 0;
                    break;
                }
            } else if(feedback[j] == 'X') {
                int k;
                for(k = 0; k < WORD_LEN; k++) {
                    if(tmp[k] == guess[j]) {
                        valid = 0;
                        break;
                    }
                }
                if(!valid) break;
            }
        }
        
        if(valid) {
            wl->possible[new_cnt++] = word;
        }
    }
    
    wl->count = new_cnt;
}

void free_wordlist(WordList *wl) {
    free(wl->possible);
}