#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int t = 3;      // 2 < nc < 5

typedef struct arvm{
	int nchaves, folha;
	char **chaves;
	//===================
	char *album;
	int nfaixas;
	int minutos;
	//===================
	struct arvm **filho, *antirmao, *proxirmao;
}TDISCO;


//=====================================Funções Auxiliares====================================

TDISCO* busca(TDISCO* a, char *chave){
	if(!a) return a;

	int i = 0;

	while((i < a->nchaves) && strcmp(chave, a->chaves[i]) > 0) i++;

	if((i < a->nchaves) && strcmp(chave, a->chaves[i]) == 0 && a->folha) return a;

	if((i < a->nchaves) && strcmp(chave, a->chaves[i]) == 0 && !a->folha) return busca(a->filho[i+1], chave);

	return busca(a->filho[i], chave);
}

TDISCO* remover(TDISCO* arv, char *ch, int T){
  if(!arv) return arv;
  int i;
  for(i = 0; i < arv->nchaves && strcmp(arv->chaves[i], ch) < 0; i++);
  if(i < arv->nchaves && strcmp(ch, arv->chaves[i]) == 0){ //CASO 1
    if(arv->folha){ //CASO 1
      int j;
      for(j=i; j<arv->nchaves-1;j++)  strcpy(arv->chaves[j], arv->chaves[j+1]);
      arv->nchaves--;
      return arv;      
    } 
  }

  TDISCO *y = arv->filho[i], *z = NULL;
  if (y->nchaves == T-1){ //CASOS 3A e 3B
    if(y->folha){
	    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=T)){ //CASO 3A
	      z = arv->filho[i+1];
	      strcpy(y->chaves[T-1], z->chaves[0]); //y->chaves[T-1] = arv->chaves[i];   //dar a y a chave i da arv
	      y->nchaves++;
	      strcpy(arv->chaves[i], z->chaves[1]);
	      int j;
	      for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
	        strcpy(z->chaves[j], z->chaves[j+1]); //z->chaves[j] = z->chaves[j+1];
	      
	      y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
	      for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
	        z->filho[j] = z->filho[j+1];
	      z->nchaves--;
	      arv->filho[i] = remover(arv->filho[i], ch, T);
	      return arv;
	    }
	    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=T)){ //CASO 3A
	      z = arv->filho[i-1];
	      int j;
	      for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
	        strcpy(y->chaves[j], y->chaves[j-1]); //y->chaves[j] = y->chaves[j-1];
	      for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
	        y->filho[j] = y->filho[j-1];
	      strcpy(y->chaves[0], z->chaves[z->nchaves-1]);  //y->chaves[0] = arv->chaves[i-1];    //dar a y a chave i da arv
	      y->nchaves++;
	      strcpy(arv->chaves[i-1], z->chaves[z->nchaves-1]); //arv->chaves[i-1] = z->chaves[z->nchaves-1];   //dar a arv uma chave de z
	      y->filho[0] = z->filho[z->nchaves];         //enviar ponteiro de z para o novo elemento em y
	      z->nchaves--;
	      arv->filho[i] = remover(y, ch, T);
	      return arv;
	    }
    }

    if(!y->folha){
    	if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=T)){ //CASO 3A
	       z = arv->filho[i+1];
	       strcpy(y->chaves[T-1], arv->chaves[i]);   //dar a y a chave i da arv
	       y->nchaves++;
	       strcpy(arv->chaves[i], z->chaves[0]);     //dar a arv uma chave de z
	       int j;
	       for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
	          strcpy(z->chaves[j], z->chaves[j+1]);
	       y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
	       for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
	          z->filho[j] = z->filho[j+1];
	       z->nchaves--;
	       arv->filho[i] = remover(arv->filho[i], ch, T);
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
      		arv->filho[i] = remover(y, ch, T);
      		return arv;
    	}
    }
    
    if(!z){ //CASO 3B
      if(!y->folha){
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
	        arv = remover(arv, ch, T);
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
	        arv = remover(arv, ch, T);
	        return arv;
	      }
	   }

	   if(y->folha){
	   	  if(i < arv->nchaves && arv->filho[i+1]->nchaves == T-1){
	   	  	z = arv->filho[i+1];
	   	  	int k;
	   	  	int m = 0;
	   	  	for(k = T-1; k < 2*T-1 && m < T-1;k++){
	    		strcpy(y->chaves[k], z->chaves[m]);
	    		y->nchaves++;
	    		z->nchaves--;
	    		m++;	
	    	}

	    	y->proxirmao = z->proxirmao;

	    	int l;
	    	for(l = i; l < arv->nchaves-1;l++)
	    		strcpy(arv->chaves[l], arv->chaves[l+1]);

	    	int p;
	    	for(p = i; p < arv->nchaves;p++)
	    		arv->filho[p] = arv->filho[p+1];
	    	
	    	arv->nchaves--;
	    	arv = remover(arv, ch, T);

	   	  }

	   	  if(i < arv->nchaves && arv->filho[i-1]->nchaves == T-1){
	   	  	z = arv->filho[i-1];
	   	  	int k;
	   	  	int m = 0;
	   	  	for(k = T-1; k < 2*T-1 && m < T-1;k++){
	    		strcpy(z->chaves[k], y->chaves[m]);
	    		z->nchaves++;
	    		y->nchaves--;
	    		m++;	
	    	}

	    	z->proxirmao = y->proxirmao;

	    	int l;
	    	for(l = i; l < arv->nchaves-1;l++)
	    		strcpy(arv->chaves[l], arv->chaves[l+1]);

	    	int p;
	    	for(p = i; p < arv->nchaves;p++)
	    		arv->filho[p] = arv->filho[p+1];
	    	
	   	  	arv->nchaves--;
	    	arv = remover(arv, ch, T);

	   	  }
	   }   
    }
  }  
  arv->filho[i] = remover(arv->filho[i], ch, T);
  return arv;
}


TDISCO* Divisao_folha(TDISCO *pai, int i, TDISCO *filho, int t){
    TDISCO *aux = Cria(t);

    aux->nchaves= t-1 ;

    aux->folha = filho->folha;

    int j;

    if(aux->folha){
        for(j=0;j<t;j++){
            (aux->chaves[j] = filho->chaves[j+t]);
//      strcpy(aux->adic[j] ,filho->adic[j+t-1]);
        }

    }
    filho->nchaves = t;

    for(j=pai->nchaves; j>=i; j--) pai->filho[j+1]=pai->filho[j];

    pai->filho[i] = aux;

    for(j=pai->nchaves; j>=i; j--)pai->chaves[j] =pai->chaves[j-1];

    pai->chaves[i-1] = aux->chaves[t-2];
    pai->nchaves++;

//  if((pai->filho[i]) && pai->filho[i]->folha){
//    pai->filho[i-1]->next_brother = pai->filho[i];
//  }

	return pai;
}


TDISCO* Divisao(TDISCO *x, int i, TDISCO* y, int t){
    if(y->folha){
        return Divisao_folha(x,i,y,t);
    }
    TDISCO *z=Cria(t);
    z->nchaves= t - 1;
    z->folha = y->folha;
    int j;
    for(j=0;j<t-1;j++) z->chaves[j] = y->chaves[j+t];
    if(!y->folha){
        for(j=0;j<t;j++){
            z->filho[j] = y->filho[j+t];
            y->filho[j+t] = NULL;
        }
    }
    y->nchaves = t-1;
    for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
    x->filho[i] = z;
    for(j=x->nchaves; j>=i; j--) x->chaves[j] = x->chaves[j-1];
    x->chaves[i-1] = y->chaves[t-1];
    x->nchaves++;
    return x;
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

void busca_infos(TDISCO* a, char* chave){
	TDISCO* achado = busca(a, chave);
	if(!achado) return;

	printf("%s %d %d\n", achado->album, achado->nfaixas, achado->minutos);
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


TDISCO* busca_obras(TDISCO* a, char* nome){ //retorna NULL se não achar nenhuma obra
	if(!a) return NULL;                     //retorna o primeiro nó que o artista aparece se achar

	TDISCO* aux = a;

	while(!aux->folha) aux = aux->filho[0];

	
	while(aux != NULL){
		int i = 0;

		while((i < aux->nchaves) && strcmp(nome, strtok(aux->chaves[i], "/")) > 0) i++;

		if((i < aux->nchaves) && strcmp(nome, strtok(aux->chaves[i], "/")) < 0) return NULL;
		
		if((i < aux->nchaves) && strcmp(nome, strtok(aux->chaves[i], "/")) == 0) return aux;

		if(i >= aux->nchaves) aux = aux->proxirmao;
	}

	return aux;

}

TDISCO* retira(TDISCO* arv, char* ch, int t){
	if(!arv || !busca(arv, ch)) return arv;
	return remover(arv, ch, t);
}




int main(){
	char *str1, *str2;


	str1 = "renata";
	str2 = "renata ";
	printf("%d\n", strcmp(str1,str2));	

	return 0;

}