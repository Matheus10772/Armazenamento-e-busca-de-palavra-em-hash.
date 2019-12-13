#include"cabecalho_da_hash.h"

int main(){

        int escolha = 1, tamanhohash = 13;
        char nome[30], busca[47];
        rvetor* rvetor2;
        FILE* arq;
        hash *intexto;

        while(1){
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
                system("clear");
                intexto = criarhash(intexto,tamanhohash);
                break;
            case 2:
            system("clear");
                printf("Qual e o nome do arquivo?\n");
                scanf("%s", nome);
                printf("\nNome escolhido: %s", nome);
                arq = abrirarquivo(nome);
                break;
            case 3:
                system("clear");
                intexto = processararquivo(arq, intexto, tamanhohash);
                break;
            case 4:
                system("clear");
                printf("Qual palavra deseja buscar?");
                scanf("%s",busca);
                consultarlinha(busca,tamanhohash,intexto);
                break;
            case 5:
                system("clear");
                imprimirtudo(intexto,tamanhohash);
                break;
        case 0:
                exit(1);
                break;
        default:
          system("clear");
          printf("\nOpção inválida. Tente novamente");
        
        }
    }
        return 0;
}
