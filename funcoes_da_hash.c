#include"cabecalho_da_hash.h"

hash* criarhash(hash* newhash,int tamanhohash){
  /*Função responsável por criar uma nova hash de tamanho pré-definido.
  A função recebe como parâmetro o tamanho da hash um ponteiro do tipo "hash".
  No final da execução, retorna o ponteiro para hash criada com os valores já devidamente inicializados */
    newhash = (hash*)malloc(sizeof(hash)*tamanhohash);
	  inicializarvalores(newhash, tamanhohash);
    //system("clear");
    printf("\nHash criada com sucesso. Tamanho alocado: 13 (padrão)\n");
    return newhash;
}

void inicializarvalores(hash* hash1, int tamanhohash){
  /*Inicializa os valores da hash criada.*/
	for (int i = 0; i < tamanhohash; i++) {
		(*(hash1+i)).c = NULL;
		(*(hash1+i)).prox = NULL;
	}
}

void processararquivo(FILE* arq, hash* hash1, int tamanhohash) {
	/*Função responsável por processar todos as palavras contidas no arquivo.
	A função lê palavra por palavra e insere na hash uma a uma junto com a informação
	da linha onde ela estava.*/
	if (hash1 != NULL && arq != NULL) {
		int MAX_TAM = 24;//variável auxiliar usada para criar um vetor de string dinâmico.
		char* palavra = malloc(sizeof(char) * MAX_TAM);
		int linha = 0;//variável utilizada para guardar na estrutura, junto com a palavra, a linha onde ela estava
		int indice = 0;//variável utilizada para saber o tamanho da palavra até o momento.
		char temp;
		while (!feof(arq))
		{//laço de repetição usado para armazenar a palvra do arquivo no vetor auxiliar.
			temp = fgetc(arq);
			if ((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z')) {
				if (indice > MAX_TAM) {
					MAX_TAM = MAX_TAM * 2;
					palavra = realloc(palavra, sizeof(char) * MAX_TAM);
				}
				palavra[indice] = temp;
				indice++;
			}
			else if (isspace(temp)) {
				//verifica se houve quebra de linha.
				if (temp == '\n') {
					linha++;
				}
				palavra[indice] = '\0';
				//printf("\n%s", palavra);
				if (palavra[0] != '\0' && palavra[0] != '\n') {//garante o controle do que será inserido na hash
					inserirnahash(arq, hash1, tamanhohash, indice, palavra, linha);
				}
				//limpa o vetor auxiliar e reiniciar o processo para pegar a próxima palavra do arquivo.
				free(palavra);
				MAX_TAM = 24;
				indice = 0;
				palavra = malloc(sizeof(char) * MAX_TAM);
			}
		}
		inserirnahash(arq, hash1, tamanhohash, indice, palavra, linha);
		printf("\nO processamento do arquivo foi finalizado.\n Consulte o histórico acima para verificar se houve algum erro");
	}
	else {
		printf("\nErro. Não existe uma hash ainda ou não esxiste nenhum arquivo aberto.\n");
	}
}

void inserirnahash(FILE* arq, hash* hash1,int tamanhohash, int indice, char* palavra, int linha)
{/*Recebe uma string contendo uma palavra e armazena na hash posição equivalente ao 
número obtido no cálculo do modhash da palavra.*/
  if(hash1 != NULL && arq != NULL){
  	int mod = valormodhash(palavra, tamanhohash, indice);
    if(mod <= tamanhohash){//verifica se existe uma posição na hash equivalente ao modhash.
    	hash* aux = &hash1[mod];
    	while ((*aux).c != NULL) {
        //laço de repetição verifica se já existe uma palavra inserida e cira uma lista encadeada na posição da hash se necessário.
			if ((*aux).prox == NULL) {
				(*aux).prox = (hash*)malloc(sizeof(hash));
        printf("\nAloca");
			}
    	aux = (*aux).prox;
		inicializarvalores(aux, 1);
    	}
    	(*aux).c = malloc(sizeof(char) * indice);
    	for (int j = 0; j <= indice ; j++) {
    		(*aux).c[j] = palavra[j];
    	}
      printf("\n%s ", (*aux).c);
    	(*aux).tamanhopalavra = indice;
		printf("\n%d ", (*aux).tamanhopalavra);
    	(*aux).linha = linha + 1;
		printf("\n%d ", (*aux).linha);
      //free(aux);
    }
  }
  else{printf("\nErro.Não existe hash ou nenhum arquivo foi aberto.");}
}

FILE* abrirarquivo(char arqname[]){
  /*Responsável por abrir verificar a disponibilidade do arquivo e carrega-lo na memória.*/
    FILE* arq = fopen(arqname, "r+");
    if(arq == NULL){
        //system("clear");
        printf("\nFalha ao acessar o arquivo. Pode estar sem permissão de acesso ou o arquivo ser inexistente\n");
    }
    //system("clear");
    printf("\nArquivo aberto com sucesso");
    return arq;
}

int valormodhash(char* palavra, int tamanhohash, int palavratamanho){
  /*Calcula o modhash da palavra.O modhash é calculado somando-se todos os valores 
das letra na tabela ASCII, dividindo-se pelo tamanho da hash e pegando o resto como resultado*/
  if(palavra != NULL){
    int temp;
    int soma = 0;//armazena a soma dos valores na tabela ASCII dos caracteres da palvra.
    char* palavraaux = palavra;
    for(int i = 0; i < palavratamanho; i++){
      //percorre toda a palvra somando os valores.
        temp = (int)palavraaux[i];
        soma = soma + temp;
    }
    int modhash = (soma%tamanhohash);
    printf("\nvalor modhash: %d", modhash);
    //free(palavraaux);
    return modhash;
  }
  else{
    printf("\nErro. Não existe palavra para calcular o modhash");
    int valorreturn = tamanhohash + 1;
    return valorreturn;
  }
}

void consultarlinha(char* palavra, int tamanhohash, hash* hash1){
    int percorrer = 0;
    int tamanhopalavra = 0;
    char palavrastruct[47];
    char palavraprocurada[47];
    int posicaopalavra = 1;
    while(palavra[tamanhopalavra] != '\0'){
      palavraprocurada[tamanhopalavra] = palavra[tamanhopalavra];
      tamanhopalavra++;
    }
    palavraprocurada[tamanhopalavra] = '\0';
    printf("\n%s palavra procurada", palavraprocurada);
    int modhash = valormodhash(palavra,tamanhohash,tamanhopalavra);
    hash* aux = &hash1[modhash];
    do{
      int indice = 0;
      while((*aux).c[indice] != '\0'){
        palavrastruct[indice] = (*aux).c[indice];
        indice++;
      }
      palavrastruct[indice]  = '\0';
      printf("\n%s palavra struct", palavrastruct);
      if(strcmp(palavraprocurada,palavrastruct) == 0){
        printf("\n %dª palavra \"%s\": \n Linha: %d\n", posicaopalavra,(*aux).c,(*aux).linha);
        printf("\n");
        posicaopalavra++;
      }
      aux = (*aux).prox;
    }while(1);
}
    
  /*Função responsável por pesquisar a linha e quantas da palavra pesquisada existem na hash.
  A função cria uma lista encadeada com cada posição uma contendo a linha e a quantidade 
  daquela palavra até o momento.
  int MAX_TAM = 5;//variável auxiliar usada alocar o vetor dinâmicamente. 
  rvetor* rvetor1 = malloc(sizeof(rvetor)*MAX_TAM);//lista encadeada usada para armazenar as informações da palavra procurada.
  if (hash1 != NULL && palavra != NULL) {
  	int indicerv = 0;//indice do vetor de armazenamento "rvtor".
		char palavraprocurar[47];//usado para armazenar a palavra procurada em um vetor não dinâmico. Necessário para usar na função strcmp.
		char palavrastruct[47];//usado para armazenar a palavra na struct em um vetor não dinâmico. Necessário para usar na função strcmp.
		int indice = 0;//indice da hash.
		int posicaopalavra = 1;//usada para definir quantas da palavra procurada existe na hash.
		int modhash;
		hash* aux;
		while (palavra[indice] != '\0')
		{ printf("\nEntrei aqui");
			palavraprocurar[indice] = palavra[indice];
			indice++;
		}
		modhash = valormodhash(palavra, tamanhohash, indice);
		aux = &hash1[modhash];
		printf("\nDepois do aux");
		do
		{
      aux = aux->prox;
			indice = 0;
			while (aux->c[indice] != '\0')
			{
				palavrastruct[indice] = aux->c[indice];
				indice++;
			}
			palavrastruct[indice] = '\0';
			if (strcmp(palavraprocurar, palavrastruct) == 0) {
        //compara se a palavra procurada, é equivalente a palavra na struct.
        //em caso afirmativo, armazena as informaçõe em "rvetor".
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
			//printf("\n%d próximo da struct", aux->prox);
		} while ((*aux).prox != 0);
    (*(rvetor1 + 0)).indicerv = indicerv;
  	return rvetor1;
	}
  else{
    printf("\nErro.Não existe hash ou a palavra procurada não foi inserida no vetor corretamente");
    printf("\nTente novamente");
    //free(rvetor1);
    //return rvetor1;
  }
}*/
