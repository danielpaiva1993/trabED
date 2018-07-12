#include <stdio.h>
#include <memory.h>
#include"B+Tree.h"
#include"DataBasys.h"
int main(int argc, char *argv[]) {
    const int t = (int)argv[1][0]-48;
    char* file = argv[2];
    TABP* arvore ;
    int control=1,qf,d;
    char key[64],na[64];
    arvore = Inicializa();
    arvore = start_db(arvore,file,t);


    while(control != -1){

        printf(" Insira 2 para remover artista da playlist \n");
        printf(" Insira 3 para buscar informacoes subordinadas \n");
        printf(" Insira 4 para buscar obras \n");
        printf(" Insira 5 para alterar informacoes subordinadas \n");
        printf(" Insira 6 para imprimir a arvore \n");
        printf(" Insira -1 para sair \n");
        scanf("%d",&control);

        if(control == 2){
            printf("Digite o nome do artisa");
            getchar();
            scanf("%[^=\n]",key);
            arvore = remove_artista(arvore,key,t);

        }else if(control == 3 ){
            getchar();

            scanf("%[^=\n]",key);
            TABP* aux = busca_sub(arvore,key);
        }else if(control == 4 ){
            getchar();
            scanf("%[^=\n]",key);
            busca_obras(arvore,key,t);
        }else if(control == 5){
            printf(" digite a chave\n");
            getchar();
            scanf("%[^=\n]",key);
            printf(" digite o nome do album\n");
            getchar();

            scanf("%[^=\n]",na);
            printf("digite a quantidade de faixas e a duracao total do album\n");
            getchar();

            scanf("%d %d",&qf,&d);

            altera_sub(arvore,key,na,qf,d);

        }else if(control == 6){
            Imprime(arvore,0);
        }


    }

    return 0;
}