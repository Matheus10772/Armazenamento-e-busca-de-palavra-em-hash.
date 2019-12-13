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

hash* processararquivo(FILE* arq, hash* hash1, int tamanhohash) {
	/*Função responsável por processar todos as palavras contidas no arquivo.
	A função lê palavra por palavra e insere na hash uma a uma junto com a informação
	da linha onde ela estava.*/
	int contadorpalavra = 1;
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
				if (palavra[0] != '\0' && palavra[0] != '\n') {//garante o controle do que será inserido na hash
					hash1 = inserirnahash(arq, hash1, tamanhohash, indice, palavra, linha);
					contadorpalavra++;
				}
				//limpa o vetor auxiliar e reiniciar o processo para pegar a próxima palavra do arquivo.
				free(palavra);
				MAX_TAM = 24;
				indice = 0;
				palavra = malloc(sizeof(char) * MAX_TAM);
			}
		}
		hash1 = inserirnahash(arq, hash1, tamanhohash, indice, palavra, linha);
		contadorpalavra++;
		printf("\nO processamento do arquivo foi finalizado.\n Consulte o histórico acima para verificar se houve algum erro");
		printf("\nExistem %d palavras no arquivo", contadorpalavra);
	}
	else {
		printf("\nErro. Não existe uma hash ainda ou não esxiste nenhum arquivo aberto.\n");
	}
	return hash1;
}

hash* inserirnahash(FILE* arq, hash* hash1,int tamanhohash, int indice, char* palavra, int linha)
{   /*Recebe a palavra da função processar arquivo e insere em uma posição da hash mediante ao cálculo do mod hash.*/
	if(hash1 != NULL && arq != NULL){
		int mod = valormodhash(palavra, tamanhohash, indice);
		hash* aux = &hash1[mod];
		if(mod<=tamanhohash){
		while ((*aux).c != NULL) {//Para evitar colisões, esse laço de repetição cria uma lsita encadeada caso necessário.
				if ((*aux).prox == NULL) {
					(*aux).prox = (hash*)malloc(sizeof(hash));
				}
				aux = (*aux).prox;
				if((*aux).c == NULL){
				inicializarvalores(aux, 1);
				}
			}
		(*aux).c = malloc(sizeof(char) * indice);
		for (int j = 0; j <= indice ; j++) {//laço de repetição copia a palavra do vetor auxiliar para a estrutura na hash.
			(*aux).c[j] = palavra[j];
		}
		(*aux).tamanhopalavra = indice;//Coloca o tamanho da palavra na estrutura na hash.
		(*aux).linha = linha + 1;//Armazena em qual linha estava a palavra.
		(*aux).prox = NULL;
		return hash1;
		}
		else{
			printf("\nErro. Não existe essa posição na hash");
		}
	}
	else
	{
		printf("\nErro. Falha na hash ou no arquivo. Tente novamente");
		return hash1;
	}
	
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
    return modhash;
  }
  else{
    printf("\nErro. Não existe palavra para calcular o modhash");
    int valorreturn = tamanhohash + 1;
    return valorreturn;
  }
}

void consultarlinha(char* palavra, int tamanhohash, hash* hash1){
	//Função responsável por pesquisar a linha e quantas da palavra pesquisada existem na hash.
    int tamanhopalavra = 0; //armazena o tamanho da palavra procurada pelo usuário.
    char palavrastruct[47];//recebe a palavra que estava na estrutura dentro da hash.
    char palavraprocurada[47];//aramazena a palavra procurada pelo usuário.
    int posicaopalavra = 1;//contabiliza quanto de uma mesma palavra existe na hash.;
	int flag = 0; //verifica se existe na hash, ao menos uma vez, a palavra procurada.
    if(hash1 != NULL && palavra != NULL){
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
		if(strcmp(palavraprocurada,palavrastruct) == 0){
			printf("\n %dª palavra \"%s\": \n Linha: %d\n", posicaopalavra,(*aux).c,(*aux).linha);
			printf("\n");
			flag = 1;
			posicaopalavra++;
		}
		aux = (*aux).prox;
		}while(aux != NULL);
		if(flag == 0){printf("\nNão existe a palavra procurada na hash");}
	}
	else
	{
		printf("\nErro. Não foi possível acessar a hash ou a palavra. Tente novamente");
	}
}

void imprimirtudo(hash* hash1, int tamanhohash){//função responsável por imprimir toda a hash.
	hash* aux;
	for(int i = 0; i<tamanhohash; i++){
		aux = &hash1[i];
		int posicaopalavra = 1;//contabiliza quanto de uma mesma palavra existe na hash.
		do
		{
			printf("\n %dª palavra \"%s\": \n Linha: %d\n", posicaopalavra,(*aux).c,(*aux).linha);
			posicaopalavra++;
			aux = (*aux).prox;
		} while (aux != NULL);
	}
}
