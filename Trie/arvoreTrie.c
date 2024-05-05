#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ALFABETO 26
#define ASCII_BASE 97

typedef struct no {
    struct no *filho[TAM_ALFABETO];
    int valor;
} noTRIE;

typedef struct {
    noTRIE *raiz;
} arvTRIE;

arvTRIE *novaArvore() {
    arvTRIE *aux = (arvTRIE *)malloc(sizeof(arvTRIE));
    aux->raiz = NULL; // Inicialize a raiz como NULL
    return aux;
}

noTRIE *novoNo() {
    noTRIE *aux = (noTRIE *)malloc(sizeof(noTRIE));
    for (int i = 0; i < TAM_ALFABETO; i++) {
        aux->filho[i] = NULL;
    }
    aux->valor = 0; // Inicialize o valor como 0
    return aux;
}

void inserir(arvTRIE *r, char *str, int valor) {
    if (r->raiz == NULL) {
        r->raiz = novoNo();
    }

    noTRIE *atual = r->raiz;
    for (int i = 0; str[i]; i++) {
        int index = str[i] - ASCII_BASE;
        if (atual->filho[index] == NULL) {
            atual->filho[index] = novoNo();
        }
        atual = atual->filho[index];
        if (str[i + 1] == '\0') {
            atual->valor = valor;
        }
    }
}

noTRIE *removerRecursivo(noTRIE *atual, char *str, int pos) {
    if (atual == NULL) {
        return NULL;
    }
    if (str[pos] == '\0') {
        // Chegamos ao final da palavra
        free(atual);
        return NULL;
    }
    int indice = str[pos] - ASCII_BASE;
    atual->filho[indice] = removerRecursivo(atual->filho[indice], str, pos + 1);

    // Verifica se o nó atual pode ser removido
    for (int i = 0; i < TAM_ALFABETO; i++) {
        if (atual->filho[i] != NULL) {
            return atual; // Não pode ser removido
        }
    }
    free(atual);
    return NULL;
}

void remover(arvTRIE *r, char *str) {
    r->raiz = removerRecursivo(r->raiz, str, 0);
}

void imprimirPalavras(noTRIE *atual, char *prefixo, int nivel) {
    if (atual->valor) {
        prefixo[nivel] = '\0';
        printf("%s\n", prefixo);
    }
    for (int i = 0; i < TAM_ALFABETO; i++) {
        if (atual->filho[i]) {
            prefixo[nivel] = i + ASCII_BASE;
            imprimirPalavras(atual->filho[i], prefixo, nivel + 1);
        }
    }
}

void imprimir_dicionario(arvTRIE *r) {
    char prefixo[100]; // Tamanho máximo da palavra
    imprimirPalavras(r->raiz, prefixo, 0);
}

int buscar(arvTRIE * r, char * str){
    noTRIE * atual = r->raiz;
    for (int i = 0 ; str[i] ; i++){
        int indice = str[i] - ASCII_BASE;
        if (atual->filho[indice] == NULL) return 0;
        atual = atual->filho[indice];
    }
    return atual->valor;
}

int main() {
    arvTRIE *r = novaArvore();

    inserir(r, "francisco", 1);
    inserir(r, "frango", 2);
    inserir(r, "framboesa", 5);
    inserir(r, "aorizonte", 3);
    remover(r, "francisco");
    remover(r, "frango");
    printf("%d\n", buscar(r, "frango"));
    imprimir_dicionario(r);


    return 0;
}