#include <stdio.h>
#include <stdlib.h>

typedef struct noTST {
    char ch; // Caractere da TRIE
    int valor; // Valor associado à chave
    struct noTST *menor; // Antes de ch na ordem lexicográfica
    struct noTST *igual;
    struct noTST *maior; // Depois de ch na ordem lexicográfica
} noTST_TRIE;

typedef noTST_TRIE *TST_TRIE;

noTST_TRIE *criaNo(char ch, int valor, noTST_TRIE *menor, noTST_TRIE *igual, noTST_TRIE *maior) {
    noTST_TRIE *aux = (noTST_TRIE *)malloc(sizeof(noTST_TRIE));
    aux->ch = ch;
    aux->valor = valor;
    aux->menor = menor;
    aux->igual = igual;
    aux->maior = maior;
    return aux;
}

void inserirTST(TST_TRIE * r, char* str, int valor){ 
    if (*r == NULL) 
        *r = criaNo(*str, valor, NULL, NULL, NULL); 
  
    if ((*str) < (*r)->ch) 
        inserirTST(&((*r)->menor), str, valor); 
  
    else if ((*str) > (*r)->ch) 
        inserirTST(&((*r)->maior), str, valor); 
   
    else { 
        if (*(str + 1)) 
            inserirTST(&((*r)->igual), str + 1, valor); 
  
        else
            (*r)->valor = valor; 
    } 
}

int buscarTST(TST_TRIE * r, char *str) 
{ 
    if (*r == NULL) 
        return 0; 
  
    if ((*str) < (*r)->ch) 
        return buscarTST(&((*r)->menor), str); 
  
    else if ((*str) > (*r)->ch) 
        return buscarTST(&((*r)->maior), str); 
  
    else { 
        if (*(str + 1) == '\0') 
            return (*r)->valor; 
  
        return buscarTST(&((*r)->igual), str + 1); 
    } 
} 

int main() {
    TST_TRIE r = NULL;
    // Exemplo de inserção de palavras na árvore Trie
    inserirTST(&r, "apple", 1);
    inserirTST(&r, "banana", 2);
    inserirTST(&r, "app", 5);
    printf("%d", buscarTST(&r, "banana"));
    return 0;
}