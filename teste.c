#include"hash.h"

hash* criarhash(hash* newhash,int tamanhohash){
    newhash = (hash*)malloc(sizeof(hash)*tamanhohash);
	  inicializarvalores(newhash, tamanhohash);
    system("clear");
    printf("\nHash criada com sucesso. Tamanho alocado: 13 (padrão)\n");
    return newhash;
}

void inicializarvalores(hash* hash1, int tamanhohash){
	for (int i = 0; i < tamanhohash; i++) {
		(*(hash1+i)).c = NULL;
		(*(hash1+i)).prox = 0;
	}
}

void processararquivo(FILE* arq,hash* hash1,int tamanhohash){
    if(hash1 != NULL && arq != NULL){
        char temp;
        int MAX_TAM = 5;
        char* palavra = malloc(sizeof(char)*MAX_TAM);
        int linha = 0;
        int indice = 0;
        while (!feof(arq))
        {
            temp = fgetc(arq);
            if((temp >= 97 && temp <= 122) || (temp >= 65 && temp <= 90)){
                if(indice > MAX_TAM){
                  MAX_TAM = MAX_TAM * 2;
                  palavra = realloc(palavra,sizeof(char)*MAX_TAM);
                }
                palavra[indice] = temp;
                indice++;
            }
            else if(isspace(temp)){
      				if (temp == '\n') {
      					linha++;
      				}
      				palavra[indice] = '\0';
      				if(palavra[0] != '\0' && palavra[0] != '\n')
      					inserirnahash(arq, hash1, tamanhohash, indice, palavra, linha);
      				free(palavra);
      				MAX_TAM = 5;
      				indice = 0;
      				palavra = malloc(sizeof(char) * MAX_TAM);
            }
        }
		inserirnahash(arq, hash1, tamanhohash, indice, palavra, linha);
    printf("\nO processamento do arquivo foi finalizado.\n Consulte o histórico acima para verificar se houve algum erro");
    }
    else{
        printf("\nErro. Não existe uma hash ainda ou não esxiste nenhum arquivo aberto.\n");
    }
}

void inserirnahash(FILE* arq, hash* hash1,int tamanhohash, int indice, char* palavra, int linha)
{
  if(hash1 != NULL && arq != NULL){
  	int mod = valormodhash(palavra, tamanhohash, indice);
    if(mod <= tamanhohash){
    	hash* aux = &hash1[mod];
    	while (aux->c != NULL) {
        if(aux->prox == NULL)
          aux->prox = (hash*)malloc(sizeof(hash));
    		aux = aux->prox;
    	}
    	aux->c = malloc(sizeof(char) * indice);
    	for (int j = 0; j <= indice ; j++) {
    		aux->c[j] = palavra[j];
    	}
    	aux->tamanhopalavra = indice + 1;
    	aux->linha = linha + 1;
      //free(aux);
    }
  }
  else{printf("\nErro.Não existe hash ou nenhum arquivo foi aberto.");}
}

FILE* abrirarquivo(char arqname[]){
    FILE* arq = fopen(arqname, "r+");
    if(arq == NULL){
        system("clear");
        printf("\nFalha ao acessar o arquivo. Pode estar sem permissão de acesso ou o arquivo ser inexistente\n");
    }
    system("clear");
    printf("\nArquivo aberto com sucesso");
    return arq;
}

int valormodhash(char* palavra, int tamanhohash, int palavratamanho){
  if(palavra != NULL){
    int temp;
    int soma = 0;
    char* palavraaux = palavra;
    for(int i = 0; i < palavratamanho; i++){
        temp = (int)palavraaux[i];
        soma = soma + temp;
    }
    int modhash = (soma%tamanhohash);
    //free(palavraaux);
    return modhash;
  }
  else{
    printf("\nErro. Não existe palavra para calcular o modhash");
    int valorreturn = tamanhohash + 1;
    return valorreturn;
  }
}

rvetor* consultarlinha(char* palavra, int tamanhohash, hash* hash1){
  int MAX_TAM = 5;
  rvetor* rvetor1 = malloc(sizeof(rvetor)*MAX_TAM);
  if (hash1 != NULL && palavra != NULL) {
  	int indicerv = 0;
		char palavraprocurar[47];
		char palavrastruct[47];
		int indice = 0;
		int posicaopalavra = 1;
    int modhash;
		hash* aux;
		while (palavra[indice] != '\0')
		{
			palavraprocurar[indice] = palavra[indice];
			indice++;
		}
		modhash = valormodhash(palavra, tamanhohash, indice);
		aux = &hash1[modhash];
		do
		{
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
				(*(rvetor1 + indicerv)).posicaopalavra = posicaopalavra;
				posicaopalavra++;
			}
			aux = aux->prox;
			indicerv++;
			printf("\n%d próximo da struct", aux->prox);
		} while ((*aux).prox != 0);
    (*(rvetor1 + 0)).indicerv = indicerv;
  	return rvetor1;
	}
  else{
    printf("\nErro.Não existe hash ou a palavra procurada não foi inserida no vetor corretamente");
    printf("\nTnte novamente");
    //free(rvetor1);
    //return rvetor1;
  }
}
