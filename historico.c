#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializa o histórico
void inicializarHistorico(Historico* h) {
    h->atendimentos = (AtendimentoHistorico*) malloc(INICIAL * sizeof(AtendimentoHistorico));
    h->capacidade = INICIAL;
    h->totalAtendimentos = 0;
}

// Redimensiona se necessário
void redimensionarHistorico(Historico* h, int novaCapacidade) {
    AtendimentoHistorico* temp = (AtendimentoHistorico*) realloc(h->atendimentos, novaCapacidade * sizeof(AtendimentoHistorico));
    if (temp == NULL) {
        printf("Erro ao realocar memória.\n");
        exit(1);
    }
    h->atendimentos = temp;
    h->capacidade = novaCapacidade;
}

// Adiciona um atendimento
void adicionarAtendimento(Historico* h, char* nomePaciente, char* cpf, char* psicologo, char* cursoPaciente, char* descricao) {
    if (h->totalAtendimentos == h->capacidade) {
        redimensionarHistorico(h, h->capacidade * 2);
    }

    AtendimentoHistorico novoItemHistorico;

    strcpy(novoItemHistorico.nomePaciente, nomePaciente);
    strcpy(novoItemHistorico.cpf, cpf);
    strcpy(novoItemHistorico.psicologo, psicologo);
    strcpy(novoItemHistorico.cursoPaciente, cursoPaciente);
    strcpy(novoItemHistorico.descricao, descricao);

    h->atendimentos[h->totalAtendimentos] = novoItemHistorico;
    h->totalAtendimentos++;
}

// Lista todos os atendimentos
void listarTodosAtendimentos(Historico* h) {
    for (int i = 0; i < h->totalAtendimentos; i++) {
        printf("Nome: %s | CPF: %s | Psicologo: %s | Curso: %s\nDescricao: %s\n\n",
            h->atendimentos[i].nomePaciente,
            h->atendimentos[i].cpf,
            h->atendimentos[i].psicologo,
            h->atendimentos[i].cursoPaciente,
            h->atendimentos[i].descricao);
    }
}

// Lista atendimentos por CPF
void listarAtendimentosPorCPF(Historico* h, char* cpf) {
    int encontrou = 0;
    for (int i = 0; i < h->totalAtendimentos; i++) {
        if (strcmp(h->atendimentos[i].cpf, cpf) == 0) {
            if (!encontrou) {
                printf("\n=== HISTÓRICO DO CPF: %s ===\n", cpf);
                encontrou = 1;
            }
            printf("Nome: %s | CPF: %s | Psicologo: %s | Curso: %s\nDescricao: %s\n\n",
                h->atendimentos[i].nomePaciente,
                h->atendimentos[i].cpf,
                h->atendimentos[i].psicologo,
                h->atendimentos[i].cursoPaciente,
                h->atendimentos[i].descricao);
        }
    }
    if (!encontrou) {
        printf("Nenhum atendimento encontrado para o CPF %s.\n", cpf);
    }
}

// Lista atendimentos por Curso
void listarAtendimentosPorCurso(Historico* h, char* curso) {
    int encontrou = 0;
    for (int i = 0; i < h->totalAtendimentos; i++) {
        if (strcmp(h->atendimentos[i].cursoPaciente, curso) == 0) {
            if (!encontrou) {
                printf("\n=== HISTÓRICO DO CURSO: %s ===\n", curso);
                encontrou = 1;
            }
            printf("Nome: %s | CPF: %s | Psicologo: %s | Curso: %s\nDescricao: %s\n\n",
                h->atendimentos[i].nomePaciente,
                h->atendimentos[i].cpf,
                h->atendimentos[i].psicologo,
                h->atendimentos[i].cursoPaciente,
                h->atendimentos[i].descricao);
        }
    }
    if (!encontrou) {
        printf("Nenhum atendimento encontrado para o curso %s.\n", curso);
    }
}

// Libera memória
void destruirHistorico(Historico* h) {
    free(h->atendimentos);
    h->atendimentos = NULL;
    h->capacidade = 0;
    h->totalAtendimentos = 0;
}
