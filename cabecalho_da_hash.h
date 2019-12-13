#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct hash{
    char *c;
    int linha;
    int tamanhopalavra;
    struct hash *prox;
}hash;//estrutura usada para criação da hash.

typedef struct
{
    int linha;
    int posicaopalavra;
	int indicerv;
}rvetor;//estrutura usada para criar o vetor de armazenamento das informações da palavra procurada.


hash* criarhash(hash* newhash, int tamanhohash);
hash* processararquivo(FILE* arq,hash* hash1, int tamanhohash);
hash* inserirnahash(FILE* arq, hash* hash1,int tamanhohash, int indice, char* palavra, int linha);
FILE* abrirarquivo(char arqnome[]);
void inicializarvalores(hash *hash1, int tamanhohash);
void inicializarrvetor(rvetor* rvetor1, int tamanho);
int valormodhash(char* palavra, int tamanhohash, int palavratamanho);
void consultarlinha(char* palavraprocurar, int tamanhohash, hash* hash1);
void imprimirtudo(hash* hash1, int tamanhohash);
