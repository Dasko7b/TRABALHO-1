#include "fila.h"
#ifndef HISTORICO_H
#define HISTORICO_H


typedef struct Historico {

    Atendimento atendimento; 
    struct Historico* proximo; 
    
} Historico; 

Historico* inicializarLista();
Historico* inserirNoHistorico(Historico* h, Atendimento novoAtendimento);
void HistoricoPorCurso(Historico* h);//printa o historico por curso
void HistoricoAtendimentoCPF(Historico* h);//Printa historico por cpf

#endif
