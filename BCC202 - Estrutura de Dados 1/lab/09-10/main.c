/*Receba dois vetores A e B com tamanho fixo N. Trate A como um vetor linha e B como um vetor coluna e calcule AxB e BxA. Crie uma função linhaColuna(), que receba os dois vetores e retorne AxB e uma função colunaLinha(), que receba os dois vetores e retorne BxA.*/

#include <stdio.h>
#define N 3

void linhaColuna(int *a, int *b, int *axb);
void colunaLinha(int *a, int *b, int bxa[][N]);

int main() {
    int a[N], b[N], bxa[N][N];
    int axb;
    
    //recebendo valores
    printf("Digite os valores do primeiro vetor: ");
    for (int i=0; i<N; i++) {
        scanf("%d", &a[i]);
    }
    
    printf("Digite os valores do segundo vetor: ");
    for (int i=0; i<N; i++) {
        scanf("%d", &b[i]);
    }   
    
    //chamando funções
    linhaColuna(a, b, &axb);
    colunaLinha(a, b, bxa);
    
    //printando primeiro resultado
    printf("\nAxB = %d", axb);
    
    //printando segundo resultado
    printf("\n\nBxA\n");
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            printf("%d ", bxa[i][j]);
        }
        printf("\n");
    }

    return 0;
}


void linhaColuna(int *a, int *b, int *axb) {
    *axb = 0;

    for (int i=0; i<N; i++) {
        *axb += a[i] * b[i];
    }
}

void colunaLinha(int *a, int *b, int bxa[][N]) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            bxa[i][j] = a[j] * b[i];
        }
    }
}