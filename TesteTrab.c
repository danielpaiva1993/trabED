#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 3      // 1 < nc < 5

typedef struct arvm{
	int nchaves, folha;
	char **chaves;
	//===================
	char *nomedisco;
	int nfaixas;
	int minutos;
	//===================
	struct arvm **filho, *antirmao, *proxirmao;
}TDISCO;


TDISCO *busca(TDISCO* a, char *chave){
	if(!a) return a;

	int i = 0;

	while((i < a->nchaves) && (a->chaves[i] < a)) i++;

	if((i < a->nchaves) && (a->folha) && (chave == a->chaves[i])) return a;

	return busca(a->filho[i], chave);
}





int main(){
	char *um,*dois;


	um = "renata/2016";
	dois = "renata/2017";
	printf("%d",strcmp(um,dois));	

}