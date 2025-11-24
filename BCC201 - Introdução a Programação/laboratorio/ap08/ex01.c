/*Faça um programa imprima na tela um quadrado NXN oco formado apenas por uma letra qualquer. O tamanho do quadrado é dado pelo usuário. Dica: Faça o quadrado cheio primeiro para depois tentar o oco. A entrada é composta por uma letra e por um número inteiro e positivo (faça a validação desse número). A saída de seu programa será formada pela borda do quadrado.*/

#include <stdio.h>
#include <ctype.h>

int main() {
  int n; char letra;

  //recebendo letra e n
  printf("Letra: ");
  letra = toupper(getchar());
  do {
    printf("N: ");
    scanf("%d", &n);
  } while(n<=0);
    
  for (int i=0; i<n; i++) {
    printf("\n");
    for (int j=0; j<n; j++) {
      if (i == 0 || i == n-1)
        printf("%c ", letra);
      else if (j == 0 || j == n-1)
        printf("%c ", letra);
      else
        printf("  ");
    }
  }

  printf("\n");
  return 0;
}