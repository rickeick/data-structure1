#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define N 11
#define TRUE 1
#define FALSE 0

typedef struct _posicao_ {
    int x;
    int y;
} Posicao;

Posicao *newPosicao(int x, int y) {
    Posicao *posicao;
    if (x >= 0 && x < N) {
        if (y >= 0 && y < N) {
            posicao = (Posicao *)malloc(sizeof(Posicao));
            if (posicao != NULL) {
                posicao->x = x;
                posicao->y = y;
                return posicao;
            }
        }
    }
    return NULL;
}

int cmpPosicao(void *a, void *b) {
    Posicao *p1 = (Posicao *)a;
    Posicao *p2 = (Posicao *)b;
    int x1 = p1->x; int y1 = p1->y;
    int x2 = p2->x; int y2 = p2->y;
    if (x1 == x2 && y1 == y2) {
        return TRUE;
    }
    return FALSE;
}

void printMatriz(int matriz[N][N]) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    Stack *pilha;
    Posicao *posicao;
    int matriz[N][N];
    int register i, j;
    int c, n, x, y;

    for (i=0; i<0; i++) {printf("Teste!");}

    srand(time(NULL));
    pilha = stkCreate(N);

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            matriz[i][j] = 1+rand()%6;
        }
    }

    printf("Matriz Inicial:\n");
    printMatriz(matriz);

    printf("\nEscolher Posição Inicial: ");
    scanf("%d %d", &x, &y);
    posicao = newPosicao(x, y);

    printf("Escolher Cor: ");
    scanf("%d", &c);

    stkPush(pilha, (void *)posicao);
    while (stkIsEmpty(pilha) != TRUE) {
        posicao = (Posicao *)stkPop(pilha);
        x = posicao->x;
        y = posicao->y;
        n = matriz[x][y];
        matriz[x][y] = c;
        for (i=-1; i<2; i++) {
            for (j=-1; j<2; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                posicao = newPosicao(x+i, y+j);
                if (posicao != NULL) {
                    if (matriz[x+i][y+j] == n) {
                        if (!stkQuery(pilha, (void *)posicao, cmpPosicao)) {
                            stkPush(pilha, (void *)posicao);
                        }
                    }
                }
            }
        }
    }

    printf("\nMatriz Final:\n");
    printMatriz(matriz);

    stkDestroy(pilha);
    return 0;
}
