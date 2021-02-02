#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>

int identificaObjeto(Objeto*** objeto, char **mapa, int y, int x, int identificadorVetor, int tamanho){//REUTILIZAÇÃO DO ESQUELETO DA VERIFICA TERRENO JÁ QUE SÓ EXISTE UM OBJETO CUJA VERIFICATERRENO IRÁ PASSAR PELA POSIÇÃO ACERTADA.
    int terrenovalido = 1, j, i, k;
    // tamanho = quantidade de objetos)

    for(k = 0; k < tamanho; k++){
        if(!objeto[identificadorVetor][k]->meio){ //objetos sem meio: boia, submarino e porta-avioes

        for(i = 0; (i < objeto[identificadorVetor][k]->b); i++){
            for(j = 0; (j < objeto[identificadorVetor][k]->a)&&(objeto[identificadorVetor][k]->orientacao == 1)&&terrenovalido; j++){ //OBS: SEPARAMOS EM DOIS 'FOR' POR QUESITO DE DESEMPENHO!
                if((objeto[identificadorVetor][k]->posx - j == y)&&(objeto[identificadorVetor][k]->posy + i == x)){ //(porque senão dentro de um único for ia ter que verificar em toda iteração se a direção é 1 ou 0.)
                    return k;
                }
            }
            for(j = 0; (j < objeto[identificadorVetor][k]->a)&&(objeto[identificadorVetor][k]->orientacao == 2)&&terrenovalido; j++){
                if((objeto[identificadorVetor][k]->posx + j == y)&&(objeto[identificadorVetor][k]->posy + i == x)){
                    return k;
                }
            }
            for(j = 0; (j < objeto[identificadorVetor][k]->a)&&(objeto[identificadorVetor][k]->orientacao == 4)&&terrenovalido; j++){
                if((objeto[identificadorVetor][k]->posx + i == y)&&(objeto[identificadorVetor][k]->posy + j == x)){
                    return k;
                }
            }
            for(j = 0; (j < objeto[identificadorVetor][k]->a)&&(objeto[identificadorVetor][k]->orientacao == 3)&&terrenovalido; j++){
                if((objeto[identificadorVetor][k]->posx + i == y)&&(objeto[identificadorVetor][k]->posy - j == x)){
                    return k;
                }
            }
        }
        }
    else{  //aviao e espiao que tem meio
        if((objeto[identificadorVetor][k]->orientacao == 1)){
            for(i = 0; i < objeto[identificadorVetor][k]->b; i++){
                if((objeto[identificadorVetor][k]->posx == y)&&(objeto[identificadorVetor][k]->posy + i == x)){
                    return k;
                }
            }
            for(i = 0; i < objeto[identificadorVetor][k]->a; i++){
                if((objeto[identificadorVetor][k]->posx - i == y)&&(objeto[identificadorVetor][k]->posy + objeto[identificadorVetor][k]->meio == x)){
                    return k;
                }
            }
        }
        else if((objeto[identificadorVetor][k]->orientacao == 2)){
            for(i = 0; i < objeto[identificadorVetor][k]->b; i++){
                if((objeto[identificadorVetor][k]->posx == y)&&(objeto[identificadorVetor][k]->posy + i == x)){
                    return k;
                }
            }
            for(i = 0; i < objeto[identificadorVetor][k]->a; i++){
                if((objeto[identificadorVetor][k]->posx + i == y)&&(objeto[identificadorVetor][k]->posy + objeto[identificadorVetor][k]->meio == x)){
                    return k;
                }
            }
        }
        else if((objeto[identificadorVetor][k]->orientacao == 4)){
            for(i = 0; i < objeto[identificadorVetor][k]->b; i++){
                if((objeto[identificadorVetor][k]->posx + i == y)&&(objeto[identificadorVetor][k]->posy == x)){
                    return k;
                }
            }
            for(i = 0; i < objeto[identificadorVetor][k]->a; i++){
                if((objeto[identificadorVetor][k]->posx + objeto[identificadorVetor][k]->meio == y)&&(objeto[identificadorVetor][k]->posy + i == x)){
                    return k;
                }
            }
        }
        else if((objeto[identificadorVetor][k]->orientacao == 3)){
            for(i = 0; i < objeto[identificadorVetor][k]->b; i++){
                if((objeto[identificadorVetor][k]->posx + i == y)&&(objeto[identificadorVetor][k]->posy == x)){
                    return k;
                }
            }
            for(i = 0; i < objeto[identificadorVetor][k]->a; i++){
                if((objeto[identificadorVetor][k]->posx + objeto[identificadorVetor][k]->meio == y)&&(objeto[identificadorVetor][k]->posy - i == x)){
                    return k;
                }
            }
        }
    }
    }
    return NULL;
}


void inicializaTabuleiro(Tabuleiro* tabuleiro){
    int i, j;
    for(i = 0; i < tabuleiro->linhas; i++){
        for(j = 0; j < tabuleiro->colunas; j++){
            tabuleiro->matriz_campo[i][j].valor = '*';
        }
    }
}
void visualizaTabuleiro(Tabuleiro *tabuleiro){
	int i, j;
	printf("  "); //Fator de correção (para alinhar a linha das letras com a matriz mapa)
    for(i = 0; i < tabuleiro->colunas; i++){
        printf(" %c", 'A'+i); //imprime a linhas das letras
    }

    printf("\n");

	for(i = 0; i < tabuleiro->linhas; i++){
        printf("%2d ", i); //imprime a coluna de números
    	for(j = 0; j < tabuleiro->colunas; j++){
            if(tabuleiro->matriz_campo[i][j].visivel)//se estiver visivel...
                printf("%c ", tabuleiro->matriz_campo[i][j].valor);
            else
                printf("%c ", '*');
    	}
    	printf("\n");
	}
}

void atirar(Game* jogo, int id_jogador, Turno* turno, Objeto*** objetosJogadorIA){//id_jogador_identifica qual é o jogador da vez(0: jogador, 1: IA).
    int x,y, partesFaltantes = 0, indiceVet; /* se objeto foi acertado, servirá como parametro para precisão da IA */
    if(!id_jogador){/* TURNO JOGADOR */      /* indiceVet recebe k da identificaObjeto */
        printf("Digite a Posicao do tiro:(x y)");
        scanf("%d %d", &x, &y);

        if(jogo->jogadorIA->tabuleiro->matriz_campo[y][x].visivel){//JOGADA INVALIDA
            system("cls"); //limpa tela
            printf("ATENCAO: Jogada Invalida! A posicao %dx%d ja foi atingida. Jogue novamente:\n", x, y);
            visualizaTabuleiro(jogo->jogadorIA->tabuleiro);
            atirar(jogo, 0, turno);//RECURSIVIDADE DUVIDOSA...(ARRUMAR AQUI TA ERRADO É SÓ UMA GAMBIARRA1)
        }
        jogo->jogadorIA->tabuleiro->matriz_campo[y][x].visivel = 1;
        if(jogo->jogadorIA->tabuleiro->matriz_campo[y][x].valor != '*'){//VERIFICA O TIRO
            jogo->jogadorIA->frota_total --;
            //PROGRAMAÇÃO RELACIONADA AO TIRO. DECREMENTO DA FROTA INIMIGA...ETC
        }
        else{//ACERTOU A ÁGUA
            jogo->jogadorIA->tabuleiro->matriz_campo[y][x].valor = '#';
        }
    }
    else /* TURNO IA */
    {
        if(!turno->objetoAcertado)
        {
            x = rand() % (jogo->jogador->tabuleiro->linhas);
            y = rand() % (jogo->jogador->tabuleiro->colunas);


              /* if(jogo->jogador->tabuleiro->matriz_campo[y][x].visivel){//JOGADA INVALIDA
                    system("cls"); //limpa tela
                    printf("ATENCAO: Jogada Invalida! A posicao %dx%d ja foi atingida. Jogue novamente:\n", x, y);
                    visualizaTabuleiro(jogo->jogador->tabuleiro);
                    atirar(jogo, 1, turno);//RECURSIVIDADE DUVIDOSA...(ARRUMAR AQUI TA ERRADO É SÓ UMA GAMBIARRA1)
                }*/

                //PROGRAMAÇÃO RELACIONADA AO TIRO. DECREMENTO DA FROTA INIMIGA...ETC
                jogo->jogador->tabuleiro->matriz_campo[y][x].visivel = 1;
                if(jogo->jogador->tabuleiro->matriz_campo[y][x].valor != '*'){//VERIFICA O TIRO
                    jogo->jogador->frota_total --;
                    if((jogo->jogador->tabuleiro->matriz_campo[y][x].valor != '0'))
                       turno->objetoAcertado = 1; //ATIVA A IA!!!!!!!!
                }
                else{//ACERTOU A ÁGUA
                    jogo->jogador->tabuleiro->matriz_campo[y][x].valor = '#';
                }
        }
        else /* procura as partes faltantes do objeto acertado */
        {

            //algoritimos diferente dependendo do jogo->jogador->tabuleiro->matriz_campo[y][x].valor
            /* Acho que essa parte ficará grande demais, muito if e else, para cada decisão de jogada, não acha  ? */
            /* mas a parte dos objetos faltantes, quando ele atingir o limite, da um break, porque ai quer dizer que achou o
            objeto como um todo */
        }

    }
}

void adicionaNoTabuleiro(Objeto *objeto, Tabuleiro* tabuleiro){//CONVERTER DIREITO PARA ASCII
    int i, j;

    if(!objeto->meio){  //objetos sem meio: boia, submarino e porta-avioes
        for(i = 0; (i < objeto->b); i++){
            for(j = 0; (j < objeto->a)&&objeto->orientacao == 1; j++){ //dir = 1, sen = 1
                tabuleiro->matriz_campo[objeto->posx - j][objeto->posy + i].valor = '0' + objeto->identificador;
            }
            for(j = 0; (j < objeto->a)&&objeto->orientacao == 2; j++){//dir = 1, sen = 0
                tabuleiro->matriz_campo[objeto->posx + j][objeto->posy + i].valor = '0' + objeto->identificador;
            }
            for(j = 0; (j < objeto->a)&&objeto->orientacao == 4; j++){//dir = 0, sen = 1
                tabuleiro->matriz_campo[objeto->posx + i][objeto->posy + j].valor = '0' + objeto->identificador;
            }
            for(j = 0; (j < objeto->a)&&objeto->orientacao == 3; j++){//dir = 0, sen = 0
                tabuleiro->matriz_campo[objeto->posx + i][objeto->posy - j].valor = '0' + objeto->identificador;
            }
        }
    }
    else{ //aviao e espiao que tem meio
        if(objeto->orientacao == 1){
            for(i = 0; i < objeto->b; i++){
                tabuleiro->matriz_campo[objeto->posx][objeto->posy + i].valor  = '0' + objeto->identificador;
            }
            for(i = 0; i < objeto->a; i++){
                tabuleiro->matriz_campo[objeto->posx - i][objeto->posy + objeto->meio].valor  = '0' + objeto->identificador;
            }
        }
        else if(objeto->orientacao == 2){
            for(i = 0; i < objeto->b; i++){
                tabuleiro->matriz_campo[objeto->posx][objeto->posy + i].valor  = '0' + objeto->identificador;
            }
            for(i = 0; i < objeto->a; i++){
                tabuleiro->matriz_campo[objeto->posx + i][objeto->posy + objeto->meio].valor  = '0' + objeto->identificador;
            }
        }
        else if(objeto->orientacao == 4){
            for(i = 0; i < objeto->b; i++){
                tabuleiro->matriz_campo[objeto->posx + i][objeto->posy].valor  = '0' + objeto->identificador;
            }
            for(i = 0; i < objeto->a; i++){
                tabuleiro->matriz_campo[objeto->posx + objeto->meio][objeto->posy + i].valor  = '0' + objeto->identificador;
            }
        }
        else if(objeto->orientacao == 3){
            for(i = 0; i < objeto->b; i++){
                tabuleiro->matriz_campo[objeto->posx + i][objeto->posy].valor = '0' + objeto->identificador;
            }
            for(i = 0; i < objeto->a; i++){
                tabuleiro->matriz_campo[objeto->posx + objeto->meio][objeto->posy - i].valor = '0' + objeto->identificador;
            }
        }
    }
}

void destroiTurno(Turno* turno)
{
    free(turno);
}

Turno* criarTurno()
{
    Turno* turno;
    turno = (Turno*)malloc(sizeof(Turno));
    turno->objetoAcertado =0;
    return turno;
}

Tabuleiro* criaTabuleiro(int linhas, int colunas){
    int i;
    Tabuleiro* tabuleiro = (Tabuleiro*) malloc(sizeof(Tabuleiro));
    tabuleiro->matriz_campo = (Celula**) malloc(sizeof(Celula*) * linhas);

    tabuleiro->linhas = linhas;
    tabuleiro->colunas = colunas;

    for(i = 0; i < linhas; i++){
        tabuleiro->matriz_campo[i] = (Celula*) malloc(sizeof(Celula) * colunas);
    }
    return tabuleiro;
}

Tabuleiro* inicializaJogador(Objeto*** objetos, int linhas, int colunas){
    int i;

    Tabuleiro *tabuleiro;
    tabuleiro = criaTabuleiro(linhas, colunas);
    inicializaTabuleiro(tabuleiro);

    for(i = 0; i < NBOIA; i++){
        adicionaNoTabuleiro(objetos[0][i], tabuleiro);
    }
    for(i = 0; i < NSUB; i++){
        adicionaNoTabuleiro(objetos[1][i], tabuleiro);
    }
    for(i = 0; i < NPORTA; i++){
        adicionaNoTabuleiro(objetos[2][i], tabuleiro);
    }
    for(i = 0; i < NAVIAO; i++){
        adicionaNoTabuleiro(objetos[3][i], tabuleiro);
    }
    for(i = 0; i < NESPIAO; i++){
        adicionaNoTabuleiro(objetos[4][i], tabuleiro);
    }
    return tabuleiro;

}

FILE* abreArquivo(char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "r");
    if(arquivo != NULL){
        return arquivo;
    }
    else{
        printf("Impossivel abrir o arquivo.\n");
        exit(1);
    }
}

Objeto*** leArquivo(char* nome_arquivo){
    Objeto*** objetos = (Objeto***) malloc(sizeof(Objeto*)*5); //Alocando linhas da matriz objetos
    int i, identificador, orientacao, posx, posy;

    FILE* arquivo = abreArquivo(nome_arquivo);

    objetos[0] = (Objeto**) malloc(sizeof(Objeto*)*NBOIA); /* alocando colunas da matriz objetos */
    objetos[1] = (Objeto**) malloc(sizeof(Objeto*)*NSUB);
    objetos[2] = (Objeto**) malloc(sizeof(Objeto*)*NPORTA);
    objetos[3] = (Objeto**) malloc(sizeof(Objeto*)*NAVIAO);
    objetos[4] = (Objeto**) malloc(sizeof(Objeto*)*NESPIAO);

    for(i=0;i<NBOIA;i++)
    {
        objetos[0][i] = (Objeto*)malloc(sizeof(Objeto));
    }
    for(i=0;i<NSUB;i++)
    {
        objetos[1][i] = (Objeto*)malloc(sizeof(Objeto));
    }
    for(i=0;i<NPORTA;i++)
    {
        objetos[2][i] = (Objeto*)malloc(sizeof(Objeto));
    }
    for(i=0;i<NAVIAO;i++)
    {
        objetos[3][i] = (Objeto*)malloc(sizeof(Objeto));
    }
    for(i=0;i<NESPIAO;i++)
    {
        objetos[4][i] = (Objeto*)malloc(sizeof(Objeto));
    }

    while(fscanf(arquivo, "%d %d %d %d %d", &i, &identificador, &orientacao, &posx, &posy) != EOF){ //recebendo os dados do arquivo
        if(!identificador){//BOIA
            objetos[0][i]->meio = 0;
            objetos[0][i]->a = 1;
            objetos[0][i]->b = 1;
            objetos[0][i]->identificador = identificador;
            objetos[0][i]->orientacao = orientacao;
            objetos[0][i]->posx = posx;
            objetos[0][i]->posy = posy;
        }
        else if(identificador == 2){//SUBMARINO
            objetos[1][i]->meio = 0;
            objetos[1][i]->a = 4;
            objetos[1][i]->b = 1;
            objetos[1][i]->identificador = identificador;
            objetos[1][i]->orientacao = orientacao;
            objetos[1][i]->posx = posx;
            objetos[1][i]->posy = posy;
        }
        else if(identificador == 5){//PORTA-AVIÕES
            objetos[2][i]->meio = 0;
            objetos[2][i]->a = 5;
            objetos[2][i]->b = 2;
            objetos[2][i]->identificador = identificador;
            objetos[2][i]->orientacao = orientacao;
            objetos[2][i]->posx = posx;
            objetos[2][i]->posy = posy;
        }
        else if(identificador == 1){//AVIAO
            objetos[3][i]->meio = 1;
            objetos[3][i]->a = 2;
            objetos[3][i]->b = 3;
            objetos[3][i]->identificador = identificador;
            objetos[3][i]->orientacao = orientacao;
            objetos[3][i]->posx = posx;
            objetos[3][i]->posy = posy;
        }
        else if(identificador == 3){//ESPIAO
            objetos[4][i]->meio = 1;
            objetos[4][i]->a = 4;
            objetos[4][i]->b = 3;
            objetos[4][i]->identificador = identificador;
            objetos[4][i]->orientacao = orientacao;
            objetos[4][i]->posx = posx;
            objetos[4][i]->posy = posy;
        }
    }
    return (objetos);
}


//CORRIGIDO

Game* inicializaParametrosIniciais(Objeto*** objetosJogador, Objeto*** objetosJogadorIA, int linhas, int colunas){
     int i,j;
     //ALOCANDO MEMÓRIA NECESSÁRIA
     Game* jogo = (Game*) malloc(sizeof(Game));
     jogo->jogador = (Jogador*) malloc(sizeof(Jogador));
     jogo->jogadorIA = (Jogador*) malloc(sizeof(Jogador));
     //===========================

     jogo->fim_jogo = 0;
     jogo->jogador->frota_total = 118;
     jogo->jogadorIA->frota_total = 118;
     jogo->jogador->tabuleiro = inicializaJogador(objetosJogador, linhas, colunas); //Iniicaliza o mapa já com os dados
     jogo->jogadorIA->tabuleiro = inicializaJogador(objetosJogadorIA, linhas, colunas);

     //INICIALIZANDO A VISIBILIDADE:
     for(i = 0; i < jogo->jogador->tabuleiro->linhas; i++){
        for(j = 0;j < jogo->jogador->tabuleiro->colunas; j++){
            jogo->jogador->tabuleiro->matriz_campo[i][j].visivel = 0;
            jogo->jogadorIA->tabuleiro->matriz_campo[i][j].visivel = 0;
        }
     }

     return jogo;
}
