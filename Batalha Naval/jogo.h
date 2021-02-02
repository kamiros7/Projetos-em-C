#include <stdio.h>
#include <stdlib.h>
#define NBOIA 10
#define NAVIAO 5
#define NSUB 5
#define NESPIAO 8
#define NPORTA 2

typedef struct{
    int identificador, orientacao, posx, posy, a, b, meio;
}Objeto;

typedef struct
{
    int visivel;
    char valor;
}Celula;

typedef struct
{
    int linhas;
    int colunas;
    Celula **matriz_campo;
}Tabuleiro;

typedef struct
{
    int id;
    int vencedor;
    int frota_total;
    Tabuleiro* tabuleiro;
}Jogador;

typedef struct
{
    int x;
    int y;
    int orientacao;
    int contador;
    int objetoAcertado;
}Turno;

typedef struct
{
    Jogador* jogador;
    Jogador* jogadorIA;
    Turno* turno;
    int fim_jogo;
}Game;

int identificaObjeto(Objeto*** objeto, char **mapa, int y, int x, int identificadorVetor, int tamanho); /* como saberemos o tamanho antes de sabermos que peça será ? */
void inicializaTabuleiro(Tabuleiro* tabuleiro);
void visualizaTabuleiro(Tabuleiro *tabuleiro);
void atirar(Game* jogo, int id_jogador, Turno* turno, Objeto*** objetosJogadorIA);
void adicionaNoTabuleiro(Objeto *objeto, Tabuleiro* tabuleiro);
void destroiTurno(Turno* turno);
Turno* criarTurno();
Tabuleiro* criaTabuleiro(int linhas, int colunas);
Tabuleiro* inicializaJogador(Objeto*** objetos, int linhas, int colunas);
FILE* abreArquivo(char* nome_arquivo);
Objeto*** leArquivo(char* nome_arquivo); /* criaObjeto */
Game* inicializaParametrosIniciais(Objeto*** objetosJogador, Objeto*** objetosJogadorIA, int linhas, int colunas);
