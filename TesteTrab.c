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
}TABM;

int main(){
	char *um,*dois;


	um = "renata/2016";
	dois = "renata/2017";
	printf("%d",strcmp(um,dois));	

}