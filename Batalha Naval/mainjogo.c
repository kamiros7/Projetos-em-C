#include "jogo.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    //INICIALIZANDO PARÂMETROS(ABRINDO ARQUIVO E INICIALIZANDO PARAMETROS INTERNOS DOS JOGADORES)
    char* end_arquivo_jogador = "geradorMapa\\bin\\Debug\\arquivo.txt";
    char* end_arquivo_jogadorIA = "geradorMapa\\bin\\Debug\\arquivoia.txt";
    int linhas, colunas;
    Game* jogo;
    Turno* turno = criarTurno();

    abreArquivo(end_arquivo_jogador);
    abreArquivo(end_arquivo_jogadorIA);

    Objeto*** objetosJogador = leArquivo(end_arquivo_jogador);
    Objeto*** objetosJogadorIA = leArquivo(end_arquivo_jogadorIA);

    srand(time(NULL));

    printf("Batalha Naval - T2 Prog - Universidade Tecnologica Federal do Parana\n");
    printf("Linhas:\n");
    scanf("%d", &linhas);
    printf("Colunas:\n");
    scanf("%d", &colunas);
    jogo = inicializaParametrosIniciais(objetosJogador, objetosJogadorIA, linhas, colunas);

    //Loop do jogo.
    while(!jogo->fim_jogo){
        system("cls"); // limpa a tela.
        printf("Voce:\n");
        visualizaTabuleiro(jogo->jogador->tabuleiro);
        printf("\nInimigo:\n");
        visualizaTabuleiro(jogo->jogadorIA->tabuleiro);
        atirar(jogo, 0, turno, objetosJogadorIA); // turno do jogador


        //VERIFICA SE O JOGO ACABOU
        if(jogo->jogadorIA->frota_total == 0){
            jogo->fim_jogo = 1;
            jogo->jogador->vencedor = 1;
            jogo->jogadorIA->vencedor = 0;
            break;
        }
        atirar(jogo,1, turno, objetosJogadorIA); //turno da IA
        //VERIFICA SE O JOGO ACABOU
        if(jogo->jogador->frota_total == 0){
            jogo->fim_jogo = 1;
            jogo->jogadorIA->vencedor = 1;
            jogo->jogador->vencedor = 0;
            break;
        }
    }
    system("cls");
    printf("Fim de Jogo.\n");
    if(jogo->jogador->vencedor)
        printf("Parabens! voce Ganhou!\n");
    else
        printf("O Inimigo venceu!\n");

    printf("\nDesenvolvido por: Joao Victor Laskoski e Luis Camilo Jussiani Moreira\n");

    destroiTurno(turno);   /* PRECISAMOS DEASLOCAR TUDOOO */
    //fclose(end_arquivo_jogador);  /* varialvel tipo FILE apenas na função, como fechar o arquivo ? */
    //fclose(end_arquivo_jogadorIA);
    /* como leArquivo é um criaObjeto, precisamos de um destruirObjeto */
    return 0;
}

