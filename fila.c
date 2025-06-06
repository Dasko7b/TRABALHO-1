#include "fila.h"
#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Matheus josé
// Inicializa a fila (o nó cabeça).
// O nó cabeça aponta para si mesmo e seu nome é marcado como vazio.
int iniciarFila(Fila* fila) {
    if (fila == NULL) {
        return 1; // Erro se a fila for nula
    }
    fila->proximo = fila;
    fila->nome[0] = '\0'; // Indica que o nó cabeça não contém dados de pessoa válidos
    fila->CPF[0] = '\0';
    fila->curso[0] = '\0';
    return 0;
}
//Mathues josé
// Inicializa a lista de atendimentos (o nó cabeça).
// O próximo é nulo e o nome é marcado como vazio.
// Nota: O nome da função no header fornecido é "inicarAtendimentos".
int inicarAtendimentos(Atendimento* atendimento) {
    if (atendimento == NULL) {
        return 1; // Erro se o atendimento for nulo
    }
    atendimento->prox = NULL;
    atendimento->nome[0] = '\0'; // Indica que o nó cabeça não contém dados de atendimento válidos
    atendimento->CPF[0] = '\0';
    atendimento->curso[0] = '\0';
    atendimento->psicologo[0] = '\0';
    atendimento->data[0] = '\0';
    atendimento->resumo[0] = '\0';
    return 0;
}
//Dyego Dasko
// Registra a chegada de uma nova pessoa na fila.
void regitrarChegada(Fila* fila, char nome[100], char CPF[15], char curso[50]) {
    if (fila == NULL) {
        printf("ERRO: Fila principal não alocada/inicializada.\n");
        return;
    }

    // Se o nó cabeça da fila está "vazio" (sem dados de pessoa), usa ele mesmo.
    if (fila->nome[0] == '\0') {
        strncpy(fila->nome, nome, 99);
        fila->nome[99] = '\0';
        strncpy(fila->CPF, CPF, 14);
        fila->CPF[14] = '\0';
        strncpy(fila->curso, curso, 49);
        fila->curso[49] = '\0';
        fila->proximo = fila; // Garante que aponta para si mesmo se for o único
    } else {
        // Se a fila não está vazia, encontra o último nó para inserir o novo após ele.
        Fila* iterador = fila;
        while (iterador->proximo != fila) {
            iterador = iterador->proximo;
        }

        // Aloca um novo nó para a nova pessoa.
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

        novoNoFila->proximo = fila;   // O novo nó aponta de volta para o cabeça.
        iterador->proximo = novoNoFila; // O antigo último nó aponta para o novo nó.
    }
}
//Dyego Dasko
// Realiza o atendimento da pessoa na frente da fila e a move para a lista de atendimentos. //adicionei mais um parametro para essa função , para poder char do historico.c
int realizarAtendimento(Fila* fila, Historico* h, Atendimento* cabecaListaAtendimentos, char psicologo[100], char data[10], char resumo[500]) {
    if (fila == NULL || fila->nome[0] == '\0') { // Verifica se a fila está vazia
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

    // Adiciona à lista de Atendimentos.
    // Se o nó cabeça da lista de atendimentos estiver "vazio", usa ele mesmo.
    if (cabecaListaAtendimentos->nome[0] == '\0') {
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
        cabecaListaAtendimentos->prox = NULL;

        //chama a função do historico.c
        adicionarAtendimento(h, cabecaListaAtendimentos->nome, cabecaListaAtendimentos->CPF, 
                     cabecaListaAtendimentos->psicologo, cabecaListaAtendimentos->curso, 
                     cabecaListaAtendimentos->resumo);
    } else {
        // Aloca um novo nó para o atendimento.
        Atendimento* novoAtendimento = (Atendimento*)malloc(sizeof(Atendimento));
        if (novoAtendimento == NULL) {
            printf("ERRO DE ALOCAÇÃO (Novo Nó de Atendimento)\n");
            return 1;
        }
        // Copia os dados da pessoa da fila e do atendimento.
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
        novoAtendimento->prox = NULL;

        // Encontra o fim da lista de atendimentos para adicionar o novo.
        Atendimento* atualAtendimento = cabecaListaAtendimentos;
        while (atualAtendimento->prox != NULL) {
            atualAtendimento = atualAtendimento->prox;
        }
        atualAtendimento->prox = novoAtendimento;
        
        //chama a função do historico.c
        adicionarAtendimento(h, novoAtendimento->nome, novoAtendimento->CPF, 
                     novoAtendimento->psicologo, novoAtendimento->curso, 
                     novoAtendimento->resumo);
    }
 // Remove a pessoa da Fila.
    // Se era a única pessoa na fila (dados estavam no nó cabeça).
    if (fila->proximo == fila) {
        fila->nome[0] = '\0'; // Marca o nó cabeça como "vazio".
        fila->CPF[0] = '\0';
        fila->curso[0] = '\0';
    } else {
        // Se há mais de uma pessoa, os dados do próximo nó são copiados para o nó cabeça.
        Fila* proximoNoFila = fila->proximo;
        
        strncpy(fila->nome, proximoNoFila->nome, 99);
        fila->nome[99] = '\0';
        strncpy(fila->CPF, proximoNoFila->CPF, 14);
        fila->CPF[14] = '\0';
        strncpy(fila->curso, proximoNoFila->curso, 49);
        fila->curso[49] = '\0';

        // O nó cabeça agora aponta para o nó seguinte ao que foi "removido".
        fila->proximo = proximoNoFila->proximo;
        free(proximoNoFila); // Libera o nó que continha os dados agora movidos.
    }

    printf("Atendimento registrado e pessoa removida da fila.\n");
    return 0;
}
//Dyego Dasko
// Remove a pessoa da frente da fila (sem registrar atendimento).
int removerDaFila(Fila* fila) {
    if (fila == NULL || fila->nome[0] == '\0') { // Verifica se a fila está vazia
        printf("Fila vazia, nada para remover.\n");
        return 1;
    }

    printf("Removendo da frente da fila: Nome: %s, CPF: %s\n", fila->nome, fila->CPF);

    // Se for o único elemento na fila.
    if (fila->proximo == fila) {
        fila->nome[0] = '\0';   // Marca o nó cabeça como "vazio".
        fila->CPF[0] = '\0';
        fila->curso[0] = '\0';
        printf("Único elemento da fila removido. Fila agora está vazia.\n");
    } else { // Se houver mais de um elemento.
        Fila* proximoNo = fila->proximo;

        // Copia os dados do próximo nó para o nó cabeça.
        strncpy(fila->nome, proximoNo->nome, 99);
        fila->nome[99] = '\0';
        strncpy(fila->CPF, proximoNo->CPF, 14);
        fila->CPF[14] = '\0';
        strncpy(fila->curso, proximoNo->curso, 49);
        fila->curso[49] = '\0';

        // O nó cabeça aponta para o nó seguinte ao que foi "removido".
        fila->proximo = proximoNo->proximo;
        free(proximoNo); // Libera o nó que foi efetivamente removido.
        printf("Primeiro elemento da fila removido com sucesso.\n");
    }
    return 0;
}
//Matheus josé
// Lista todas as pessoas atualmente na fila.
void listarFila(Fila* fila) {
    if (fila == NULL || fila->nome[0] == '\0') { // Verifica se a fila está vazia
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
    } while (atual != fila); // Percorre a fila circular até voltar ao nó cabeça.
}