#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct Atendimento{

    char psicologo[100];
    char data[10];
    char resumo[500];

} Atendimento;


typedef struct Historico {

    Atendimento atendimento; 
    struct Historico* proximo; 
    int tamanhoHistorico;
    
} Historico; 

Historico* inicializarLista();
Historico* inserirNoHistorico(Historico* h, Atendimento novoAtendimento);
void HistoricoPorCurso(Historico* h);//printa o historico por curso
void HistoricoAtendimentoCPF(Historico* h);//Printa historico por cpf

#endif
