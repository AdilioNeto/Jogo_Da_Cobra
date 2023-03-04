#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <windows.h>


int pontuacao = 0;
int pon;
int temp = 450;
int nivel = 2;
int horizontal = 0;
int vertical = 0;

int altura = 20;
int largura = 30;
char area[20][30];
long long tamanhodacobra = 1;
int tamanhodacobraaux = -1;
int acaba = 0;

long long cobra[20][30];
long long a = 0;
int direcao[];

int inicioj = 1;
int inicioi = 1;
char comando;
char parede = '.';

int macai = 1;
int macaj = 1;

void green () {
  printf("\033[0;32m");
}

void red () {
  printf("\033[1;31m");
}

void reset () {
  printf("\033[0m");
}

void geramaca(){

    area[macai][macaj] = ' ';
    macai = rand() % altura;
    macaj = rand() % largura;

    if(macai == 0){
        macai++;
    }else if(macai == altura - 1){
        macai--;
    }

    if(macaj == 0){
        macaj++;
    }else if(macaj == largura - 1){
        macaj--;
    }

    if(cobra[macai][macaj] != 0){
        geramaca();
    }

    area[macai][macaj] = 'o';

}


void criaarea(){
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            if( i == 0 || j == 0 || (j == largura - 1) || i == (altura - 1)){
                area[i][j] = parede;
            }else{
                area[i][j] = ' ';
            }

        }
    }
}


void imprimearea(){
    system("cls");
    printf("pontuacao: %d\n%d\n", pontuacao, tamanhodacobra);
    if(nivel == 1){
        printf("nivel: facil\n");
    }else if(nivel == 2){
        printf("nivel: normal\n");
    }else if(nivel == 3){
        printf("nivel: dificil\n");
    }
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            if(cobra[i][j] == 1 && direcao[a] == 1){
                green();
                printf("^");
            }else if(cobra[i][j] == 1 && direcao[a] == 2){
                green();
                printf("v");
            }else if(cobra[i][j] == 1 && direcao[a] == 3){
                green();
                printf(">");
            }else if(cobra[i][j] == 1 && direcao[a] == 4){
                green();
                printf("<");
            }else if(cobra[i][j] != 1 && cobra[i][j] != 0){
                green();
                printf("*");
            }else if(area[i][j] == 'o'){
                red();
                printf("%c", area[i][j]);
            }else{
                reset();
                printf("%c", area[i][j]);
            }


        }
        printf("\n");
    }
}

void *vearea(){

    while(!acaba){
        system("cls");
        imprimearea();
    }

    system("cls");

    sabermelhor();

    if(pontuacao > pon){
        melhor();
    }
}



void seguir(){

    tamanhodacobra++;

    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
                if(direcao[a] == 1){
                    cobra[inicioi + 1][inicioj] = tamanhodacobra;
                }else if(direcao[a] == 2){
                    cobra[inicioi - 1][inicioj] = tamanhodacobra;
                }else if(direcao[a] == 3){
                    cobra[inicioi][inicioj - 1] = tamanhodacobra;
                }else if(direcao[a] == 4){
                    cobra[inicioi][inicioj + 1] = tamanhodacobra;
                }
        }
    }

}

void comemaca(){
    if(inicioi == macai && inicioj == macaj){
        geramaca();
        pontuacao++;
        tamanhodacobraaux++;

    }

}

void limparastro(){
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            if(cobra[i][j] != 0 && cobra[i][j] != 1 && cobra[i][j] < tamanhodacobra - tamanhodacobraaux){
                cobra[i][j] = 0;
            }
        }
    }
}

void *movecorpo(){

    while(!acaba){
        movecorpoaux();
        comemaca();
        Sleep(temp);
    }

    system("cls");

    sabermelhor();

    if(pontuacao > pon){
        melhor();
    }

}

void movecorpoaux(){

    if(direcao[a] == 1){
        if(cobra[inicioi - 1][inicioj] == 0 && area[inicioi - 1][inicioj] != parede){
            cobra[inicioi][inicioj] = 0;
            inicioi--;
        }else{
            acaba++;
        }
    }else if(direcao[a] == 2){
        if(cobra[inicioi + 1][inicioj] == 0 && area[inicioi + 1][inicioj] != parede){
            cobra[inicioi][inicioj] = 0;
            inicioi++;
        }else{
            acaba++;
        }
    }else if(direcao[a] == 4){
        if(cobra[inicioi][inicioj - 1] == 0 && area[inicioi][inicioj - 1] != parede){
            cobra[inicioi][inicioj] = 0;
            inicioj--;
        }else{
            acaba++;
        }
    }else if(direcao[a] == 3){
        if(cobra[inicioi][inicioj + 1] == 0 && area[inicioi][inicioj + 1] != parede){
            cobra[inicioi][inicioj] = 0;
            inicioj++;
        }else{
            acaba++;
        }
    }else{
        acaba++;
    }

    cobra[inicioi][inicioj] = 1;
    seguir();
    limparastro();


}

void melhor(){
    FILE* f;

    f = fopen("melhorpontuacao.txt", "w");

    if(f == 0){
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    fprintf(f, "%d", pontuacao);

    fclose(f);

}

void sabermelhor(){

    FILE* f;

    f = fopen("melhorpontuacao.txt", "r");

    if(f == 0){
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    fscanf(f, "%d", &pon);

    fclose(f);

}


void movecabeca(){

    comando = getch();
    a++;

    if(comando == 'w' || comando == 'W'){
        comando = 'w';
    }else if(comando == 's' || comando == 'S'){
        comando = 's';
    }else if(comando == 'a' || comando == 'A'){
        comando = 'a';
    }else if(comando == 'd' || comando == 'D'){
        comando = 'd';
    }

    if(direcao[a - 1] != 2 && area[inicioi - 1][inicioj] != parede && comando == 'w'){
        if(cobra[inicioi - 1][inicioj] == 0 && direcao[a - 1] != 1){
            cobra[inicioi][inicioj] = 0;
            inicioi--;
            direcao[a] = 1;
            cobra[inicioi][inicioj] = 1;
            seguir();
            limparastro();
        }else{
            a--;
            if(comando == 'w' && direcao[a] != 1){
                acaba++;
            }
        }
    }else if(direcao[a - 1] != 1 && area[inicioi + 1][inicioj] != parede && comando == 's'){
        if(cobra[inicioi + 1][inicioj] == 0 && direcao[a - 1] != 2){
            cobra[inicioi][inicioj] = 0;
            inicioi++;
            direcao[a] = 2;
            cobra[inicioi][inicioj] = 1;
            seguir();
            limparastro();
        }else{
            a--;
            if(comando == 's' && direcao[a] != 2){
                acaba++;
            }
        }
    }else if(direcao[a - 1] != 3 && area[inicioi][inicioj - 1] != parede && comando == 'a'){
        if(cobra[inicioi][inicioj - 1] == 0 && direcao[a - 1] != 4){
            cobra[inicioi][inicioj] = 0;
            inicioj--;
            direcao[a] = 4;
            cobra[inicioi][inicioj] = 1;
            seguir();
            limparastro();
        }else{
            a--;
            if(comando == 'a' && direcao[a] != 4){
                acaba++;
            }
        }
    }else if(direcao[a - 1] != 4 && area[inicioi][inicioj + 1] != parede && comando == 'd'){
        if(cobra[inicioi][inicioj + 1] == 0 && direcao[a - 1] != 3){
            cobra[inicioi][inicioj] = 0;
            inicioj++;
            direcao[a] = 3;
            cobra[inicioi][inicioj] = 1;
            seguir();
            limparastro();
        }else{
            a--;
            if(comando == 'd' && direcao[a] != 3){
                acaba++;
            }
        }
    }else if(direcao[a-1] == 3 || direcao[a-1] == 4){
        horizontal = 1;
        if(horizontal == 1 && comando == 'w' && area[inicioi - 1][inicioj] == parede){
            acaba++;
        }else if(horizontal == 1 && comando == 's' && area[inicioi + 1][inicioj] == parede){
            acaba++;
        }
        a--;

    }else if(direcao[a-1] == 1 || direcao[a-1] == 2){
        vertical = 1;
        if(vertical == 1 && comando == 'd' && area[inicioi][inicioj + 1] == parede){
            acaba++;
        }else if(vertical == 1 && comando == 'a' && area[inicioi][inicioj - 1] == parede){
            acaba++;
        }
        a--;
    }else{
        a--;
    }

}

void zeracobra(){
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            cobra[i][j] = 0;
        }
    }
}

void iniciar(){

    pontuacao = 0;
    zeracobra();
    acaba = 0;
    inicioi = 1;
    inicioj = 1;
    tamanhodacobra = 1;
    tamanhodacobraaux = -1;

    criaarea();

    a = 0;

    direcao[a] = 3;

    cobra[inicioi][inicioj] = 1;

    geramaca();

}





int main(){

    srand(time(0));

    int opcao;
    int opcaoaux;

    do{
            system("cls");
            printf("1-Iniciar jogo.");
            printf("\n2-Definir nivel.");
            printf("\n3-Saber Melhor pontuacao.");
            printf("\n0-Sair.");
            printf("\nResposta: ");
            scanf("%d", &opcao);

            if(opcao == 1){

                do{
                        iniciar();

                        pthread_t thread_id;

                        pthread_create(&thread_id, NULL, movecorpo, 0);
                        pthread_create(&thread_id, NULL, vearea, 0);

                        do{
                            movecabeca();
                            comemaca();
                        }while(!acaba);

                        sabermelhor();

                        if(pontuacao > pon){
                            melhor();
                        }

                        system("cls");
                        system("pause");

                        system("cls");
                        printf("1-Jogar novamente.");
                        printf("\n2-Nao jogar novamnte.");
                        printf("\nResposta: ");
                        scanf("%d", &opcaoaux);

                }while(opcaoaux == 1);

            }else if(opcao == 2){
                system("cls");
                printf("1-Facil");
                printf("\n2-Normal");
                printf("\n3-Dificil");
                printf("\nResposta: ");
                scanf("%d", &nivel);

                if(nivel == 1){
                    temp = 400;
                }else if(nivel == 2){
                    temp = 300;
                }else if(nivel == 3){
                    temp = 200;
                }


            }else if(opcao == 3){
                sabermelhor();
                system("cls");
                printf("Melhor pontuacao: %d\n\n", pon);
                system("pause");
                system("cls");
                printf("\n1-Voltar ao menu prinicpal.");
                printf("\n0-Sair.");
                printf("\nResposta: ");
                scanf("%d", &opcao);
            }

    }while(opcao != 0);




    return 0;
}
