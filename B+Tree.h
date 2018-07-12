//
// Created by matheus on 29/06/18.
//

#ifndef B_INDEXING_B_TREE_H
#define B_INDEXING_B_TREE_H
typedef struct arvbplus{
    char **chave;
    int nc,f;

    char **na;
    int *qf,*d;


    struct arvbplus *prox,*prev;

    struct arvbplus **filho;


}TABP;

TABP *Cria(int t);
TABP* Busca(TABP* arvore,char* chave);
TABP *Cria_folha(int t);
TABP *Libera(TABP* a);
TABP* Inicializa();
TABP* Divide_folha(TABP* p, TABP* f,int i, int t);
TABP* Divisao(TABP* p, TABP* f,int i ,int t);
TABP* Remover(TABP* p , char* _chave,int t);
TABP* Insere(TABP* p,char* _chave, char* _na, int _qf, int _d ,int t );
TABP* Insere_nao_completo(TABP* p, char* chave,char* _na, int _qf, int _d,int t);
void Imprime(TABP* a,int i);
#endif //B_INDEXING_B_TREE_H
