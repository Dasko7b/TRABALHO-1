#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iniciarFila(Fila* fila) {
    if (fila == NULL) {
        return 1;
    }
    fila->proximo = fila;
    fila->tem_pessoa = 0;
    fila->nome[0] = '\0';
    fila->CPF[0] = '\0';
    fila->curso[0] = '\0';
    return 0;
}

int iniciarAtendimentos(Atendimento* atendimento) {
    if (atendimento == NULL) {
        return 1;
    }
    atendimento->prox = NULL;
    atendimento->tem_pessoa = 0;
    atendimento->nome[0] = '\0';
    atendimento->CPF[0] = '\0';
    atendimento->curso[0] = '\0';
    atendimento->psicologo[0] = '\0';
    atendimento->data[0] = '\0';
    atendimento->resumo[0] = '\0';
    return 0;
}

void regitrarChegada(Fila* fila, char nome[100], char CPF[15], char curso[50]) {
    if (fila == NULL) {
        printf("ERRO: Fila principal não alocada/inicializada.\n");
        return;
    }

    if (fila->tem_pessoa == 0) {
        strncpy(fila->nome, nome, 99);
        fila->nome[99] = '\0';
        strncpy(fila->CPF, CPF, 14);
        fila->CPF[14] = '\0';
        strncpy(fila->curso, curso, 49);
        fila->curso[49] = '\0';
        fila->tem_pessoa = 1;
        fila->proximo = fila;
    } else {
        Fila* iterador = fila;
        while (iterador->proximo != fila) {
            iterador = iterador->proximo;
        }

        Fila* novoNoFila = (Fila*)malloc(sizeof(Fila));
        if (novoNoFila == NULL) {
            printf("ERRO DE ALOCAÇÃO (Nó da Fila em regitrarChegada)\n");
            return;
        }
        strncpy(novoNoFila->nome, nome, 99);
        novoNoFila->nome[99] = '\0';
        strncpy(novoNoFila->CPF, CPF, 14);
        novoNoFila->CPF[14] = '\0';
        strncpy(novoNoFila->curso, curso, 49);
        novoNoFila->curso[49] = '\0';
        novoNoFila->tem_pessoa = 1;

        novoNoFila->proximo = fila;
        iterador->proximo = novoNoFila;
    }
}

int realizarAtendimento(Fila* fila, Atendimento* cabecaListaAtendimentos, char psicologo[100], char data[10], char resumo[500]) {
    if (fila == NULL || fila->tem_pessoa == 0) {
        printf("Fila vazia, nenhum atendimento para realizar.\n");
        return 1;
    }
    if (cabecaListaAtendimentos == NULL) {
        printf("ERRO: Lista de atendimentos não inicializada/passada corretamente.\n");
        return 1;
    }

    printf("Atendendo:\n");
    printf("  Nome: %s\n", fila->nome);
    printf("  CPF: %s\n", fila->CPF);
    printf("  Curso: %s\n", fila->curso);
    printf("  Psicólogo: %s\n", psicologo);
    printf("  Data: %s\n", data);
    printf("  Resumo: %s\n", resumo);

    if (cabecaListaAtendimentos->tem_pessoa == 0) {
        strncpy(cabecaListaAtendimentos->nome, fila->nome, 99);
        cabecaListaAtendimentos->nome[99] = '\0';
        strncpy(cabecaListaAtendimentos->CPF, fila->CPF, 14);
        cabecaListaAtendimentos->CPF[14] = '\0';
        strncpy(cabecaListaAtendimentos->curso, fila->curso, 49);
        cabecaListaAtendimentos->curso[49] = '\0';
        strncpy(cabecaListaAtendimentos->psicologo, psicologo, 99);
        cabecaListaAtendimentos->psicologo[99] = '\0';
        strncpy(cabecaListaAtendimentos->data, data, 9);
        cabecaListaAtendimentos->data[9] = '\0';
        strncpy(cabecaListaAtendimentos->resumo, resumo, 499);
        cabecaListaAtendimentos->resumo[499] = '\0';
        cabecaListaAtendimentos->tem_pessoa = 1;
        cabecaListaAtendimentos->prox = NULL;
    } else {
        Atendimento* novoAtendimento = (Atendimento*)malloc(sizeof(Atendimento));
        if (novoAtendimento == NULL) {
            printf("ERRO DE ALOCAÇÃO (Novo Nó de Atendimento)\n");
            return 1;
        }
        strncpy(novoAtendimento->nome, fila->nome, 99);
        novoAtendimento->nome[99] = '\0';
        strncpy(novoAtendimento->CPF, fila->CPF, 14);
        novoAtendimento->CPF[14] = '\0';
        strncpy(novoAtendimento->curso, fila->curso, 49);
        novoAtendimento->curso[49] = '\0';
        strncpy(novoAtendimento->psicologo, psicologo, 99);
        novoAtendimento->psicologo[99] = '\0';
        strncpy(novoAtendimento->data, data, 9);
        novoAtendimento->data[9] = '\0';
        strncpy(novoAtendimento->resumo, resumo, 499);
        novoAtendimento->resumo[499] = '\0';
        novoAtendimento->tem_pessoa = 1;
        novoAtendimento->prox = NULL;

        Atendimento* atualAtendimento = cabecaListaAtendimentos;
        while (atualAtendimento->prox != NULL) {
            atualAtendimento = atualAtendimento->prox;
        }
        atualAtendimento->prox = novoAtendimento;
    }

    if (fila->proximo == fila) {
        fila->tem_pessoa = 0;
        fila->nome[0] = '\0';
        fila->CPF[0] = '\0';
        fila->curso[0] = '\0';
    } else {
        Fila* proximoNoFila = fila->proximo;
        
        strncpy(fila->nome, proximoNoFila->nome, 99);
        fila->nome[99] = '\0';
        strncpy(fila->CPF, proximoNoFila->CPF, 14);
        fila->CPF[14] = '\0';
        strncpy(fila->curso, proximoNoFila->curso, 49);
        fila->curso[49] = '\0';

        fila->proximo = proximoNoFila->proximo;
        free(proximoNoFila);
    }

    printf("Atendimento registrado e pessoa removida da fila.\n");
    return 0;
}

int removerDaFila(Fila* fila) {
    if (fila == NULL || fila->tem_pessoa == 0) {
        printf("Fila vazia, nada para remover.\n");
        return 1;
    }

    printf("Removendo da frente da fila: Nome: %s, CPF: %s\n", fila->nome, fila->CPF);

    if (fila->proximo == fila) {
        fila->tem_pessoa = 0;
        fila->nome[0] = '\0';
        fila->CPF[0] = '\0';
        fila->curso[0] = '\0';
        printf("Único elemento da fila removido. Fila agora está vazia.\n");
    } else {
        Fila* proximoNo = fila->proximo;

        strncpy(fila->nome, proximoNo->nome, 99);
        fila->nome[99] = '\0';
        strncpy(fila->CPF, proximoNo->CPF, 14);
        fila->CPF[14] = '\0';
        strncpy(fila->curso, proximoNo->curso, 49);
        fila->curso[49] = '\0';

        fila->proximo = proximoNo->proximo;
        free(proximoNo);
        printf("Primeiro elemento da fila removido com sucesso.\n");
    }
    return 0;
}

void listarFila(Fila* fila) {
    if (fila == NULL || fila->tem_pessoa == 0) {
        printf("Fila esta vazia.\n");
        return;
    }

    Fila* atual = fila;
    printf("--- PESSOAS NA FILA ---\n");
    do {
        printf("Nome: %s\n", atual->nome);
        printf("CPF: %s\n", atual->CPF);
        printf("Curso: %s\n", atual->curso);
        printf("------------------------\n");
        atual = atual->proximo;
    } while (atual != fila);
}