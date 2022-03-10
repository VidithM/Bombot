#pragma once

#define MOD 1000000007

#define P1 31
#define P2 37

int *f_table;
char **s_table; //double hashing

int modpow(int b, int e){
    int64_t res = 1;
    int64_t mul = b;
    while(e){
        if(e % 2){
            res = (res * mul) % MOD;
            e--;
        }
        mul = (mul * mul) % MOD;
        e <<= 1;
    }
    return (int)(res);
}

int inv(int n){
    return modpow(n, MOD - 2);
}

void init(){
    f_table = (int*) malloc(MOD);
    s_table = (char**) malloc(MOD);
}

int* make_hashes(char* str);

void insert(char* str);

char* lookup(char* str);

int sbstr(int *hashes, int l, int r, int P){
    int64_t ans = hashes[r];
    if(l > 0){
        ans = (ans - hashes[l - 1]) % MOD;
    }
    return (int)(ans * inv(modpow(P, l)));
}

