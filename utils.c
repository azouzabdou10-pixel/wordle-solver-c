#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "game.h"

int load_dictionary(const char *filename, char ***dict) {
    FILE *f = fopen(filename, "r");
    if(!f) {
        printf("Error opening file\n");
        return 0;
    }
    
    int cap = 1000;
    int cnt = 0;
    *dict = malloc(sizeof(char*) * cap);
    
    char buf[100];
    while(fgets(buf, sizeof(buf), f)) {
        int len = strlen(buf);
        if(buf[len-1] == '\n') buf[len-1] = '\0';
        
        if(strlen(buf) != WORD_LEN) continue;
        
        int i;
        for(i = 0; buf[i]; i++) {
            buf[i] = tolower(buf[i]);
        }
        
        if(cnt >= cap) {
            cap *= 2;
            *dict = realloc(*dict, sizeof(char*) * cap);
        }
        
        (*dict)[cnt] = malloc(WORD_LEN + 1);
        strcpy((*dict)[cnt], buf);
        cnt++;
    }
    
    fclose(f);
    return cnt;
}

void free_dictionary(char **dict, int size) {
    int i;
    for(i = 0; i < size; i++) {
        free(dict[i]);
    }
    free(dict);
}

void print_feedback(const char *guess, const char *feedback) {
    int i;
    printf("Guess: ");
    for(i = 0; i < WORD_LEN; i++) {
        if(feedback[i] == 'G') {
            printf("[%c]", guess[i]);
        } else if(feedback[i] == 'Y') {
            printf("(%c)", guess[i]);
        } else {
            printf(" %c ", guess[i]);
        }
    }
    printf("\n");
}