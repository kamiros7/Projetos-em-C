#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define FPS 60


ALLEGRO_DISPLAY *janela = NULL; /* janela */
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL; /* fila de eventos do allegro */
ALLEGRO_TIMER *timer =NULL; /* timer para FPS */

/*======================================================================================================================================*/

bool inicializar(int LARGURA_TELA, int ALTURA_TELA)
{

    al_init(); /*inicialização do allegro */
    al_init_primitives_addon(); /* inicializa a manipulação de imagens */
    al_install_keyboard(); /* inicialiaza do teclado */
    timer = al_create_timer(1.0 / FPS); /* inicializa o timer */


    janela = al_create_display(LARGURA_TELA, ALTURA_TELA); /* define o tamanho da janela */

    fila_eventos = al_create_event_queue(); /* criação da fila de eventos */

    al_register_event_source(fila_eventos, al_get_display_event_source(janela)); /* registra a janela */
    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); /* registra a fila de eventos */
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer)); /*registra o timer */

    al_flip_display(); /* função que faz aparecer o conteudo na janela */
    al_start_timer(timer); /* inicia o timer */
    return 1;
}


/*=======================================================================================================================================*/



int main()
{
    float colisao_x;
    float colisao_y;
    float colisao; // norma para fazer o produto vetorial

    float projx1, projx2;
    float projy1, projy2;

    float* x;
    float* y;
    int* dir_x; // velocidade em x
    int* dir_y; // velocidade em y

    int i, j, n_bolas;
    bool sair = 0;

    printf("digite o numero de bolas : \n");
    scanf(" %d", &n_bolas);

    int LARGURA_TELA, ALTURA_TELA;
    printf("digite a largura e altura do display respectivamente : ");
    scanf("%d %d",&LARGURA_TELA, &ALTURA_TELA);

    if (!inicializar(LARGURA_TELA, ALTURA_TELA))
        return -1;

    srand(time(NULL)); /* gerador de numeros aleatórios */

    /* alocação dos vetores */
    x =  (float*) malloc(sizeof(float) * n_bolas);
    y =  (float*) malloc(sizeof(float) * n_bolas);
    dir_x =  (int*) malloc(sizeof(int) * n_bolas);
    dir_y =  (int*) malloc(sizeof(int) * n_bolas);

    /* dados dos circulos */
    float raio = 50.0;

    for ( i=0; i< n_bolas; i++)
    {
       x[i] = rand() % LARGURA_TELA- (raio*2);
       y[i] = rand () % ALTURA_TELA - (raio*2);
       dir_x[i] = rand() % 3, dir_y[i] = rand() % 3;
    }

    while (!sair)
    {
        if (!al_is_event_queue_empty(fila_eventos)){
           ALLEGRO_EVENT evento;

           /*espera ate que algum evento esteja na fila */
           al_wait_for_event(fila_eventos, &evento);

           switch(evento.keyboard.keycode) /* fechar o programa com a letra Q */
             {
              case ALLEGRO_KEY_Q :
              sair = 1;
             }

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) /* fechar o programa pelo X */
                sair = 1;
         }

   al_clear_to_color(al_map_rgb(255,255,255)); /*limpando a tela deixando o fundo branco */

    for (i =0; i < n_bolas; i++)
     {
        /* renderização dos círculos */

        al_draw_filled_circle(x[i], y[i], raio, al_map_rgb(255, 0, 0)); /*cor vermelha para cada bola */

        /*atualuização das velocidades */
        x[i] += 1 * dir_x[i];
        y[i] += 1 * dir_y[i];

     }
       al_flip_display();

        /* Essa colisão se refere das bolas contra a parede, como a massa
        da parede é "infinito", sua velocidade  apenas se inverte devido a
        colisao ser totalmente elastica, sendo inversão de VX caso ocorra
        lateralmente e de VY caso ocorra verticalmente */

        for(i=0; i < n_bolas; i++)
        {
          if (x[i] >= LARGURA_TELA - raio)
           {
            dir_x[i] = -1;
            x[i] = LARGURA_TELA - raio;
        } else if (x[i] <= raio) {
            dir_x[i] = 1;
            x[i] = raio;
         }


          if (y[i] >= ALTURA_TELA - raio)
           {
             dir_y[i] = -1;
             y[i] = ALTURA_TELA - raio;
        } else if (y[i] <= raio) {
            dir_y[i] = 1;
            y[i] = raio;
           }

        }



        for(i=0; i < n_bolas; i++)
            for(j = i+1; j < n_bolas; j++)
             {
                /* funções para ver se ocorreu colisão entre cada uma das bolas as bolas */
                /* haverá colis~es se a disntacia entre os centros das bolas for menos que a soma dos raios */
                /* HOUVE MANIPULAÇAO MATEMATICA PARA NÃO USAR RAIZ JÁ QUE DEMANDA MAIS DO COMPUTADOR */

                float dist_centros = 0;
                dist_centros = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
                   if(dist_centros <= raio*raio*4) /* houve colisão */
                      {
                       /* implementa a fisica */
                       /* para descobrir a velocidade após a colisão, precisa projetar a velocidade no eixo de colisão
                       primeiramente, dessa forma precisa aplicar o produto vetorial */

                       colisao_x = x[i] - x[j];
                       colisao_y = y[i] - y[j];
                       colisao = colisao_x * colisao_x + colisao_y * colisao_y; // norma

                       /*projeção das velocidades */
                        projx1 =  ((dir_x[i] * colisao_x ) + ( dir_y[i] * colisao_y)) * colisao_x / colisao;
                        projx2 =  ((dir_x[j] * colisao_x ) + ( dir_y[j] * colisao_y)) * colisao_x  / colisao;
                        projy1 = ((dir_x[i] * colisao_x) + (dir_y[i] * colisao_y))*colisao_y / colisao;
                        projy2 = ((dir_x[j] * colisao_x)+ (dir_y[j] * colisao_y)) * colisao_y / colisao;

                       /* inversão das velocidades no eixo */
                       dir_x[i] -= ( projx1 - projx2);
                       dir_x[j] -= (projx2 - projx1);
                       dir_y[i] -= (projy1 - projy2);
                       dir_y[j] -= (projy2 - projy1);

                       /* conserto do bug para que elas não fiquem coladas e perder o movimento,
                       dessa forma, deslocando um pixel cada bola */


                       if(colisao_x!=0 && colisao_y !=0 )
                        {
                         dir_x[i] += colisao_x/ abs(colisao_x);
                         dir_y[i] += colisao_y / abs(colisao_y);

                         dir_x[j] -= colisao_x / abs(colisao_x);
                         dir_y[j] -= colisao_y / abs(colisao_y);
                        }
                     }

          }

        al_rest( 0.002); /* paralização do programa */
    }
    /* desalocando os vetores */
    free(x);
    free(y);
    free(dir_x);
    free(dir_y);

    al_destroy_timer(timer); /* finaliza o timer */
    al_destroy_event_queue(fila_eventos); /* finaliza a fila de eventos */
    al_destroy_display(janela); /* finaliza a janela */

    return 0;
}
