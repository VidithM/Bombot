#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"
#include "server.h"

//#define DEBUG

#define MAX_LEN (1 << 10)

void print_str(char* str){
    while(*str != '\0'){
        printf("%c", *(str++));
    }
    printf("\n");
}

int eq(char* a, char *b){
    int l = 0;
    int r = 0;
    while(a[l] != '\0' && b[r] != '\0'){
        if(a[l] != b[r]){
            return 0;
        }
        l++;
        r++;
    }
    if(a[l] == b[l]){
        return 1; // both \0
    }
    return 0;
}

int main(){
    FILE *words_file;
    words_file = fopen("wordlist", "r");

    char c = fgetc(words_file);
    int curr_idx = 0;
    char *curr_word = (char*) malloc(MAX_LEN * sizeof(char));
    
    struct node *trie = (struct node*) malloc(sizeof(struct node));
    init(trie);

    int invalid = 0;

    while(c != EOF){
#ifdef DEBUG
        printf("At char: 0x%X\n", c);
#endif
        if(c == '\n'){
            if(!invalid){
                int len = curr_idx;
                if(len > 0){
                    char* word = (char*) malloc(len * sizeof(char) + 1);
                    memcpy(word, curr_word, len);
                    //print_str(word);
                    word[len] = '\0';
                    for(int i = 0; i < len; i++){
                        for(int j = i; j < len; j++){
                            char* put = (char*) malloc((j - i + 2) * sizeof(char) + 1);
                            memcpy(put + 1, curr_word + i, j - i + 1);
                            put[j - i + 2] = '\0';
                            put[0] = '?';
                            //print_str(put);
                            insert_root(put, word, trie, j - i + 2);
                        }
                    }
                }
            } else {
#ifdef DEBUG
                printf("Discarding word\n");
#endif
            }
            invalid = 0;
            curr_idx = 0;
        } else if(c >= 'a' && c <= 'z'){
           curr_word[curr_idx] = c;
           curr_idx++;
        } else if(c != 0x0d){ // ignore carriage return
            invalid = 1;
        }
        c = fgetc(words_file);
    }
    print_str(use_root("?ulv", trie, 4));

    start_server(8000);
    connect_client();
}