#include"hash.h"

int main(){
    int escolha=1, tamanhohash;
    char nome[30], busca[47];
    rvetor* rvetor2;
    FILE* arq;
    hash *intexto;
    while(escolha!=0){
        printf("\nMenu do Tp (Versao 1.0)\n");
        printf("\nEscolha uma opção:\n");
        printf("0 - Sair do programa\n");
        printf("1 - Criar hash\n");
        printf("2 - Abrir arquivo\n");
        printf("3 - Inserir na hash\n");
        printf("4 - Consultar linha\n");
        printf("\n");
        scanf("%d", &escolha);
    if(escolha == 1){
        printf("Qual o tamanho da hash?\n");
        scanf("%d",&tamanhohash);
        intexto = criarhash(intexto,tamanhohash);
    }
    else if(escolha == 2){
        printf("Qual e o nome do arquivo?\n");
        //fgets(nome,30,stdin);
        scanf("%s", nome);
        printf("\nNome escolhido: %s", nome);
        arq = abrirarquivo(nome);
    }
    else if(escolha == 3)
        inserirnahash(arq, intexto, tamanhohash);
    else if(escolha == 4){
        printf("Qual palavra deseja buscar?");
        //fgets(busca,47,stdin)
        scanf("%s",busca);
        rvetor2 = consultarlinha(busca, tamanhohash, intexto);
        printf("\nLinha: %d. Número: %d", (*rvetor2).linha,(*rvetor2).posicaopalavra);
    }
    else if(escolha == 0){
        exit(1);
    }
}
    return 0;
}
