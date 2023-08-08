#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define FALSE 0
#define TRUE 1

int n, **tabuleiro;

typedef struct _posicao_ {
    int x;
    int y;
} Posicao;

Posicao *criarPosicao(int x, int y) {
    Posicao *posicao;
    if (x >= 0 && x < n) {
        if (y >= 0 && y < n) {
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

int validarPosicao(int x, int y) {
    int i=0, j=0;
    if (tabuleiro[x][y] == FALSE) {
        for (i; i<n; i++) {
            if (tabuleiro[i][y] == TRUE) {
                return FALSE;
            }
        }
        for (j; j<n; j++) {
            if (tabuleiro[x][j] == TRUE) {
                return FALSE;
            }
        }
        i=x, j=y;
        while (i>=0 && j>=0) {
            if (tabuleiro[i][j] == TRUE) {
                return FALSE;
            } i--; j--;
        }
        i=x, j=y;
        while (i>=0 && j<n) {
            if (tabuleiro[i][j] == TRUE) {
                return FALSE;
            } i--; j++;
        }
        i=x, j=y;
        while (i<n && j>=0) {
            if (tabuleiro[i][j] == TRUE) {
                return FALSE;
            } i++; j--;
        }
        i=x, j=y;
        while (i<n && j<n) {
            if (tabuleiro[i][j] == TRUE) {
                return FALSE;
            } i++; j++;
        }
        return TRUE;
    }
    return FALSE;
}

int main(void) {
    int stat, rainhas;
    int register lin, col;

    printf("Valor de N: "); scanf("%d", &n);

    tabuleiro = (int **)malloc(sizeof(int *)*n);
    for (lin=0; lin<n; lin++) {
        tabuleiro[lin] = (int *)malloc(sizeof(int)*n);
        for (col=0; col<n; col++) {
            tabuleiro[lin][col] = FALSE;
        }
    }

    Posicao *posicao;
    Stack *pilha = stkCreate(n);
    if (pilha != NULL) {
        rainhas = n;
        lin=0, col=0;
        stat = validarPosicao(lin, col);
        while (rainhas > 0) {
            while (col<n && stat == FALSE) {
                stat = validarPosicao(lin, col);
                if (stat == FALSE) {
                    col++;
                }
            }
            if (stat == TRUE) {
                posicao = criarPosicao(lin, col);
                stkPush(pilha, (void *)posicao);
                tabuleiro[lin][col] = TRUE;
                rainhas--;
                lin++;
                col=0;
            } else {
                posicao = (Posicao *)stkPop(pilha);
                if (posicao == NULL) {
                    printf("Não há solução para N = %d", n);
                    stkDestroy(pilha);
                    return 0;
                }
                lin = posicao->x; col = posicao->y;
                tabuleiro[lin][col] = FALSE;
                rainhas++;
                col++;
            }
            stat = FALSE;
        }
    }

    stat = stkDestroy(pilha);
    while (stat != TRUE) {
        (void)stkPop(pilha);
        stat = stkDestroy(pilha);
    }

    printf("Solução para N = %d:\n", n);
    for (lin=0; lin<n; lin++) {
        for (col=0; col<n; col++) {
            if (tabuleiro[lin][col] == TRUE) {
                printf("[X]");
            } else {
                printf("[ ]");
            }
        }
        printf("\n");
    }

    return 0;
}
