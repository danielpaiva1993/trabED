#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 3      // 1 < nc < 5

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


TDISCO* busca(TDISCO* a, char *chave){
	if(!a) return a;

	int i = 0;

	while((i < a->nchaves) && (a->chaves[i] < a)) i++;

	if((i < a->nchaves) && (a->folha) && (chave == a->chaves[i])) return a;

	return busca(a->filho[i], chave);
}

char *busca_album(TDISCO* a, char *chave){
	TDISCO* achado = busca(a, chave);
	if(!achado) return achado;

	return achado->album;
}

int busca_faixas(TDISCO* a, char *chave){
	TDISCO* achado = busca(a, chave);
	if(!achado) return achado;

	return achado->nfaixas;
}

int busca_minutos(TDISCO* a, char *chave){
	TDISCO* achado = busca(a, chave);
	if(!achado) return achado;

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
	char *um,*dois;


	um = "renata/2016";
	dois = "renata/2017";
	printf("%d",strcmp(um,dois));	

}