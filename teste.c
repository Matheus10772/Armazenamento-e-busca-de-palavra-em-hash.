#include"hash.h"

hash* criarhash(hash* newhash,int tamanhohash){
    newhash = (hash*)malloc(sizeof(hash)*tamanhohash);
	inicializarvalores(newhash, tamanhohash);
    return newhash;
}

void inicializarvalores(hash* hash1, int tamanhohash){
	for (int i = 0; i < tamanhohash; i++) {
		(*(hash1+i)).c = NULL;
		(*(hash1+i)).prox = 0;
	}
}

void processararquivo(FILE* arq,hash* hash1,int tamanhohash){
    if(hash1 != NULL){
        char temp;
        int MAX_TAM = 5;
        char* palavra = malloc(sizeof(char)*MAX_TAM);
        int linha = 0;
        int indice = 0;
        while (!feof(arq))
        {
            temp = fgetc(arq);
			/*printf("\n caracter: %c\n", temp);
			system("pause");*/
            if((temp >= 97 && temp <= 122) || (temp >= 65 && temp <= 90)){
                if(indice < MAX_TAM){
                palavra[indice] = temp;
                }
                else{
					MAX_TAM = MAX_TAM * 2;
                    palavra = realloc(palavra,sizeof(char)*MAX_TAM);
                    palavra[indice] = temp;
                }
                indice++;
            }
            else if(isspace(temp)){
				if (temp == '\n') {
					linha++;
				}
				palavra[indice] = '\0';
				if(palavra[0] != '\0')
					inserirnahash(arq, hash1, tamanhohash, indice, palavra, linha);
				free(palavra);
				MAX_TAM = 5;
				indice = 0;
				palavra = malloc(sizeof(char) * MAX_TAM);
            }
        }
		inserirnahash(arq, hash1, tamanhohash, indice, palavra, linha);
    }
    else{
        printf("\nNão existe uma hash ainda. Crie uma nova.\n");
    }
}

void inserirnahash(FILE* arq, hash* hash1,int tamanhohash, int indice, char* palavra, int linha)
{
	int mod;
	printf("\n%s\n", palavra);
	//system("pause");
	getchar();
	mod = valormodhash(palavra, tamanhohash, indice);
	hash* aux = hash1;
	while (aux[mod].c != NULL) {
		aux[mod].prox = (hash*)malloc(sizeof(hash));
		aux = aux[mod].prox;
	}
	aux->c = malloc(sizeof(char) * indice);
	for (int j = 0; j <= indice ; j++) {
		aux->c[j] = palavra[j];
	}
	printf("\n%s bonitinho", aux->c);
	//system("pause");
	getchar();
	aux->tamanhopalavra = indice + 1;
	aux->linha = linha + 1;
	printf("\nlinha %d bonitinho", aux->linha);
	getchar();
}

FILE* abrirarquivo(char arqname[]){
    FILE* arq = fopen(arqname, "r+");
    if(arq == NULL){
        printf("\nFalha ao acessar o arquivo. Pode estar sem permissão de acesso ou o arquivo ser inexistente\n");
    }
    return arq;
}

int valormodhash(char* palavra, int tamanhomodhash, int palavratamanho){
	int temp;
    int soma = 0;
	char* palavraaux = palavra;
    for(int i = 0; i < palavratamanho; i++){

        temp = (int)palavraaux[i];
        soma = soma + temp;
		printf("\nSoma: %d", soma);
    }
	printf("\ntamanhohash: %d", tamanhomodhash);
    int modhash = (soma%tamanhomodhash);
	printf("\n%d valor modhash", modhash);
    return modhash; 
}

rvetor* consultarlinha(char* palavra, int tamanhohash, hash* hash1){
	int MAX_TAM = 5;
	int indicerv = 0;
    rvetor* rvetor1 = malloc(sizeof(rvetor)*MAX_TAM);
	if (hash1 != NULL) {
		printf("\nEntrei no if");
		char palavraprocurar[47];
		char palavrastruct[47];
		int indice = 0;
		int posicaopalavra = 1;
		hash* aux;
		while (palavra[indice] != '\0')
		{
			palavraprocurar[indice] = palavra[indice];
			indice++;
			printf("\n1º while");
		}
		int modhash = valormodhash(palavra, tamanhohash, indice);
		aux = &hash1[modhash];
		do
		{
			printf("\nAqui oh");
			indice = 0;
			while (aux->c[indice] != '\0')
			{
				palavrastruct[indice] = aux->c[indice];
				indice++;
			}
			palavrastruct[indice] = '\0';
			if (strcmp(palavraprocurar, palavrastruct) == 0) {
				if (indicerv > MAX_TAM) {
					MAX_TAM = MAX_TAM * 2;
					rvetor1 = realloc(rvetor1,sizeof(rvetor)*MAX_TAM);
				}
				(*(rvetor1 + indicerv)).linha = aux->linha;
				printf("\nconsult linha %d", (*(rvetor1 + indicerv)).linha);
				(*(rvetor1 + indicerv)).posicaopalavra = posicaopalavra;
				posicaopalavra++;
			}
			aux = aux->prox;
			indicerv++;
			printf("\n%d próximo da struct", aux->prox);
		} while ((*aux).prox != 0);
	}
	(*(rvetor1 + 0)).indicerv = indicerv;
	return rvetor1;
}