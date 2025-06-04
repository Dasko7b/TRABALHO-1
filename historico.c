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
