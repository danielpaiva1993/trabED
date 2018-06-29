#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 3      // 1 < nc < 5

typedef struct arvm{
	int nchaves, folha;
	char chaves[2*T-1][60];
	//===================
	char *album;
	int nfaixas;
	int minutos;
	//===================
	struct arvm **filho, *antirmao, *proxirmao;
}TDISCO;

//=====================================Funções Auxiliares====================================

TDISCO* busca(TDISCO* a, char *chave){
	TDISCO* resp = NULL;

	if(!a) return resp;

	int i = 0;

	while((i < a->nchaves) && strcmp(chave, a->chaves[i]) > 0) i++;

	if((i < a->nchaves) && strcmp(chave, a->chaves[i]) == 0) return a;

	return busca(a->filho[i], chave);
}

TDISCO* remover(TDISCO* arv, char *ch){
  if(!arv) return arv;
  int i;
  for(i = 0; i < arv->nchaves && strcmp(arv->chaves[i], ch) < 0; i++);
  if(i < arv->nchaves && strcmp(ch, arv->chaves[i]) == 0){ //CASO 1
    if(arv->folha){ //CASO 1
      int j;
      for(j=i; j<arv->nchaves-1;j++)  strcpy(arv->chaves[j], arv->chaves[j+1]);      //arv->chaves[j] = arv->chaves[j+1];
      arv->nchaves--;
      return arv;      
    } 
  }

  TDISCO *y = arv->filho[i], *z = NULL;
  if (y->nchaves == T-1){ //CASOS 3A e 3B
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=T)){ //CASO 3A
      z = arv->filho[i+1];
      strcpy(y->chaves[T-1], arv->chaves[i]); //y->chaves[T-1] = arv->chaves[i];   //dar a y a chave i da arv
      y->nchaves++;
      strcpy(arv->chaves[i], z->chaves[0]); //arv->chaves[i] = z->chaves[0];     //dar a arv uma chave de z
      int j;
      for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
        strcpy(z->chaves[j], z->chaves[j+1]); //z->chaves[j] = z->chaves[j+1];
      //z->chave[j] = 0; Rosseti
      y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
      for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
        z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=T)){ //CASO 3A
      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
        strcpy(y->chaves[j], y->chaves[j-1]); //y->chaves[j] = y->chaves[j-1];
      for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
        y->filho[j] = y->filho[j-1];
      strcpy(y->chaves[0], arv->chaves[i-1]);  //y->chaves[0] = arv->chaves[i-1];    //dar a y a chave i da arv
      y->nchaves++;
      strcpy(arv->chaves[i-1], z->chaves[z->nchaves-1]); //arv->chaves[i-1] = z->chaves[z->nchaves-1];   //dar a arv uma chave de z
      y->filho[0] = z->filho[z->nchaves];         //enviar ponteiro de z para o novo elemento em y
      z->nchaves--;
      arv->filho[i] = remover(y, ch);
      return arv;
    }
    if(!z){ //CASO 3B
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == T-1){
        z = arv->filho[i+1];
        strcpy(y->chaves[T-1], arv->chaves[i]);  //y->chaves[T-1] = arv->chaves[i];     //pegar chave [i] e coloca ao final de filho[i]
        y->nchaves++;
        int j;
        for(j=0; j < T-1; j++){
          strcpy(y->chaves[T+j], z->chaves[j]);  //y->chaves[T+j] = z->chaves[j];     //passar filho[i+1] para filho[i]
          y->nchaves++;
        }
        if(!y->folha){
          for(j=0; j<T; j++){
            y->filho[T+j] = z->filho[j];
          }
        }
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
          strcpy(arv->chaves[j], arv->chaves[j+1]);  //arv->chaves[j] = arv->chaves[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == T-1)){ 
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          strcpy(z->chaves[T-1], arv->chaves[i-1]); //z->chaves[T-1] = arv->chaves[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          strcpy(z->chaves[T-1], arv->chaves[i]); //z->chaves[T-1] = arv->chaves[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < T-1; j++){
          strcpy(z->chaves[T+j], y->chaves[j]);  //z->chaves[T+j] = y->chaves[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<T; j++){
            z->filho[T+j] = y->filho[j];
          }
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch);
        return arv;
      }
    }
  }  
  arv->filho[i] = remover(arv->filho[i], ch);
  return arv;
}


//===========================================================================================

char *busca_album(TDISCO* a, char *chave){  // Os buscas retornam -1 se não encontrarem a chave dada como parâmetro!
	TDISCO* achado = busca(a, chave);
	if(!achado) return "-1";

	return achado->album;
}

int busca_faixas(TDISCO* a, char *chave){
	TDISCO* achado = busca(a, chave);
	if(!achado) return -1;

	return achado->nfaixas;
}

int busca_minutos(TDISCO* a, char *chave){
	TDISCO* achado = busca(a, chave);
	if(!achado) return -1;

	return achado->minutos;
}

void altera_album(TDISCO* a, char* chave, char* nome){
	TDISCO* achado = busca(a, chave);
	if(!achado) return;

	achado->album = nome;
}

void altera_faixas(TDISCO* a, char* chave, int faixas){
	TDISCO* achado = busca(a, chave);
	if(!achado) return;

	achado->nfaixas = faixas;
}

void altera_minutos(TDISCO* a, char* chave, int min){
	TDISCO* achado = busca(a, chave);
	if(!achado) return;

	achado->minutos = min;
}





int main(){
	char *str1, *str2;


	str1 = "renata";
	str2 = "renata ";
	printf("%d\n", strcmp(str1,str2));	

	return 0;

}