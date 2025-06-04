#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Historico* inicializarLista() {
    Historico* lista = (Historico*) malloc(sizeof(Historico));
    if (lista == NULL) {
        return NULL; 
    }

    lista->proximo = lista;

    return lista;
}
Historico* inserirNoHistorico(Historico* h, Atendimento a){

    Historico* novoNo = (Historico*) malloc(sizeof(Historico));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória.\n");
        return h;
    }

    
    strcpy(novoNo->atendimento.pessoa->CPF, a.pessoa->CPF);
    strcpy(novoNo->atendimento.pessoa->nome, a.pessoa->nome);
    strcpy(novoNo->atendimento.psicologo, a.psicologo);
    strcpy(novoNo->atendimento.data, a.data);
    strcpy(novoNo->atendimento.resumo, a.resumo);
    
    novoNo->proximo = NULL;

    return novoNo;

};

//Função para imprimir o histórico de atendimentos por curso
//Feita por Bruno Pedron Rupaner
void HistoricoPorCurso(Atendimento* h) {
    if (h == NULL || h->pessoa == NULL) {
        printf("Nenhum atendimento registrado.\n");
        return;
    }

    char cursosImpressos[100][50];
    int totalCursos = 0;

    Atendimento* atual = h;
    while (atual != NULL) {
        char* cursoAtual = atual->pessoa->curso;

        int jaExiste = 0;
        for (int i = 0; i < totalCursos; i++) {
            if (strcmp(cursosImpressos[i], cursoAtual) == 0) {
                jaExiste = 1;
                break;
            }
        }

        if (!jaExiste) {
            // Cabeçalho do curso
            printf("\n=== HISTÓRICO DO CURSO: %s ===\n", cursoAtual);
            Atendimento* temp = h;
            while (temp != NULL) {
                if (strcmp(temp->pessoa->curso, cursoAtual) == 0) {
                    printf("Nome: %s | CPF: %s\n", temp->pessoa->nome, temp->pessoa->CPF);
                    printf("Psicólogo: %s\n", temp->psicologo);
                    printf("Data: %s\n", temp->data);
                    printf("Resumo: %s\n", temp->resumo);
                    printf("-----------------------------\n");
                }
                temp = temp->prox;
            }

            strncpy(cursosImpressos[totalCursos], cursoAtual, 49);
            cursosImpressos[totalCursos][49] = '\0';
            totalCursos++;
        }

        atual = atual->prox;
    }
}

//Função para imprimir o histórico de atendimentos por CPF
//Feita por Bruno Pedron Rupaner
void HistoricoAtendimentoCPF(Atendimento* h, char cpf[15]) {
    if (h == NULL || h->pessoa == NULL) {
        printf("Nenhum atendimento registrado.\n");
        return;
    }

    int encontrou = 0;
    Atendimento* atual = h;
    while (atual != NULL) {
        if (strcmp(atual->pessoa->CPF, cpf) == 0) {
            if (!encontrou) {
                printf("\n=== HISTÓRICO DO CPF: %s ===\n", cpf);
            }

            encontrou = 1;

            printf("Nome: %s | Curso: %s\n", atual->pessoa->nome, atual->pessoa->curso);
            printf("Psicólogo: %s\n", atual->psicologo);
            printf("Data: %s\n", atual->data);
            printf("Resumo: %s\n", atual->resumo);
            printf("-----------------------------\n");
        }

        atual = atual->prox;
    }

    if (!encontrou) {
        printf("Nenhum atendimento encontrado para o CPF informado.\n");
    }
}