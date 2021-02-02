#include <stdio.h>
#include <stdlib.h>

//------- STRUCTS--------------------------------------------------------------------------------------------------------------//
typedef struct{
	int posx, posy, dir, sentido, identificador, a, b, meio;  //objetos com meio: aviao e espiao -> essa variavel serve para auxiliar nas funcoes verificaMapa e AdicionaNoMapa.
}Objeto;

                                                            // a e b serão bases e alturas das figuras que serão determinadas posteriormente  dependendo de sua direção e sentido
//--------------FUNÇÕES RELATIVAS AO MAPA-------------------------------------------------------------------------------------------//
char** criaMapa(int T);
void inicializaMapa(char** mapaMatriz, int tam);
void visualizaMapa(char **mapa, int tam);
void destroiMapa(char **mapa, int tam);
//--------- FUNÇÕES RELATIVAS AOS OBJETOS-------------------------------------------------------------------------------------//
void adicionaNoMapa(Objeto *objeto, char **mapa);
int verificaTerreno(Objeto *objeto, char **mapa);
void inicializaObjeto(Objeto *objeto, int ident_objeto, int T);
void inicializaObjetos(int tamObjetos, Objeto *objetos, int identificador, int T, char **mapa);
//--------------FUNÇÕES RELATIVA AO ARQUIVO-----------------------------------------------------------------------------------//
FILE *openFile(char* nome_arquivo);
FILE *escreveArquivo(FILE* nome_arquivo, Objeto* objetos, int identificador, int tamObjetos);

