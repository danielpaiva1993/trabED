#include <bits/types/FILE.h>
#include <stdio.h>
#include <memory.h>
#include "B+Tree.h"
#include "DataBasys.h"


//
// Created by matheus on 29/06/18.
//
TABP* start_db(TABP* arvore,char*file,int t){
    char str[1024];
    char nome[128],album[128],ano[128];
    int duracao,qtd;


    FILE *fp = fopen(file , "r");

    fgets(str,1024,fp);

    do{
        sscanf(str,"%[^=/]/%[^=/]/%d/%d/%[^=\n]",nome,ano,&qtd,&duracao,album);
        strcat(nome,ano);
        arvore = Insere(arvore,nome,album,qtd,duracao,t);
        }
    while(fgets(str,1024,fp)!=NULL);
    fclose(fp);
    return arvore;
}

TABP* busca_sub(TABP* arvore,char* _chave){
    while(!arvore->f){
        arvore = arvore->filho[0];
    }
    int i=0;
    while(i < arvore->nc && strcmp(_chave , arvore->chave[i])<0) i++;
    if(i < arvore->nc && (strcmp(_chave , arvore->chave[i])==0)){
        printf("%d/%d/%s \n",arvore->qf[i],arvore->d[i],arvore->na[i]);
        return arvore;
    }else{
        return busca_sub(arvore->prox,_chave);
    }

}

void busca_obras(TABP* a, char* nome,int t){
    TABP* arvore = a,*aux=a;
    while(!arvore->f){
        arvore = arvore->filho[0];
    }
    printf("Nome do Album | Quantidade de faixas | Duração do album \n\n");
    while(arvore) {
        int i = 0;
        while(i<arvore->nc){
            if(in(nome,arvore->chave[i])) {
                printf("%s | %d | %d | \n" , arvore->na[i] ,arvore->qf[i],arvore->d[i]);
            }
            i++;
        }
        arvore = arvore->prox;
    }
}
void altera_sub(TABP* arvore,char* _chave,char* _na, int _qf, int _d){
    TABP* aux = Busca(arvore,_chave);
    int i = 0;
//    TABP* aux2 = arvore;
//    int i = 0,j =0;
//    while(1){
//        if(arvore -> filho[i] == aux) break;
//
//    }
    while(i < aux->nc && strcmp(_chave , aux->chave[i])>0) i++;

    aux->na[i] =_na;
    aux->d[i] = _d;
    aux->qf[i] = _qf;
    aux->d[i] = _d;


}
int in(char* a1, char* a2){
    int i =0;

    while(a1[i] != '\0' && a2[i] != '\0' && a1[i] == a2[i]){
        i++;
    }
    if(a1[i] == '\0'){
        return 1;
    }
    return 0;
}

TABP* remove_artista(TABP* a,char* nome,int t){
    TABP* arvore = a,*aux=a;
    while(!arvore->f){
        arvore = arvore->filho[0];
    }
    while(arvore) {
        int i = 0;
        while(i<arvore->nc){
            if(in(nome,arvore->chave[i])){
                aux = Remover(aux,arvore->chave[i],t);
                if(!Busca(aux,arvore->chave[i]))break;
                i--;
            }
            i++;
        }
        arvore = arvore->prox;
    }
    return aux;
}