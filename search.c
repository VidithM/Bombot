#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

#define NWORDS 90000
#define WORD_LEN (1 << 10)

int main(){
    FILE *words_file;
    words_file = fopen("wordlist", "r");
    char **words = (char**) malloc(NWORDS * sizeof(char*));
    memset(words, 0, NWORDS * sizeof(char*));

    char c = fgetc(words_file);
    int curr_idx = 0;
    int curr_word_idx = 0;

    char *curr_word = (char*) malloc(WORD_LEN * sizeof(char));
    while(c != EOF){
        if(c == '\n'){
            for(int i = curr_word_idx; i < WORD_LEN; i++){
                curr_word[i] = '$';
            }
            char *put = (char*) malloc(WORD_LEN * sizeof(char));
            memcpy(put, curr_word, WORD_LEN * sizeof(char));
            words[curr_idx] = put;
            curr_idx++;
            curr_word_idx = 0;
        } else {
            curr_word[curr_word_idx] = c;
            curr_word_idx++;
        }
        c = fgetc(words_file);
    }
    fclose(words_file);
}