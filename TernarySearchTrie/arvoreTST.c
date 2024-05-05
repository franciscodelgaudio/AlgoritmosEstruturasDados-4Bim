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

/*int removerTST(TST_TRIE * r, char str[],
                int level ,int n)
{
    if (root == NULL)
        return 0;
 
 
    // CASE 4 Key present in TST, having
    // atleast one other key as prefix key.
    if (str[level+1] == '\0')
    {
        // Unmark leaf node if present
        if (isLeaf(root))
        {
            root->isleaf=0;
            return isFreeNode(root);
        }
 
        // else string is not present in TST and
        // return 0
        else
            return 0;
    }
    else
    {
        // CASE 3 Key is prefix key of another
        // long key in TST.
        if (str[level] < root->key)
            delete_node(root->left ,str ,level ,n);
        else if (str[level] > root->key)
            delete_node(root->right ,str ,level ,n);
 
        // CASE 1 Key may not be there in TST.
        else if (str[level] == root->key)
        {
            // CASE 2 Key present as unique key
            if( delete_node(root->eq ,str ,level+1 ,n) )
            {
                // delete the last node, neither it
                // has any child
                // nor it is part of any other string
                free(root->eq);
                return !isLeaf(root) && isFreeNode(root);
            }
        }
    }
 
    return 0;
}*/

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