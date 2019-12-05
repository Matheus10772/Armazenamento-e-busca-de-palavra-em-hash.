#include"hash.h"

hash* criarhash(hash* newhash,int tamanhohash){
    newhash = (hash*)malloc(sizeof(hash)*tamanhohash);
    return newhash;
}

void inserirnahash(FILE* arq,hash* hash1,int tamanhohash){
    if(hash1 != NULL){
        char temp;
        char* palavra = (char*)malloc(sizeof(char)*5);
        int MAX_TAM = 5;
        int linha = 0;
        int indice = 0;
        hash* aux;
        int mod;
        while (!feof(arq))
        {
            temp = fgetc(arq);
            if((temp>'a' && temp<'z') || (temp>'A' && temp<'Z')){
                if(indice < MAX_TAM){
                palavra[indice] = temp;
                indice++;
                }
                else{
                    palavra = (char*)realloc(palavra,sizeof(char)*5);
                    palavra[indice] = temp;
                    indice++;
                    MAX_TAM = MAX_TAM + 5;

                }

            }
            else if(temp == ' '){
                mod = valormodhash(palavra,tamanhohash, indice);
                while((*hash1).c != NULL){
                    (*hash1).prox = (hash*)malloc(sizeof(hash));
                    hash1 = hash1->prox;
                }
                (*hash1).c = (char*)malloc(sizeof(char)*indice);
                /*for(int j=0;j<indice;j++){
                    hash1->(c[j]) = palavra[j];
                }*/
                (*hash1).c = palavra;
                indice++;
                (*hash1).tamanhopalavra = indice;
                (*hash1).linha = linha;
                free(palavra);
                MAX_TAM = 5;
                indice = 0;
                palavra = (char*)malloc(sizeof(char)*5);
            }
            else if(temp == '\n'){
                linha++;
            }
        }
    }
    else{
        printf("\nNão existe uma hash ainda. Crie uma nova.\n");
    }
}

FILE* abrirarquivo(char arqname[]){
    FILE* arq = fopen(arqname, "r+");
    if(arq == NULL){
        printf("\nErro ao abrir o arquivo. Falha ao acessar o arquivo. Pode estar sem permissão de acesso ou o arquivo ser inexistente\n");
    }
    return arq;
}

int valormodhash(char* palavra, int tamanhomodhash, int palavratamanho){
    int temp;
    int soma = 0;
    for(int i=0;i<palavratamanho;i++){
        temp = (int)palavra[i];
        soma = soma + temp;
    }
    int modhash = soma/tamanhomodhash;
    return modhash;
}

rvetor* consultarlinha(char* palavra, int tamanhohash, hash* hash1){
        rvetor* rvetor1 = (rvetor*)malloc(sizeof(rvetor)*2);
        char palavraprocurar[47];
        strcpy(palavraprocurar,palavra);
    if(hash1 != NULL){
        int palavratamanho;
        int i = 0;
        int MAX_TAM = 2;
        int indice = 0;
        while(palavra[i] != '\0'){
            palavratamanho++;
            i++;
        }
        int mod = valormodhash(palavra,tamanhohash,palavratamanho);
        hash aux = hash1[mod];
        int linha = aux.linha;
        int posicaopalavra = 0;
        if((strcmp((aux.c),palavraprocurar)) == 1){
        rvetor1[indice].posicaopalavra = posicaopalavra;
        rvetor1[indice].linha = linha;
        indice++;
        }
        posicaopalavra++;
        while(((*hash1).prox) != NULL){
            hash1 = (*hash1).prox;
            aux = *hash1;
            linha = aux.linha;
            if(indice>MAX_TAM){
                rvetor1 = (rvetor*)realloc(rvetor1,sizeof(int)*2);
                MAX_TAM = MAX_TAM + 2;
            }
            if((strcmp((aux.c),palavraprocurar)) == 1){
            rvetor1[indice].linha = linha;
            rvetor1[indice].posicaopalavra = posicaopalavra;
            indice++; 
            }
            posicaopalavra++;
        }
    }
    else
    {
        printf("\nNão existe hash\n");
        return NULL;
    }
    
    return rvetor1;
}