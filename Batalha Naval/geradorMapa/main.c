#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "geradordemapas.h"
#define NBOIA 10
#define NAVIAO 5
#define NSUB 5
#define NESPIAO 8
#define NPORTA 2

int main(){
    int T;
	char** mapaJogador, **mapaIA;
	Objeto boias[NBOIA], submarinos[NSUB], porta[NPORTA], aviao[NAVIAO], espiao[NESPIAO];

	FILE *arquivo = openFile("arquivo.txt"); //fechar arquivo com fclose

	srand(time(NULL));
    printf("DIGITE O TAMANHO DOS MAPAS(Tamanho para o trabalho = 20):\n");
    scanf("%d", &T);
	mapaJogador = criaMapa(T);
	mapaIA = criaMapa(T);
	inicializaMapa(mapaJogador, T);
	inicializaMapa(mapaIA, T);

	//GERANDO A POSIÇÃO NO MAPA DE CADA OBJETO
	//Boias---------------------------------------------------------------------------------------------------------------------//
	inicializaObjetos(NBOIA, boias, 0, T, mapaJogador);
	//Submarinos----------------------------------------------------------------------------------------------------------------//
	inicializaObjetos(NSUB, submarinos, 2, T, mapaJogador);
	//Porta-Aviões--------------------------------------------------------------------------------------------------------------//
 	inicializaObjetos(NPORTA, porta, 4, T, mapaJogador);
	//aviao---------------------------------------------------------------------------------------------------------------------//
	inicializaObjetos(NAVIAO, aviao, 1, T, mapaJogador);
	//espião--------------------------------------------------------------------------------------------------------------------//
	inicializaObjetos(NESPIAO, espiao, 3, T, mapaJogador);

	//GERANDO OS ARQUIUVOS DO MAPA PARA O JOGADOR
    arquivo = escreveArquivo(arquivo, boias,0, NBOIA);
    arquivo = escreveArquivo(arquivo, submarinos,2, NSUB);
    arquivo = escreveArquivo(arquivo, porta,5, NPORTA);
    arquivo = escreveArquivo(arquivo, aviao,1, NAVIAO) ;
    arquivo = escreveArquivo(arquivo, espiao,3, NESPIAO);


    //GERANDO A POSIÇÃO NO MAPA DE CADA OBJETO
	//Boias---------------------------------------------------------------------------------------------------------------------//
	inicializaObjetos(NBOIA, boias, 0, T, mapaIA);
	//Submarinos----------------------------------------------------------------------------------------------------------------//
	inicializaObjetos(NSUB, submarinos, 2, T, mapaIA);
	//Porta-Aviões--------------------------------------------------------------------------------------------------------------//
 	inicializaObjetos(NPORTA, porta, 5, T, mapaIA);
	//aviao---------------------------------------------------------------------------------------------------------------------//
	inicializaObjetos(NAVIAO, aviao, 1, T, mapaIA);
	//espião--------------------------------------------------------------------------------------------------------------------//
	inicializaObjetos(NESPIAO, espiao, 3, T, mapaIA);

	printf("\n");
	printf("MAPA JOGADOR:\n");
	visualizaMapa(mapaJogador, T);
	printf("\nMAPA INTELIGENCIA ARTIFICIAL:\n");
	visualizaMapa(mapaIA, T);
	destroiMapa(mapaJogador, T);
	destroiMapa(mapaIA, T);
	return 0;
}


