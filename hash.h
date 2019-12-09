#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


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
	int indicerv;
}rvetor;


hash* criarhash(hash* newhash, int tamanhohash);
void processararquivo(FILE* arq,hash* hash1, int tamanhohash);
void inserirnahash(FILE* arq, hash* hash1,int tamanhohash, int indice, char* palavra, int linha);
FILE* abrirarquivo(char arqnome[]);
void inicializarvalores(hash *hash1, int tamanhohash);
void inicializarrvetor(rvetor* rvetor1, int tamanho);
int valormodhash(char* palavra, int tamanhohash, int palavratamanho);
rvetor* consultarlinha(char* palavraprocurar, int tamanhohash, hash* hash1);
