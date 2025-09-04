/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

struct Racional {
    int numerador;
    int denominador;
};

int mdc(int a, int b);
void simplifica(struct Racional *r);
int equal(struct Racional r1, struct Racional r2, struct Racional *r3);

int main() {
    struct Racional r1, r2, r3;
    int res;

    // recebendo valores
    printf("Digite numerador e denominador de r1: ");
    scanf("%d %d", &r1.numerador, &r1.denominador);

    printf("Digite numerador e denominador de r2: ");
    scanf("%d %d", &r2.numerador, &r2.denominador);

    // comparando valores recebidos
    res = equal(r1, r2, &r3);

    // printando resultado
    if (res == 0)
        printf("r1 e r2 são diferentes!\n");
    else
        printf("r1 e r2 são iguais a (%d / %d)!\n", r3.numerador, r3.denominador);

    return 0;
}

// calcula o máximo divisor comum (MDC)
int mdc(int a, int b) {
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

// simplifica um número racional
void simplifica(struct Racional *r) {
    int divisor = mdc(r->numerador, r->denominador);
    r->numerador /= divisor;
    r->denominador /= divisor;

    // manter o sinal no numerador
    if (r->denominador < 0) {
        r->numerador *= -1;
        r->denominador *= -1;
    }
}

// verifica se dois racionais são iguais
int equal(struct Racional r1, struct Racional r2, struct Racional *r3) {
    simplifica(&r1);
    simplifica(&r2);

    if (r1.numerador == r2.numerador && r1.denominador == r2.denominador) {
        *r3 = r1; // pode ser r2 também, pois são iguais
        return 1;
    }
    return 0;
}
