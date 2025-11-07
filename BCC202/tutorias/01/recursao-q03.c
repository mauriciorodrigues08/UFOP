#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define TAMANHO_STR 30

void imprimeInvertido(char* str);
void imprimeInvertidoAux(char* str, int index);
bool ehPalindromo(char* str, int inicio, int fim);

int main(){
  int inicio, fim;
  char string[TAMANHO_STR];

  printf("Insira a string: ");
  fgets(string, TAMANHO_STR, stdin);

  int tamanhoStr = strlen(string);
  string[tamanhoStr - 1] = '\0';
  tamanhoStr--;

  for(int i = 0; i < tamanhoStr; i++)
    string[i] = tolower(string[i]);

  printf("\nA palavra: %s escrita ao contrario é: ", string);
  imprimeInvertido(string);
  inicio = 0;
  fim = tamanhoStr - 1;

  printf("\n%s %s\n", string, ehPalindromo(string, inicio, fim)? "É um palindromo":"Nao é palindromo");


  return 0;
}

void imprimeInvertido(char* str){
  imprimeInvertidoAux(str, strlen(str)-1);
}

void imprimeInvertidoAux(char* str, int index){
  if(index < 0)
    return;
  else{
    printf("%c", str[index]);
    return imprimeInvertidoAux(str, index-1);
  }
}

bool ehPalindromo(char* str, int inicio, int fim){
  if(str[inicio] != str[fim] || fim <= 0)
    return false;
  else if(inicio >= fim)
    return true;
  else
    return ehPalindromo(str, inicio + 1, fim - 1);
}