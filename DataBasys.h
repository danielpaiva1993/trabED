//
// Created by matheus on 09/07/18.
//

#ifndef B_INDEXING_DATABASYS_H
#define B_INDEXING_DATABASYS_H
#include "B+Tree.h"

TABP* start_db(TABP* arvore,char*file,int t);
TABP* remove_artista(TABP* arvore,char* _chave,int t);
void altera_sub(TABP* arvore,char* _chave,char* _na, int _qf, int _d);

int in(char* a1, char* a2);

#endif //B_INDEXING_DATABASYS_H
