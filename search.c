#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"

//#define DEBUG

#define MAX_LEN (1 << 10)

int main(){
    FILE *words_file;
    words_file = fopen("wordlist", "r");

    char c = fgetc(words_file);
    int curr_idx = 0;
    char *curr_word = (char*) malloc(MAX_LEN * sizeof(char));
    init(&trie);

    char invalid = 0;
    while(c != EOF){
#ifdef DEBUG
        printf("At char: 0x%X\n", c);
#endif
        if(c == '\n'){
            if(!invalid){
                int len = curr_idx;
                //printf("%d\n", len);
                char* word = (char*) malloc(len * sizeof(char) + 1);
                memcpy(word, curr_word, len);
                word[len] = '\0';
                for(int i = 0; i < len; i++){
                    for(int j = i + 1; j < len; j++){
                        char* put = (char*) malloc((j - i + 1) * sizeof(char));
                        memcpy(put, curr_word + i, j - i + 1);
                        insert_root(word, put, len);
                    }
                }
            } else {
#ifdef DEBUG
                printf("discarding word\n");
#endif
            }
            invalid = 0;
            curr_idx = 0;
        } else if(c >= 0x61 && c <= 0x7a){
           curr_word[curr_idx] = c;
           curr_idx++;
        } else {
            invalid = 1;
        }
        c = fgetc(words_file);
    }
    fclose(words_file);
}