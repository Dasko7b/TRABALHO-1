#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iniciarFila(Fila* fila) {
    if (fila == NULL) {
        return 1;
    }
    fila->proximo = fila;
    fila->pessoa = NULL;
    return 0;
}

int inicarAtendimentos(Atendimento* atendimento) {
    if (atendimento == NULL) {
        return 1;
    }
    atendimento->prox = NULL;
    atendimento->pessoa = NULL;
    return 0;
}

void regitrarChegada(Fila* fila, char nome[100], char CPF[15], char curso[50]) {
    if (fila == NULL) {
        printf("ERRO: Fila principal não alocada/inicializada.\n");
        return;
    }

    Pessoa* novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));
    if (novaPessoa == NULL) {
        printf("ERRO DE ALOCAÇÃO (Pessoa em regitrarChegada)\n");
        return;
    }
    strncpy(novaPessoa->nome, nome, 99);
    novaPessoa->nome[99] = '\0';
    strncpy(novaPessoa->CPF, CPF, 14);
    novaPessoa->CPF[14] = '\0';
    strncpy(novaPessoa->curso, curso, 49);
    novaPessoa->curso[49] = '\0';

    if (fila->pessoa == NULL) {
        fila->pessoa = novaPessoa;
        fila->proximo = fila;
    } else {
        Fila* iterador = fila;
        while (iterador->proximo != fila) {
            iterador = iterador->proximo;
        }

        Fila* novoNoFila = (Fila*)malloc(sizeof(Fila));
        if (novoNoFila == NULL) {
            printf("ERRO DE ALOCAÇÃO (Nó da Fila em regitrarChegada)\n");
            free(novaPessoa);
            return;
        }
        novoNoFila->pessoa = novaPessoa;
        novoNoFila->proximo = fila;
        iterador->proximo = novoNoFila;
    }
}

int realizarAtendimento(Fila* fila, char psicologo[100], char data[10], char resumo[500]) {
    if (fila == NULL || fila->pessoa == NULL) {
        printf("Fila vazia, nenhum atendimento para realizar.\n");
        return 1;
    }

    Pessoa* pessoaAtendidaOriginal = fila->pessoa;

    printf("Atendendo:\n");
    printf("  Nome: %s\n", pessoaAtendidaOriginal->nome);
    printf("  CPF: %s\n", pessoaAtendidaOriginal->CPF);
    printf("  Curso: %s\n", pessoaAtendidaOriginal->curso);
    printf("  Psicólogo: %s\n", psicologo);
    printf("  Data: %s\n", data);
    printf("  Resumo: %s\n", resumo);

    if (fila->proximo == fila) {
        free(fila->pessoa);
        fila->pessoa = NULL;
    } else {
        Fila* proximoNo = fila->proximo;
        free(fila->pessoa);

        fila->pessoa = proximoNo->pessoa;
        fila->proximo = proximoNo->proximo;
        
        free(proximoNo);
    }
    return 0;
}

int removerDaFila(Fila* fila) {
    if (fila == NULL || fila->pessoa == NULL) {
        printf("Fila vazia, nada para remover.\n");
        return 1;
    }

    Pessoa* pessoaDaCabecaOriginal = fila->pessoa;

    if (fila->proximo == fila) {
        free(pessoaDaCabecaOriginal);
        fila->pessoa = NULL;
        printf("Único elemento da fila removido. Fila agora está vazia.\n");
    } else {
        Fila* proximoNo = fila->proximo;

        fila->pessoa = proximoNo->pessoa;
        fila->proximo = proximoNo->proximo;

        free(pessoaDaCabecaOriginal);
        free(proximoNo);
        printf("Primeiro elemento da fila removido com sucesso.\n");
    }

    return 0;
}

void listarFila(Fila* fila) {
    if (fila == NULL || fila->pessoa == NULL) {
        printf("Fila esta vazia.\n");
        return;
    }

    Fila* atual = fila;
    printf("--- PESSOAS NA FILA ---\n");
    do {
        if (atual->pessoa != NULL) { 
            printf("Nome: %s\n", atual->pessoa->nome);
            printf("CPF: %s\n", atual->pessoa->CPF);
            printf("Curso: %s\n", atual->pessoa->curso);
            printf("------------------------\n");
        }
        atual = atual->proximo;
    } while (atual != fila && atual != NULL);
}