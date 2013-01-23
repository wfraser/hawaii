//
// main.c
// Hawaiian-sounding word generator
//
// Copyright (c) 2013 William R. Fraser
// 1/22/2013. Written in Kahana, Maui :)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "hawaii.h"

// Main entry point. Generates one word between 6 and 12 characters and prints it.
int main(int argc, char** argv)
{
    char word[12];
    memset(word, 0, sizeof(word));

    time_t t = time(NULL);
    srand((unsigned int)t);

#if 0
    // print all possible syllables
    for (int i = 0; i < sizeof(vowels) * (1 + sizeof(cons)); i++) {
        putsyl(i, word);
        printf("%s\n", word);
    }
#endif

    hawaii(word, sizeof(word));
    char* word2 = add_apostrophes(word, strlen(word));
    
    printf("%s\n", word2);

    return 0;
}
