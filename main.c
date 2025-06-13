#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <raylib.h>

#define MARGEM 10

#include "rlgl.h"

int tabuleiro[4][4];
int pontuacao = 0;
int vitoria = 0;

void limpaTabuleiro(int tabuleiro[4][4]){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}


void printTabuleiro(int tabuleiro[4][4]){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}
int move(int tabuleiro[4][4], char input){
    int moveu = 0;
    int pontuacaoRodada = 0;
    switch (input) {
        case 'a': // Movimento para a esquerda
            for (int i = 0; i < 4; i++) {
                int juntou[4] = {0}; //criei esse array para saber quando os números ja foram somados e não somalos novamente no mesmo input.
                for (int j = 1; j < 4; j++) {
                    if (tabuleiro[i][j]) { //se a célula não for vazia
                        int k = j;

                        while (k > 0) {
                            //se célula adjacente estiver vazia, mover na direcao
                            //k é uma variavel extra, eu criei para conseguir manipulá-la fora do "for" e garantir que o numero se mova ate uma parede/celula diferente.
                            if (tabuleiro[i][k-1] == 0) {
                                tabuleiro[i][k-1] = tabuleiro[i][k];
                                tabuleiro[i][k] = 0;
                                k--;
                                moveu = 1;



                            } else if (tabuleiro[i][k-1] == tabuleiro[i][k] && !juntou[k-1]) { //se célula adjacente tiver valor igual E não somou ainda, soma e move
                                tabuleiro[i][k-1] *= 2;
                                tabuleiro[i][k] = 0;
                                juntou[k-1] = 1;
                                moveu = 1;
                                pontuacaoRodada += tabuleiro[i][k-1];
                                break;
                            } else { //nao foi movida nem juntada, mas sua posicao ainda é valida
                                break;
                            }
                        }
                    }
                }
            }
        break;

        case 'd': // Movimento para a direita
            for(int i = 0; i < 4; i++) {
                int juntou[4] = {0}; //criei esse array para saber quando os números ja foram somados e não somalos novamente no mesmo input.
                for(int j = 2; j >= 0; j--) {
                    if(tabuleiro[i][j]) {
                        //se a célula não for vazia
                        int k = j;

                        while(k < 3) {
                            //se célula adjacente estiver vazia, mover na direcao
                            //k é uma variavel extra, eu criei para conseguir manipulá-la fora do "for" e garantir que o numero se mova ate uma parede/celula diferente.
                            if(tabuleiro[i][k + 1] == 0) {
                                tabuleiro[i][k + 1] = tabuleiro[i][k];
                                tabuleiro[i][k] = 0;
                                k++;
                                moveu = 1;

                            } else if(tabuleiro[i][k + 1] == tabuleiro[i][k] && !juntou[k + 1]) {
                                //se célula adjacente tiver valor igual E não somou ainda, soma e move
                                tabuleiro[i][k + 1] *= 2;
                                tabuleiro[i][k] = 0;
                                juntou[k + 1] = 1;
                                moveu = 1;
                                pontuacaoRodada += tabuleiro[i][k + 1];
                                break;
                            } else {
                                //nao foi movida nem juntada, mas sua posicao ainda é valida
                                break;
                            }
                        }
                    }
                }
            }
            break;


        case 's': // Movimento para baixo
            for(int j = 0; j < 4; j++) { //checa as colunas primeiro agora ao invés das linhas
                int juntou[4] = {0}; //criei esse array para saber quando os números ja foram somados e não somalos novamente no mesmo input.
                for(int i = 2; i >= 0; i--) {
                    if(tabuleiro[i][j]) {
                        //se a célula não for vazia
                        int k = i;

                        while(k < 3) {
                            if(tabuleiro[k + 1][j] == 0) {
                                tabuleiro[k + 1][j] = tabuleiro[k][j];
                                tabuleiro[k][j] = 0;
                                k++;
                                moveu = 1;
                            } else if(tabuleiro[k + 1][j] == tabuleiro[k][j] && !juntou[k + 1]) {
                                //se célula adjacente tiver valor igual E não somou ainda, soma e move
                                tabuleiro[k + 1][j] *= 2;
                                tabuleiro[k][j] = 0;
                                juntou[k + 1] = 1;
                                moveu = 1;
                                pontuacaoRodada += tabuleiro[k + 1][j];
                                break;
                            } else {
                                //nao foi movida nem juntada, mas sua posicao ainda é valida
                                break;
                            }
                        }
                    }
                }
            }
            break;


        case 'w': // Movimento para cima
            for(int j = 0; j < 4; j++) {
                // checa as colunas primeiro
                int juntou[4] = {0};
                for(int i = 1; i < 4; i++) {
                    if(tabuleiro[i][j]) {
                        int k = i;

                        while(k > 0) {
                            if(tabuleiro[k - 1][j] == 0) {
                                tabuleiro[k - 1][j] = tabuleiro[k][j];
                                tabuleiro[k][j] = 0;
                                k--;
                                moveu = 1;

                            } else if(tabuleiro[k - 1][j] == tabuleiro[k][j] && !juntou[k - 1]) {
                                tabuleiro[k - 1][j] *= 2;
                                tabuleiro[k][j] = 0;
                                juntou[k - 1] = 1;
                                moveu = 1;
                                pontuacaoRodada += tabuleiro[k - 1][j];
                                break;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
    pontuacao += pontuacaoRodada;
    return moveu;
}

void geraPeca(int tabuleiro[4][4]){
    //sorteia uma coordenada aleatoria
    int x = rand() % 4;
    int y = rand() % 4;

    //se existe uma peca nessa coordenada, sorteia outra
    while(tabuleiro[x][y]) {
        x = rand() % 4;
        y = rand() % 4;
    }
    int num = rand() % 10;
    if(num < 8) {
        tabuleiro[x][y] = 2;
    }else {
        tabuleiro[x][y] = 4;
    }
}

int checaDerrota(int tabuleiro[4][4]){
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
            if(!tabuleiro[i][j]) {
                return 0;
            }
            //checa se existem peças adjacentes iguais dentro dos limites da matriz
            if((i > 0 && tabuleiro[i][j] == tabuleiro[i-1][j])
                || (j > 0 && tabuleiro[i][j] == tabuleiro[i][j-1])
                || (i < 3 && tabuleiro[i][j] == tabuleiro[i+1][j])
                || (j < 3 && tabuleiro[i][j] == tabuleiro[i][j+1])){

                return 0;
            }

        }
    }
    //derrota
    return 1;
}
int checaVitoria(int tabuleiro[4][4]){
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
            if(tabuleiro[i][j] == 2048) {
                return 1;
            }
        }
    }
    return 0;
}

//Parte visual do jogo daqui pra baixo
int botao(Rectangle rec, char texto[], Color cor){
    Vector2 pos = {rec.x, rec.y};
    Vector2 tamanho = {rec.width, rec.height};

    DrawRectangleRounded(rec, 0.2, 32, cor);
    DrawRectangleRoundedLinesEx(rec, 0.2, 32, 5, (Color){250, 248, 240, 255});
    DrawText(texto, pos.x + (tamanho.x / 2) - (MeasureText(texto, 20) / 2), pos.y + (tamanho.y / 2) - (MeasureTextEx(GetFontDefault(), texto, 20, 1).y / 2), 20, BLACK);

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rec)) {
        return 1;
    }

    return 0;


}


void telaDerrota(){
    int larguraTela = GetScreenWidth();
    int alturaTela = GetScreenHeight();
    int alturaMenu = 630;

    Color corBorda = (Color){156, 138, 123, 255};
    Color corFundo = (Color){250, 248, 240, 255};

    Rectangle gameOver = {(larguraTela / 2) - ((larguraTela*0.9) / 2), alturaMenu + 10, larguraTela*0.9, 325};
    DrawRectangleRoundedLinesEx(gameOver, 0.2, 32, 5, corBorda);
    DrawRectangleRounded(gameOver, 0.2, 32, corFundo);
    DrawText("Game Over", (larguraTela / 2) - (MeasureText("Game Over", 40) / 2), alturaMenu + 25, 40, BLACK);


    Rectangle jogarNovamente = {gameOver.x + 10, gameOver.y + 100, gameOver.width - 20, 50};
    if(botao(jogarNovamente, "Jogar Novamente", (Color){244, 203, 71, 255})) {
        pontuacao = 0;
        limpaTabuleiro(tabuleiro);
        geraPeca(tabuleiro);
        geraPeca(tabuleiro);
        vitoria = 0;

    }

    Rectangle sair = {gameOver.x + 10, gameOver.y + 170, gameOver.width - 20, 50};
    if(botao(sair, "Sair", (Color){250, 124, 80, 255})) {
        CloseWindow();
    }


}

void desenhaGrade(Rectangle recTabuleiro, Color corVazio){
    float alturaQuadrado = (recTabuleiro.height - 5 * MARGEM) / 4.0f;
    float larguraQuadrado = (recTabuleiro.width - 5 * MARGEM) / 4.0f;
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
            float posX = recTabuleiro.x + MARGEM + (j * (larguraQuadrado + MARGEM));
            float posY = recTabuleiro.y + MARGEM + (i * (alturaQuadrado + MARGEM));
            Rectangle quadrado = {posX, posY, larguraQuadrado, alturaQuadrado};
            DrawRectangleRounded(quadrado, 0.1, 32, corVazio);

        }
    }
}


void desenhaQuadrado(Rectangle recTabuleiro, Vector2 pos, int valor){
    Color corQuadrado;
    Color corTexto;

    switch(valor) {
        case 0:
            corQuadrado = (Color){189, 172, 151, 255};;
            break;
        case 2:
            corQuadrado = (Color){238, 228, 218, 255};
            corTexto = (Color){117, 100, 82, 255};
            break;
        case 4:
            corQuadrado = (Color){235, 216, 182, 255};
            corTexto = (Color){117, 100, 82, 255};
            break;
        case 8:
            corQuadrado = (Color){242, 174, 114, 255};
            corTexto = (Color){255, 255, 255, 255};
            break;
        case 16:
            corQuadrado = (Color){246, 148, 97, 255};
            corTexto = (Color){255, 255, 255, 255};
            break;
        case 32:
            corQuadrado = (Color){250, 124, 80, 255};
            corTexto = (Color){255, 255, 255, 255};
            break;
        case 64:
            corQuadrado = (Color){245, 91, 55, 255};
            corTexto = (Color){255, 255, 255, 255};
            break;
        case 128:
            corQuadrado = (Color){244, 203, 71, 255};
            corTexto = (Color){255, 255, 255, 255};
            break;
        case 256:
            corQuadrado = (Color){244, 203, 71, 255};
            corTexto = (Color){255, 255, 255, 255};
            break;
        default:
            corQuadrado = (Color){244, 203, 71, 255};
            corTexto = (Color){255, 255, 255, 255};
            break;
    }



    float alturaQuadrado = (recTabuleiro.height - 5 * MARGEM) / 4.0f;
    float larguraQuadrado = (recTabuleiro.width - 5 * MARGEM) / 4.0f;
    float posX = recTabuleiro.x + MARGEM + (pos.x * (larguraQuadrado + MARGEM));
    float posY = recTabuleiro.y + MARGEM + (pos.y * (alturaQuadrado + MARGEM));

    Rectangle quadrado = {posX, posY, larguraQuadrado, alturaQuadrado};
    DrawRectangleRounded(quadrado, 0.1, 32, corQuadrado);

    if(valor) {
        int tamanhoFonte = 40;
        int larguraTexto = MeasureText(TextFormat("%i", valor), tamanhoFonte);
        int alturaTexto = tamanhoFonte;

        int posTextoX = posX + (larguraQuadrado / 2.0f) - (larguraTexto / 2);
        int posTextoY = posY + (alturaQuadrado / 2.0f) - (alturaTexto / 2);
        DrawText(TextFormat("%i", valor), posTextoX, posTextoY, tamanhoFonte, corTexto);
    }
}



int main(void){
    srand(time(NULL));

    limpaTabuleiro(tabuleiro);
    geraPeca(tabuleiro);
    geraPeca(tabuleiro);

    //teste vitoria
    //tabuleiro[0][0] = 1024;
    //tabuleiro[2][0] = 1024;

    InitWindow(600, 1000, "2048");
    SetTargetFPS(60);

    Rectangle recTabuleiro = {0, 30, 600, 600};

    Color color = {250, 248, 246, 255};
    Color corTabuleiro = {156, 138, 123, 255};
    Color corFundo = {235, 223, 221, 255};
    Color corVazio = {189, 172, 151, 255};




    //loop principal
    while(!WindowShouldClose()) {
        //Preparando a janela
        BeginDrawing();
        ClearBackground(corFundo);
        DrawRectangleRounded(recTabuleiro, 0.05, 32, corTabuleiro);
        desenhaGrade(recTabuleiro, corVazio);

        
            // captura os inputs
        KeyboardKey tecla = GetKeyPressed();
        char input = 0;
        if(tecla) {
            switch(tecla) {
                case KEY_W:
                    input = 'w';
                    break;
                case KEY_A:
                    input = 'a';
                    break;
                case KEY_S:
                    input = 's';
                    break;
                case KEY_D:
                    input = 'd';
                    break;
                default:
                    break;
            }
        }
        if(input) {
            int moveu = move(tabuleiro, input);
            if(moveu) {
                geraPeca(tabuleiro);
            }
        }
        // desenhar a matriz na tela
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(tabuleiro[i][j]) {
                    // invertido, pois j = x e i = y
                    Vector2 pos = {j, i};
                    desenhaQuadrado(recTabuleiro, pos, tabuleiro[i][j]);
                }
            }
        }
        if(checaDerrota(tabuleiro)) {
            telaDerrota();
        }

        if(checaVitoria(tabuleiro) && !vitoria) {
            Rectangle recVitoria = {GetScreenWidth() / 2 - (GetScreenWidth()*0.25), recTabuleiro.y + (recTabuleiro.height / 2) - recTabuleiro.y*0.4, GetScreenWidth()*0.5, recTabuleiro.y*0.4};
            char texto[] = "Vitória!";
            DrawText(texto, recVitoria.x + (recVitoria.width / 2) - (MeasureText(texto, 40) / 2), recVitoria.y + (recVitoria.height / 2) - (MeasureTextEx(GetFontDefault(), texto, 40, 1).y / 2), 40, BLACK);
            Rectangle recContinuar = {recVitoria.x + 10, recVitoria.y + recVitoria.height + 15, recVitoria.width - 20, 50};
            if(botao(recContinuar, "Continuar", (Color){244, 203, 71, 255})) {
                vitoria = 1;
            }
        }

        //pontuação
        Rectangle pontuacaoTexto = { (GetScreenWidth() / 2) - 100, 870, 200, 80};
        DrawRectangleRounded(pontuacaoTexto, 0.2, 32, (Color){242, 174, 114, 255});
        DrawText("Pontuação: ", pontuacaoTexto.x + 10, pontuacaoTexto.y + 5, 30, BLACK);
        DrawText(TextFormat("%i", pontuacao), pontuacaoTexto.x + 10, pontuacaoTexto.y + 40, 20, BLACK);



        EndDrawing();

    }

    CloseWindow();

    return 0;
}