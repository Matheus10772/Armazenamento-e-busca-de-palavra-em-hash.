#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct hash{
    char *c;
    int linha;
    int tamanhopalavra;
    struct hash *prox;
}hash;

typedef struct
{
    int linha;
    int posicaopalavra;
}rvetor;


hash* criarhash(hash* newhash, int tamanhohash);
void inserirnahash(FILE* arq,hash* hash1, int tamanhohash);
FILE* abrirarquivo(char arqnome[]);
int valormodhash(char* palavra, int tamanhohash, int palavratamanho);
rvetor* consultarlinha(char palavra[], int tamanhohash, hash* hash1);