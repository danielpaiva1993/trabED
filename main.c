#include <stdio.h>
#include"B+Tree.h"
#include"DataBasys.h"
int main(int argc, char *argv[]) {

    const int t = (int)argv[1][0]-48;
    TABP* arvore = Inicializa();
    arvore = start_db(arvore,argv[2],t);
    Imprime(arvore,0);
//    TABP* a = Busca(arvore,"Cassia Eller2006");
//    Imprime(arvore,0);
//    altera_sub(arvore,"Cassia Eller2006","ehoq",1,1);
//    a = Busca(arvore,"Cassia Eller2006");
    remove_artista(arvore,"Red Hot",t);
//    remove_artista(arvore,"Cassia Eller",t);
//    remove_artista(arvore,"Cassia Eller",t);
    printf("\n\n");

    Imprime(arvore,0);


    return 0;
}