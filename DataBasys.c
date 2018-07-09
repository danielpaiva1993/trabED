#include <bits/types/FILE.h>
#include <stdio.h>
#include <memory.h>
#include "B+Tree.h"
#include "DataBasys.h"


//
// Created by matheus on 09/07/18.
//
TABP* start_db(TABP* arvore,char*file,int t){
    char str[1024];
    char nome[128],album[128],ano[128];
    int duracao,qtd;


    FILE *fp = fopen(file , "r");

    fgets(str,1024,fp);

    do{
        sscanf(str,"%[^=/]/%[^=/]/%d/%d/%[^=\n]",nome,ano,&qtd,&duracao,album);
//        printf("%s/%s/%d/%d/%s \n",nome,ano,qtd,duracao,album);
        strcat(nome,ano);
        arvore = Insere(arvore,nome,album,qtd,duracao,t);
//        Imprime(arvore,0);
//        printf("\n");
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
        i = 0;
        return busca_sub(arvore->prox,_chave);
    }

}

void altera_sub(TABP* arvore,char* _chave,char* _na, int _qf, int _d){
    TABP* sub = Busca(arvore,_chave);
    if(!sub){
        return;
    }
    int i = 0;
    while(i < arvore->nc && strcmp(_chave , arvore->chave[i])>0) i++;

    sub->na[i] =_na;
    sub->d[i] = _d;
    sub->qf[i] = _qf;
    sub->d[i] = _d;

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
    TABP* arvore = a;
    while(!arvore->f){
        arvore = arvore->filho[0];
    }
    while(arvore) {
        int i = 0;
        while(i<arvore->nc){
            if(in(nome,arvore->chave[i])){
                a = Remover(a,arvore->chave[i],t);
                i--;

            }
            i++;
        }
        arvore = arvore->prox;
    }
}