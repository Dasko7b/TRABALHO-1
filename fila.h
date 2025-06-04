#ifndef LISTA_H
#define LISTA_H


typedef struct Pessoa
{
    char nome[100];
    char CPF[15];
    char curso[50];
} Pessoa;


typedef struct Fila 
{
    struct Fila* proximo; 
    Pessoa* pessoa;
} Fila; 


typedef struct Atendimento 
{
    Pessoa* pessoa;
    char psicologo[100];
    char data[10];
    char resumo[500];
    struct Atendimento* prox; 
} Atendimento; 


int iniciarFila(Fila *fila);
int inicarAtendimentos(Atendimento* atendimento); 
void regitrarChegada(Fila *fila,char nome[100],char CPF[15],char curso[50]); 
int realizarAtendimento(Fila *fila,char psicologo[100],char data[10],char resumo[500]);
int removerDaFila(Fila *fila);
void listarFila(Fila *fila);

#endif 