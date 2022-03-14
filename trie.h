#pragma once

#include <string.h>

struct node {
    char c;
    char **matches;
    size_t nMatch;
    int cap;
    struct node **to;
} trie;


void init(struct node *n){
    n -> to = (struct node**) malloc(26 * sizeof(struct node*));
    memset(n -> to, 0, 26 * sizeof(struct node*));
    n -> nMatch = 0;
    n -> cap = 0;
}

void insert(char *str, char* put, struct node *n, int at, int len){
    n -> c = str[at];
    if(at == len - 1){
        if(n -> cap == 0){
            n -> matches = (char**) malloc((1 << 4) * sizeof(char*));
            n -> cap = (1 << 4);
        } else if ((n -> nMatch) == (n -> cap)){
            n -> matches = (char**) realloc(n -> matches, (n -> cap) << 1);
            (n -> cap) <<= 1;
        }
        n -> matches[n -> nMatch] = put;
        (n -> nMatch)++;
        return;
    }
    if(n -> to[str[at + 1] - 'a'] == 0){
        struct node put;
        init(&put);
        n -> to[str[at + 1] - 'a'] = &put;
    }
    insert(str, put, n -> to[str[at + 1] - 'a'], at + 1, len);
}

char* use(char* need, int at, struct node *n, int len){
    if(at == len - 1){
        if(n -> cap == 0){
            return NULL; // empty list
        }
        char *res = (n -> matches)[0];
        (n -> matches)++;
        (n -> cap)--;
        return res;
    }
    if(n -> to[need[at + 1] - 'a'] == 0){
        return NULL; // no match
    }
    return use(need, at + 1, n -> to[need[at + 1] - 'a'], len);
}

void insert_root(char *str, char *put, int len){
    insert(str, put, &trie, 0, len);
}

char* use_root(char* need, int len){
    return use(need, 0, &trie, len);
}