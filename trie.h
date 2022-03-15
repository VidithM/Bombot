#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
//#define USE_DEBUG

struct node {
    char c;
    char **matches;
    int nMatch;
    int cap;
    struct node **to;
};

void init(struct node *n){
    n -> to = (struct node**) malloc(26 * sizeof(struct node*));
    for(int i = 0; i < 26; i++){
        n -> to[i] = NULL;
    }
    n -> nMatch = 0;
    n -> cap = 0;
}

void insert(char *str, char* put, struct node *n, int at, int len){
    n -> c = str[at];
#ifdef DEBUG
    printf("at node: %c %d %d\n", n -> c, at, len);
#endif
    if(at == len - 1){
        if(n -> cap == 0){
            n -> matches = (char**) malloc((1 << 20) * sizeof(char*));
            n -> cap = (1 << 20);
        } else if ((n -> nMatch) == (n -> cap)){
            //printf("resized\n");
            //n -> matches = (char**) realloc(n -> matches, (n -> cap) * 2);
            //(n -> cap) *= 2;
        }
        n -> matches[n -> nMatch] = put;
        (n -> nMatch)++;
        return;
    }
    if(n -> to[str[at + 1] - 'a'] == NULL){
#ifdef DEBUG
        printf("putting new trie node\n");
#endif
        struct node *put = (struct node*) malloc(sizeof(struct node));
        init(put);
        n -> to[str[at + 1] - 'a'] = put;
    }
    insert(str, put, n -> to[str[at + 1] - 'a'], at + 1, len);
#ifdef DEBUG
    printf("done node: %c %d %d\n", n -> c, at, len);
#endif
}

char* use(char* need, int at, struct node *n, int len){
#ifdef USE_DEBUG
    printf("at node: %c %d %d\n", n -> c, at, len);
#endif
    if(at == len - 1){
        if(n -> nMatch == 0){
            return NULL; // empty list
        }
        char *res = (n -> matches)[0];
        (n -> matches)++;
        (n -> nMatch)--;
        return res;
    }
    if(n -> to[need[at + 1] - 'a'] == 0){
        return NULL; // no match
    }
    return use(need, at + 1, n -> to[need[at + 1] - 'a'], len);
}

void insert_root(char *str, char *put, struct node *n, int len){
    insert(str, put, n, 0, len);
#ifdef DEBUG
    printf("done total\n");
#endif
}

char* use_root(char* need, struct node *n, int len){
    return use(need, 0, n, len);
}