#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "geradordemapas.h"

/*Trabalho da disciplina de Fundamentos de Programação 1 desenvolvido pelos alunos: João Victor Laskoski e Luis Camilo Jussiani Moreira.*/

                                                            // a e b serão bases e alturas das figuras que serão determinadas posteriormente  dependendo de sua direção e sentido
//--------------FUNÇÕES RELATIVAS AO MAPA-------------------------------------------------------------------------------------------//
char** criaMapa(int T){
    char **mapa = (char**) malloc(sizeof(char*) * T);
    int i;
    for(i = 0; i < T; i++){
        mapa[i] = (char*) malloc(sizeof(char) * T);
    }
    return mapa;
}
void inicializaMapa(char** mapaMatriz, int tam){
	int i, j;
    	for(i =0; i < tam; i++){
        	for(j =0; j < tam; j++){
            	mapaMatriz[i][j] = '*';
        	}
    	}
	}
void visualizaMapa(char **mapa, int tam){
	int i, j;
	printf("  "); //Fator de correção (para alinhar a linha das letras com a matriz mapa)
    for(i = 0; i < tam; i++){
        printf(" %c", 'A'+i); //imprime a linhas das letras
    }

    printf("\n");

	for(i = 0; i < tam; i++){
        printf("%2d ", i); //imprime a coluna de números
    	for(j = 0; j < tam; j++){
        	printf("%c ", mapa[i][j]);
    	}
    	printf("\n");
	}
}
void destroiMapa(char **mapa, int tam){
    int i;
    for(i = 0; i < tam; i++){
        free(mapa[i]);
    }
    free(mapa);
}
//--------- FUNÇÕES RELATIVA AOS OBJETOS-------------------------------------------------------------------------------------//
void adicionaNoMapa(Objeto *objeto, char **mapa){
    int i, j;

    if(!objeto->meio){  //objetos sem meio: boia, submarino e porta-avioes
        for(i = 0; (i < objeto->b); i++){
            for(j = 0; (j < objeto->a)&&(objeto->dir)&&(objeto->sentido); j++){
                mapa[objeto->posx - j][objeto->posy + i] = objeto->identificador;
            }
            for(j = 0; (j < objeto->a)&&(objeto->dir)&&(!objeto->sentido); j++){
                mapa[objeto->posx + j][objeto->posy + i] = objeto->identificador;
            }
            for(j = 0; (j < objeto->a)&&(!objeto->dir)&&(objeto->sentido); j++){
                mapa[objeto->posx + i][objeto->posy + j] = objeto->identificador;
            }
            for(j = 0; (j < objeto->a)&&(!objeto->dir)&&(!objeto->sentido); j++){;
                mapa[objeto->posx + i][objeto->posy - j] = objeto->identificador;
            }
        }
    }
    else{ //aviao e espiao que tem meio
        if((objeto->dir)&&(objeto->sentido)){
            for(i = 0; i < objeto->b; i++){
                mapa[objeto->posx][objeto->posy + i] = objeto->identificador;
            }
            for(i = 0; i < objeto->a; i++){
                mapa[objeto->posx - i][objeto->posy + objeto->meio] = objeto->identificador;
            }
        }
        else if((objeto->dir)&&(!objeto->sentido)){
            for(i = 0; i < objeto->b; i++){
                mapa[objeto->posx][objeto->posy + i] = objeto->identificador;
            }
            for(i = 0; i < objeto->a; i++){
                mapa[objeto->posx + i][objeto->posy + objeto->meio] = objeto->identificador;
            }
        }
        else if((!objeto->dir)&&(objeto->sentido)){
            for(i = 0; i < objeto->b; i++){
                mapa[objeto->posx + i][objeto->posy] = objeto->identificador;
            }
            for(i = 0; i < objeto->a; i++){
                mapa[objeto->posx + objeto->meio][objeto->posy + i] = objeto->identificador;
            }
        }
        else if((!objeto->dir)&&(!objeto->sentido)){
            for(i = 0; i < objeto->b; i++){
                mapa[objeto->posx + i][objeto->posy] = objeto->identificador;
            }
            for(i = 0; i < objeto->a; i++){
                mapa[objeto->posx + objeto->meio][objeto->posy - i] = objeto->identificador;
            }
        }
    }
}
int verificaTerreno(Objeto *objeto, char **mapa){
    int terrenovalido, j, i;

    if(!objeto->meio){ //objetos sem meio: boia, submarino e porta-avioes
        for(i = 0; (i < objeto->b); i++){
            for(j = 0; (j < objeto->a)&&(objeto->dir)&&(objeto->sentido)&&terrenovalido; j++){ //OBS: SEPARAMOS EM DOIS 'FOR' POR QUESITO DE DESEMPENHO!
                if(mapa[objeto->posx - j][objeto->posy + i] != '*'){ //(porque senão dentro de um único for ia ter que verificar em toda iteração se a direção é 1 ou 0.)
                    terrenovalido = 0;
                }
            }
            for(j = 0; (j < objeto->a)&&(objeto->dir)&&(!objeto->sentido)&&terrenovalido; j++){
                if(mapa[objeto->posx + j][objeto->posy + i] != '*'){
                    terrenovalido = 0;
                }
            }
            for(j = 0; (j < objeto->a)&&(!objeto->dir)&&(objeto->sentido)&&terrenovalido; j++){
                if(mapa[objeto->posx + i][objeto->posy + j] != '*'){
                    terrenovalido = 0;
                }
            }
            for(j = 0; (j < objeto->a)&&(!objeto->dir)&&(!objeto->sentido)&&terrenovalido; j++){
                if(mapa[objeto->posx + i][objeto->posy - j] != '*'){
                    terrenovalido = 0;
                }
            }
        }
    }
    else{  //aviao e espiao que tem meio
        if((objeto->dir)&&(objeto->sentido)){
            for(i = 0; i < objeto->b; i++){
                if(mapa[objeto->posx][objeto->posy + i] != '*'){
                    terrenovalido = 0;
                }
            }
            for(i = 0; i < objeto->a; i++){
                if(mapa[objeto->posx - i][objeto->posy + objeto->meio] != '*'){
                    terrenovalido = 0;
                }
            }
        }
        else if((objeto->dir)&&(!objeto->sentido)){
            for(i = 0; i < objeto->b; i++){
                if(mapa[objeto->posx][objeto->posy + i] != '*'){
                    terrenovalido = 0;
                }
            }
            for(i = 0; i < objeto->a; i++){
                if(mapa[objeto->posx + i][objeto->posy + objeto->meio] != '*'){
                    terrenovalido = 0;
                }
            }
        }
        else if((!objeto->dir)&&(objeto->sentido)){
            for(i = 0; i < objeto->b; i++){
                if(mapa[objeto->posx + i][objeto->posy] != '*'){
                    terrenovalido = 0;
                }
            }
            for(i = 0; i < objeto->a; i++){
                if(mapa[objeto->posx + objeto->meio][objeto->posy + i] != '*'){
                    terrenovalido = 0;
                }
            }
        }
        else if((!objeto->dir)&&(!objeto->sentido)){
            for(i = 0; i < objeto->b; i++){
                if(mapa[objeto->posx + i][objeto->posy] != '*'){
                    terrenovalido = 0;
                }
            }
            for(i = 0; i < objeto->a; i++){
                if(mapa[objeto->posx + objeto->meio][objeto->posy - i] != '*'){
                    terrenovalido = 0;
                }
            }
        }
    }
    return terrenovalido;
}
void inicializaObjeto(Objeto *objeto, int ident_objeto, int T){
    if(!ident_objeto){objeto->a = 1; objeto->b = 1; objeto->dir = rand()%2; objeto->sentido = rand()%2; objeto->identificador = '0'; objeto->meio = 0;}
    if(ident_objeto == 1){objeto->a = 2; objeto->b = 3; objeto->dir = rand()%2; objeto->sentido = rand()%2; objeto->identificador = '1'; objeto->meio = 1;}
    if(ident_objeto == 2){objeto->a = 4; objeto->b = 1; objeto->dir = rand()%2; objeto->sentido = rand()%2; objeto->identificador = '2'; objeto->meio = 0;}
    if(ident_objeto == 3){objeto->a = 4; objeto->b = 3; objeto->dir = rand()%2; objeto->sentido = rand()%2; objeto->identificador = '3'; objeto->meio = 1;}
    if(ident_objeto == 4){objeto->a = 5; objeto->b = 2; objeto->dir = rand()%2; objeto->sentido = rand()%2; objeto->identificador = '5'; objeto->meio = 0;}

    /* nessa parte do codigo, já é determinado o sentido e a direção, logo irá ser calculado somente uma posição detre as possiveis posições para cada caso que dependem da direção e do sentido. */
    /* Algorítimo para limitar qual será a posição inicial da figura, de acordo com sua base e altura, em relação ao seu sentido e direção*/

    	if(objeto->dir){  //objeto-> dir = 1( vertical ) objeto-> dir = 0 (horizontal)
        	if(objeto->sentido){ //objeto->sentido = 1( para cima ou para direita )objeto->sentido = 0 ( para esquerda ou para baixo ) (varia de acordo com a direção )
            	objeto->posx = rand()%(T-objeto->a) + objeto->a;
            	objeto->posy = rand()%(T-objeto->b + 1);
        	}
        	else{
            	objeto->posx = rand()%(T-objeto->a + 1);
            	objeto->posy = rand()%(T-objeto->b + 1);
        	}
    	}
    	else{
        	if(objeto->sentido){
            	objeto->posx = rand()%(T-objeto->b + 1);
            	objeto->posy = rand()%(T-objeto->a + 1);
        	}
        	else{
            	objeto->posx = rand()%(T-objeto->b + 1);
            	objeto->posy = rand()%(T-objeto->a) + objeto->a;
        	}
    	}
}
void inicializaObjetos(int tamObjetos, Objeto *objetos, int identificador, int T, char **mapa){
    int i;
    for(i = 0; i < tamObjetos; i++){
        inicializaObjeto(&objetos[i], identificador, T);
    	if(!verificaTerreno(&objetos[i], mapa)){
            i--;
    	}
    	else
            adicionaNoMapa(&objetos[i], mapa);
	}
}

FILE *openFile(char* nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w+");
    if(arquivo!= NULL)
    {
        printf("Arquivo aberto com exito \n");
        return(arquivo);
    }
    else
    {
        printf("Não foi possivel executar o arquivo \n");
        return NULL;
    }
}

FILE *escreveArquivo(FILE* nome_arquivo, Objeto* objetos, int identificador, int tamObjetos)
{
    int i, orientacao; //Como no trabalho 1, adotamos 1 e 0 para dir e sentido, iremos modelar para convencao com if's
    //printar boias-------------------------
    for(i=0;i<tamObjetos;i++)
    {
        if(objetos[i].dir == 1 && objetos[i].sentido == 1 )
            orientacao = 1; //NORTE
        else if(objetos[i].dir == 1 && objetos[i].sentido == 0 )
            orientacao = 2; //SUL
        else if(objetos[i].dir == 0 && objetos[i].sentido == 1 )
            orientacao = 4; //LESTE
        else if(objetos[i].dir == 0 && objetos[i].sentido == 0 )
            orientacao = 3; //OESTE

        fprintf(nome_arquivo, "%d %d %d %d %d \n", i, identificador, orientacao, objetos[i].posx, objetos[i].posy );
    }
    return (nome_arquivo);
}
