//
// hawaii.c
// Hawaiian-sounding word generator
//
// Copyright (c) 2013 William R. Fraser
// 1/22/2013. Written in Kahana, Maui :)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

char vowels[] = { 'a','e','i','o','u' };
char cons[]   = { 'h','k','l','m','n','p','w' };

// add a syllable at the start of buf
// returns the number of characters written
// assumes buf has enough space for 1 or 2 chars
int putsyl(int syl, char* buf)
{
    if (syl < sizeof(vowels)) {
        // 1-letter syllable (vowel)
        *buf = vowels[syl];
        return 1;
    }
    else {
        // 2-letter syllable (consonant-vowel)
        syl -= sizeof(vowels);
        *buf = cons[syl / sizeof(vowels)];
        buf++;
        *buf = vowels[syl % sizeof(vowels)];
        return 2;
    }
}

// Generate a random hawaiian-sounding word and store it in buf.
// Buffer is of length bufsz, including null terminator.
// Generates a word of random length between bufsz-1 and (bufsz-1)/2
void hawaii(char* buf, size_t bufsz)
{
    int half = (bufsz - 1) / 2;
    int len = half + rand() / (RAND_MAX / half);

    int n = sizeof(vowels) * (1 + sizeof(cons));

    int i = 0;
    while (i < len) {
        int syl;
        if (len - i == 1) {
            // not enough room for a 2-letter syllable; add a 1-letter one
            syl = rand() / (RAND_MAX / sizeof(vowels));
        }
        else {
            syl = rand() / (RAND_MAX / n);
        }

        i += putsyl(syl, buf + i);
    }
}

bool is_vowel(char c)
{
    switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

// Adds apostrophes between adjacent vowels.
// Give a character buffer containing the word, and the length of the word (without
// null-terminators).
// Returns a new buffer with the apostrophe-added word.
char* add_apostrophes(char* word, size_t len)
{
    char* word2 = (char*)malloc(len * 2 + 1);

    int i = 1;
    int j = 1;
    word2[0] = word[0];
    while (i < len) {
        if (is_vowel(word[i-1]) && is_vowel(word[i])) {
            word2[j++] = '\'';
        }
        word2[j++] = word[i++];
    }
    word2[j] = '\0';
    return word2;
}
