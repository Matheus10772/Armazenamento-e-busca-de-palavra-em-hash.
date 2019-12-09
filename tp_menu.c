#include"hash.h"

int main(){

      int escolha=1, tamanhohash = 13;
      char nome[30], busca[47];
      rvetor* rvetor2;
      FILE* arq;
      hash *intexto;

      while(escolha != 0){
          printf("\nMenu\n");
          printf(
          "*************************\n"
          "*ESCOLHA UMA OPÇÃO:     *\n"
          "*************************\n"
          "*0 - Sair do programa   *\n"
          "*1 - Criar hash         *\n"
          "*2 - Abrir arquivo      *\n"
          "*3 - Inserir na hash    *\n"
          "*4 - Consultar linha    *\n"
          "*************************\n"
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
        		rvetor2 = consultarlinha(busca, tamanhohash, intexto);
            system("clear");
        		int tamanho = (*(rvetor2 + 0)).indicerv;
        		for (int i = 0; i < tamanho; i++) {
        			printf("\n %dª palavra \"%s\": \n Linha: %d\n", rvetor2[i].posicaopalavra,busca,rvetor2[i].linha);
        		}
            break;
      case 0:
            system("clear");
            exit(1);
  }
}
      return 0;
}
