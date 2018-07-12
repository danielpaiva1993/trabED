//
// Created by matheus on 29/06/18.
//

#include "B+Tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

TABP* Cria(int t){
    TABP *new = (TABP*)malloc(sizeof(TABP));
    new->filho = (TABP**)malloc(sizeof(TABP*)*t*2);
    new->chave =(char**)malloc(sizeof(char*)*((t*2)-1));
    new->prev = NULL;
    new->prox = NULL;
    int i;

    for(i=0; i<(t*2); i++) new->filho[i] = NULL;
    for(i = 0 ; i <2*t -1;i++){
        new->chave[i] = (char*)malloc(sizeof(char)*64);
    }
    new-> nc =0;
    new->f = 0;

    return new;
}
TABP* Cria_folha(int t){
    TABP* new = Cria(t);
    int i;
    new->na =(char**)malloc(sizeof(char*)*((t*2)-1));
    for(i = 0 ; i <2*t -1;i++){
        new->na[i] = (char*)malloc(sizeof(char)*64);
    }
    new->f=1;

    new->qf =(int*)malloc(sizeof(int*)*((t*2)-1));
    new->d =(int*)malloc(sizeof(int*)*((t*2)-1));

    return new;
}
void Imprime(TABP *a, int andar){
    if(a){
        int i,j;
        for(i=0; i<=a->nc-1; i++){
            Imprime(a->filho[i],andar+1);
            for(j=0; j<=andar; j++) printf("                   ");
            if(a->f)            printf("%s %s %d %d\n", a->chave[i],a->na[i],a->d[i],a->qf[i]);
            else             printf("%s\n", a->chave[i]);

        }
        Imprime(a->filho[i],andar+1);
    }
}
TABP* Busca(TABP* x, char* ch){
    TABP *resp = NULL;
    if(!x) return resp;
    int i = 0;
    while(i < x->nc && strcmp(ch , x->chave[i])>0) i++;
    if(i < x->nc && (strcmp(ch , x->chave[i])==0) && !x->f) {
        return Busca(x->filho[i+1], ch);
    }
    if(i < x->nc && (strcmp(ch , x->chave[i])==0) && x->f){
        return x;
    }
    if(x->f) return resp;
    return Busca(x->filho[i], ch);
}
TABP* Inicializa(){
    return NULL;
}

TABP* Divide_folha(TABP *p,TABP*f,int i, int t){
    TABP *novo=Cria_folha(t);

    if(f->prox){
        f->prox->prev = novo;
        novo->prox = f->prox;
    }
    f->prox = novo;
    novo->prev = f;

    novo->nc= t;
    int j;
    for(j=0;j< t;j++) {
        strcpy(novo->chave[j] , f->chave[j+t-1]);
        strcpy(novo->na[j] , f->na[j+t-1]);
        novo->d[j] = f->d[j+t-1];
        novo->qf[j] = f->qf[j+t-1];

    }
    f->nc = t-1;
    for(j=p->nc; j>=i; j--) p->filho[j+1]=p->filho[j];
    p->filho[i] = novo;
    for(j=p->nc; j>=i; j--) strcpy(p->chave[j] , p->chave[j-1]);
    strcpy(p->chave[i-1] ,f->chave[t-1]);

    p->nc++;
    return p;

}
TABP *Divisao(TABP* p, TABP* f,int i , int t){
    if(f->f) return Divide_folha(p,f,i,t);

    TABP *novo=Cria(t);

    novo->nc = t-1;
    novo->f = f->f;
    int j;

    for(j=0;j<t-1;j++) {
        strcpy(novo->chave[j] , f->chave[j+t]);
    }
    for(j=0;j<t;j++){
        novo->filho[j] = f->filho[j+t];
        f->filho[j+t] = NULL;
    }
    f->nc = t-1;
    for(j=p->nc; j>=i; j--) p->filho[j+1]=p->filho[j];
    p->filho[i] = novo;
    for(j=p->nc; j>=i; j--) strcpy(p->chave[j] , p->chave[j-1]);
    strcpy(p->chave[i-1] ,f->chave[t-1]);
    p->nc++;
    return p;
}


TABP* Insere_nao_completo(TABP* p, char* chave,char* _na, int _qf, int _d,int t){
    int i = p->nc-1;
    if(p->f){
        while((i>=0) && (strcmp(chave,p->chave[i])< 0 )){
            strcpy(p->chave[i+1] , p->chave[i]);
            strcpy(p->na[i+1],p->na[i]);
            p->qf[i+1] = p ->qf[i];
            p->d[i+1] = p->d[i];
            i--;
        }
        strcpy(p->chave[i+1],chave);
        strcpy(p->na[i+1],_na);
        p->qf[i+1] = _qf;
        p->d[i+1] = _d;
        p->nc++;
        return p;
    }
    while((i>=0) && strcmp(chave,p->chave[i])<0 ) i--;
    i++;
    if(p->filho[i]->nc == ((2*t)-1)){
        p = Divisao(p, p->filho[i], (i+1), t);
        if(strcmp(chave,p->chave[i])>0 ) i++;
    }
    p->filho[i] = Insere_nao_completo(p->filho[i],chave,_na,_qf,_d, t);
    return p;
}
TABP* Insere(TABP* p,char* _chave, char* _na, int _qf, int _d ,int t ){
    if(Busca(p,_chave)){
        return p;
    }
    if(!p){
        p = Cria_folha(t);
        strcpy(p->chave[0],_chave);
        strcpy(p->na[0],_na);
        p->qf[0] = _qf;
        p->d[0] = _d;
        p->nc++;
        return p;
    }if(p->nc ==2*t-1){
        TABP* pai = Cria(t);
        pai->filho[0] = p;
        pai = Divisao(pai,p,1,t);
        pai = Insere_nao_completo(pai,_chave,_na,_qf,_d,t);
        return pai;
    }
    p = Insere_nao_completo(p,_chave,_na,_qf,_d,t);
    return p;
}


TABP* Remover(TABP* p , char* _chave,int t){
    if(!p) return p;
    int i;
    printf("Removendo %s...\n", _chave);
    for(i = 0; i<p->nc && strcmp(p->chave[i] , _chave) < 0; i++);
    if(i < p->nc && strcmp(_chave ,p->chave[i]) == 0){ //CASOS 1, 2A, 2B e 2C
        if(p->f){ //CASO 1
            printf("\nCASO 1\n");
            int j;
            for(j=i; j<p->nc-1;j++){
                strcpy(p->chave[j], p->chave[j+1]);
                strcpy(p->na[j],p->na[j+1]);
                p->qf[j] = p->qf[j+1];
                p->d[j] = p->d[j+1];
            }
            p->nc--;
            return p;
        }
        else {
            i++;
        }
    }
    TABP *y = p->filho[i], *z = NULL;
    if (y->nc == t-1){ //CASOS 3A e 3B
        if((i < p->nc) && (p->filho[i+1]->nc >=t)){ //CASO 3A
            printf("\nCASO 3A: i menor que nchaves\n");
            z = p->filho[i+1];
            if(y->f){
                strcpy(y->chave[t-1] , z->chave[0]);
                strcpy(y->na[t-1],z->na[0]);
                y->qf[t-1] = z->qf[0];
                y->d[t-1] = z->d[0];

                strcpy(p->chave[i],z->chave[1]);

            }
            else{
                strcpy(y->chave[t-1] , p->chave[i]);
                strcpy(p->chave[i],z->chave[i]);
            }


            y->nc++;
            int j;
            if(z ->f) {
                for (j = 0; j < z->nc - 1; j++) {
                    strcpy(z->chave[j], z->chave[j + 1]);
                    strcpy(z->na[j], z->na[j + 1]);
                    z->qf[j] = z->qf[j + 1];
                    z->d[j] = z->d[j + 1];
                }
            }else{
                for (j = 0; j < z->nc - 1; j++) {
                    strcpy(z->chave[j], z->chave[j + 1]);
                }
            }


            y->filho[y->nc] =  z->filho[0];
            for(j=0; j < z->nc; j++)
                z->filho[j] = z->filho[j+1];
            z->nc--;


            if(strcmp(p->chave[i] ,_chave) == 0){
                p->filho[i+1] = Remover(p->filho[i+1], _chave, t);
            }

            p->filho[i] = Remover(p->filho[i], _chave, t);
            return p;
        }
        if((i > 0) && (!z) && (p->filho[i-1]->nc >=t)){ //CASO 3A
            printf("\nCASO 3A: i igual a nchaves\n");
            z = p->filho[i-1];
            int j;
            for(j = y->nc; j>0; j--)
                strcpy(y->chave[j], y->chave[j-1]);
            for(j = y->nc+1; j>0; j--)
                y->filho[j] = y->filho[j-1];
            if(!y->f)strcpy(y->chave[0] , p->chave[i-1]);

            else {
                strcpy(y->chave[0], z->chave[z->nc-1]);
                strcpy(y->na[0], z->na[z->nc-1]);
                y->qf[0] = z->qf[z->nc-1];
                y->d[0] = z->d[z->nc-1];
            }

            y->nc++;
            strcpy(p->chave[i-1] , z->chave[z->nc-1]);
            y->filho[0] = z->filho[z->nc];
            z->nc--;
            p->filho[i] = Remover(y, _chave, t);
            return p;
        }
        if(!z){ //CASO 3B
            if(i < p->nc && p->filho[i+1]->nc == t-1){
                printf("\nCASO 3B: i menor que nchaves\n");
                z = p->filho[i+1];
                int j;
                if(!y->f){
                    strcpy(y->chave[t-1] , p->chave[i]);
                    y->nc++;
                    for(j=0; j < t-1; j++){
                        strcpy(y->chave[t+j] , z->chave[j]);
                        y->nc++;
                    }
                }
                else{
                    for(j=0; j < t-1; j++){
                        strcpy(y->chave[t-1+j] , z->chave[j]);
                        strcpy(y->na[t-1+j] , z->na[j]);
                        y->d[t+j-1] = z->d[j];
                        y->qf[t+j-1] = z->qf[j];
                        y->nc++;
                    }
                }
                if(y->f){

                    y->prox = z->prox;
                    if(z->prox){
                        z->prox->prev = y;
                    }

                }
                if(!y->f){
                    for(j=0; j<t; j++){
                        y->filho[t+j] = z->filho[j];
                    }
                }
                for(j=i; j < p->nc-1; j++){
                    strcpy(p->chave[j],p->chave[j+1]);
                    p->filho[j+1] = p->filho[j+2];
                }
                p->nc--;
                p = Remover(p, _chave, t);
                return p;
            }
            if((i > 0) && (p->filho[i-1]->nc == t-1)){
                printf("\nCASO 3B: i igual a nchaves\n");
                z = p->filho[i-1];
                int j;
                if(!y->f){
                    if(i == p->nc)
                        strcpy(z->chave[t-1] , p->chave[i-1]);
                    else
                        strcpy(z->chave[t-1] , p->chave[i]);
                    z->nc++;
                    for(j=0; j < t-1; j++){
                        strcpy(z->chave[t+j] , y->chave[j]);
                        z->nc++;
                    }
                }
                else{
                    for(j=0; j < t-1; j++){
                        strcpy(z->chave[t+j-1] , y->chave[j]);
                        strcpy(z->na[t+j-1] , y->na[j]);
                        z->qf[t+j-1] = y->qf[j];
                        z->d[t+j-1] = y->d[j];
                        z->nc++;
                    }
                }

                if(z->f){

                    z->prox = y->prox;
                    if(y->prox){
                        y->prox->prev = z;
                    }
                }

                if(!z->f){
                    for(j=0; j<t; j++){
                        z->filho[t+j] = y->filho[j];
                    }
                }
                p->nc--;
                p->filho[i-1] = z;
                p = Remover(p, _chave, t);
                return p;
            }
        }
    }
    p->filho[i] = Remover(p->filho[i], _chave, t);
    return p;
}
