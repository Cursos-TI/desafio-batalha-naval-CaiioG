#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BOARD_SIZE 10
#define SKILL_SIZE 5

// Valores no tabuleiro
#define WATER 0
#define SHIP 3
#define SKILL_AREA 5

// Função para inicializar o tabuleiro com água (0)
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = WATER;
}

// Função para posicionar alguns navios no tabuleiro para exemplo
void placeShips(int board[BOARD_SIZE][BOARD_SIZE]) {
    // Exemplo simples: colocar navios em algumas posições fixas
    board[2][3] = SHIP;
    board[2][4] = SHIP;
    board[2][5] = SHIP;
    board[5][5] = SHIP;
    board[6][5] = SHIP;
    board[7][5] = SHIP;
    board[8][5] = SHIP;
}

// Função para criar a matriz de habilidade "Cone" (5x5)
// Cone apontando para baixo, origem no topo central (linha 0, coluna 2)
void createCone(int cone[SKILL_SIZE][SKILL_SIZE]) {
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            // Inicializa com 0
            cone[i][j] = 0;

            // Condicional para formar o cone:
            // Na linha 0, só o centro (col 2)
            // Na linha 1, colunas 1 a 3
            // Na linha 2, colunas 0 a 4
            // Linhas 3 e 4 podem ser 0 para simplificar
            if (i == 0 && j == 2)
                cone[i][j] = 1;
            else if (i == 1 && (j >= 1 && j <= 3))
                cone[i][j] = 1;
            else if (i == 2 && (j >= 0 && j <= 4))
                cone[i][j] = 1;
        }
    }
}

// Função para criar a matriz de habilidade "Cruz" (5x5)
// Cruz com origem no centro (linha 2, coluna 2)
void createCross(int cross[SKILL_SIZE][SKILL_SIZE]) {
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            cross[i][j] = 0;

            // Cruz: linha central e coluna central são 1
            if (i == 2 || j == 2)
                cross[i][j] = 1;
        }
    }
}

// Função para criar a matriz de habilidade "Octaedro" (5x5)
// Losango com origem no centro (linha 2, coluna 2)
void createOctahedron(int octa[SKILL_SIZE][SKILL_SIZE]) {
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            octa[i][j] = 0;

            // Distância de Manhattan do centro (2,2)
            int dist = abs(i - 2) + abs(j - 2);

            // Losango: posições com dist <= 2 são 1
            if (dist <= 2)
                octa[i][j] = 1;
        }
    }
}

// Função para sobrepor a matriz de habilidade no tabuleiro
// origemLinha e origemColuna são as coordenadas no tabuleiro onde o centro da habilidade será colocado
void applySkill(int board[BOARD_SIZE][BOARD_SIZE], int skill[SKILL_SIZE][SKILL_SIZE], int origemLinha, int origemColuna) {
    int offset = SKILL_SIZE / 2; // 2 para matriz 5x5

    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (skill[i][j] == 1) {
                int boardRow = origemLinha - offset + i;
                int boardCol = origemColuna - offset + j;

                // Verifica limites do tabuleiro
                if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                    // Marca área afetada somente se não for navio (3)
                    if (board[boardRow][boardCol] != SHIP) {
                        board[boardRow][boardCol] = SKILL_AREA;
                    }
                }
            }
        }
    }
}

// Função para imprimir o tabuleiro no console
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == WATER)
                printf("~ "); // Água
            else if (board[i][j] == SHIP)
                printf("S "); // Navio
            else if (board[i][j] == SKILL_AREA)
                printf("* "); // Área afetada pela habilidade
            else
                printf("? "); // Caso inesperado
        }
        printf("\n");
    }
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    int cone[SKILL_SIZE][SKILL_SIZE];
    int cross[SKILL_SIZE][SKILL_SIZE];
    int octa[SKILL_SIZE][SKILL_SIZE];

    // Inicializa tabuleiro e posiciona navios
    initBoard(board);
    placeShips(board);

    // Cria as matrizes de habilidade
    createCone(cone);
    createCross(cross);
    createOctahedron(octa);

    // Define pontos de origem para as habilidades no tabuleiro
    // Exemplo: cone no topo central, cruz no centro do tabuleiro, octaedro perto do canto inferior direito
    int coneOriginRow = 1, coneOriginCol = 4;
    int crossOriginRow = 5, crossOriginCol = 5;
    int octaOriginRow = 8, octaOriginCol = 7;

    // Aplica as habilidades no tabuleiro
    applySkill(board, cone, coneOriginRow, coneOriginCol);
    applySkill(board, cross, crossOriginRow, crossOriginCol);
    applySkill(board, octa, octaOriginRow, octaOriginCol);

    // Exibe o tabuleiro com as áreas de efeito
    printBoard(board);

    return 0;
}
