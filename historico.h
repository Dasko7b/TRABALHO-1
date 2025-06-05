#ifndef HISTORICO_ATENDIMENTO_H
#define HISTORICO_ATENDIMENTO_H

#define MAX_NOME 100
#define MAX_CPF 15
#define MAX_CURSO 100
#define MAX_PSI 100
#define MAX_DESC 300
#define INICIAL 10

typedef struct {
    char nomePaciente[MAX_NOME];
    char cpf[MAX_CPF];
    char psicologo[MAX_PSI];
    char cursoPaciente[MAX_CURSO];
    char descricao[MAX_DESC];
} AtendimentoHistorico;

typedef struct Historico{
    AtendimentoHistorico* atendimentos;
    int capacidade;
    int totalAtendimentos;
} Historico;

// Protótipos
void inicializarHistorico(Historico* h);
void destruirHistorico(Historico* h);
void adicionarAtendimento(Historico* h, char* nomePaciente, char* cpf, char* psicologo, char* cursoPaciente, char* descricao);
void listarTodosAtendimentos(Historico* h);
void listarAtendimentosPorCPF(Historico* h, char* cpf);
void listarAtendimentosPorCurso(Historico* h, char* curso);

#endif
