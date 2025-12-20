#ifndef UTILS_H
#define UTILS_H

int load_dictionary(const char *filename, char ***dict);
void free_dictionary(char **dict, int size);
void print_feedback(const char *guess, const char *feedback);

#endif