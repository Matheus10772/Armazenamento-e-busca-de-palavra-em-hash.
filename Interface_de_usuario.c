#include"cabecalho_da_hash.h"

int main(){

      int escolha = 1, tamanhohash = 13;
      char nome[30], busca[47];
      rvetor* rvetor2;
      FILE* arq;
      hash *intexto;

      while(escolha != 0){
          printf("\nMenu\n");
          printf(
          "*****************************************\n"
          "*ESCOLHA UMA OPÇÃO:                     *\n"
          "*****************************************\n"
          "*0 - Sair do programa                   *\n"
          "*1 - Criar hash                         *\n"
          "*2 - Abrir arquivo                      *\n"
          "*3 - Inserir todo o arquivo na hash     *\n"
          "*4 - Consultar linha                    *\n"
          "*5 - Imprimir toda a hash               *\n"
          "*****************************************\n"
          );
          printf("\n");
          scanf("%d", &escolha);
      switch (escolha) {
        case 1:
            intexto = criarhash(intexto,tamanhohash);
            break;
        case 2:
            printf("Qual e o nome do arquivo?\n");
            scanf("%s", nome);
            printf("\nNome escolhido: %s", nome);
            arq = abrirarquivo(nome);
            break;
        case 3:
            processararquivo(arq, intexto, tamanhohash);
            break;
        case 4:
            printf("Qual palavra deseja buscar?");
            scanf("%s",busca);
            consultarlinha(busca,tamanhohash,intexto);
            break;
        /*case 5:
            for(percorrer = 0;percorrer < tamanhohash;percorrer++){
                aux = &intexto[percorrer];
                while(aux->prox != 0){
                    while(aux->c[indice] != '\0'){
                        busca[indice] = aux->c[indice];
                        indice++;
                    }
                    rvetor2 = consultarlinha(busca, tamanhohash, intexto);
                    printf("\n%dª palavra \"%s\": , na linha %d\n",rvetor2->posicaopalavra,aux->c,aux->tamanhopalavra);
                    printf("\n");
                }
                indice = 0;
            }
            break;*/
      case 0:
            //system("clear");
            exit(1);
  }
}
      return 0;
}
