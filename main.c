#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "solver.h"
#include "utils.h"

static void play_human(char **dict, int dict_size) {
    Game g;
    char guess[100];
    char feedback[WORD_LEN + 1];

    init_game(&g, dict, dict_size);

    printf("=== Wordle (Human Mode) ===\n");
    printf("Rules: G=correct place, Y=wrong place, X=not in word\n");

    while(g.attempts < MAX_TRIES && !g.won) {
        printf("\nAttempt %d/%d - Enter guess: ", g.attempts + 1, MAX_TRIES);

        if(!fgets(guess, sizeof(guess), stdin)) return;
        guess[strcspn(guess, "\n")] = '\0';

        // normalize to lowercase (simple)
        for(int i = 0; guess[i]; i++) {
            if(guess[i] >= 'A' && guess[i] <= 'Z') guess[i] = (char)(guess[i] - 'A' + 'a');
        }

        if(!is_valid_guess(guess, dict, dict_size)) {
            printf("Invalid guess. Must be a 5-letter word from dictionary.\n");
            continue;
        }

        check_guess(&g, guess, feedback);
        print_feedback(guess, feedback);
    }

    if(g.won) {
        printf("\nYou won in %d attempts!\n", g.attempts);
    } else {
        printf("\nYou lost. Target word was: %s\n", g.target);
    }
}

static void play_solver(char **dict, int dict_size) {
    Game g;
    WordList wl;
    char feedback[WORD_LEN + 1];

    init_game(&g, dict, dict_size);
    init_solver(&wl, dict, dict_size);

    printf("=== Wordle (Solver Mode) ===\n");
    printf("Rules: G=correct place, Y=wrong place, X=not in word\n");

    int first = 1;

    while(g.attempts < MAX_TRIES && !g.won) {
        char *guess = get_next_guess(&wl, first);
        first = 0;

        if(!guess) {
            printf("Solver: no possible words left.\n");
            break;
        }

        printf("\nAttempt %d/%d - Solver guess: %s\n", g.attempts + 1, MAX_TRIES, guess);

        check_guess(&g, guess, feedback);
        print_feedback(guess, feedback);

        if(!g.won) {
            filter_words(&wl, guess, feedback);
            printf("Remaining candidates: %d\n", wl.count);
        }
    }

    if(g.won) {
        printf("\nSolver won in %d attempts! Word: %s\n", g.attempts, g.target);
    } else {
        printf("\nSolver failed. Target word was: %s\n", g.target);
    }

    free_wordlist(&wl);
}

int main(void) {
    char **dict = NULL;
    int dict_size = load_dictionary("words.txt", &dict);

    if(dict_size <= 0) {
        printf("Dictionary load failed. Make sure words.txt exists.\n");
        return 1;
    }

    while(1) {
        int choice = 0;
        printf("\n=============================\n");
        printf("WORDLE PROJECT - MENU\n");
        printf("1) Human plays Wordle\n");
        printf("2) Solver plays Wordle\n");
        printf("3) Exit\n");
        printf("Choose: ");

        if(scanf("%d", &choice) != 1) {
            // clear invalid input
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        // consume newline after scanf
        int ch;
        while((ch = getchar()) != '\n' && ch != EOF) {}

        if(choice == 1) {
            play_human(dict, dict_size);
        } else if(choice == 2) {
            play_solver(dict, dict_size);
        } else if(choice == 3) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    free_dictionary(dict, dict_size);
    return 0;
}
