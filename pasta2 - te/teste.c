#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "historico.h"

void limparBuffer() {
    while (getchar() != '\n');
}

void menuPrincipal() {
    printf("\n===== SISTEMA DE ATENDIMENTO PSICOLÓGICO =====\n");
    printf("1. Registrar chegada de paciente\n");
    printf("2. Realizar atendimento\n");
    printf("3. Listar fila de espera\n");
    printf("4. Listar todos os atendimentos\n");
    printf("5. Listar atendimentos por CPF\n");
    printf("6. Listar atendimentos por curso\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    // Inicializa estruturas
    Fila fila;
    iniciarFila(&fila);
    
    Atendimento listaAtendimentos;
    inicarAtendimentos(&listaAtendimentos);
    
    Historico historico;
    inicializarHistorico(&historico);
    
    int opcao;
    char nome[100], cpf[15], curso[50];
    char psicologo[100], data[11], resumo[500];
    
    do {
        menuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1: // Registrar chegada
                printf("\nNome do paciente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                printf("CPF: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                
                printf("Curso: ");
                fgets(curso, sizeof(curso), stdin);
                curso[strcspn(curso, "\n")] = '\0';
                
                regitrarChegada(&fila, nome, cpf, curso);
                printf("Paciente registrado na fila!\n");
                break;
                
            case 2: // Realizar atendimento
                if (fila.nome[0] == '\0') {
                    printf("Fila vazia!\n");
                    break;
                }
                
                printf("\nAtendendo: %s\n", fila.nome);
                printf("Psicólogo: ");
                fgets(psicologo, sizeof(psicologo), stdin);
                psicologo[strcspn(psicologo, "\n")] = '\0';
                
                printf("Data (DD/MM/AAAA): ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                
                printf("Resumo: ");
                fgets(resumo, sizeof(resumo), stdin);
                resumo[strcspn(resumo, "\n")] = '\0';
                
                realizarAtendimento(&fila, &historico, &listaAtendimentos , psicologo, data, resumo);
                break;
                
            case 3: // Listar fila
                printf("\n--- Fila de Espera ---\n");
                listarFila(&fila);
                break;
                
            case 4: // Listar todos atendimentos
                printf("\n--- Histórico Completo de Atendimentos ---\n");
                listarTodosAtendimentos(&historico);
                break;
                
            case 5: // Listar por CPF
                printf("\nCPF para pesquisa: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                listarAtendimentosPorCPF(&historico, cpf);
                break;
                
            case 6: // Listar por curso
                printf("\nCurso para pesquisa: ");
                fgets(curso, sizeof(curso), stdin);
                curso[strcspn(curso, "\n")] = '\0';
                listarAtendimentosPorCurso(&historico, curso);
                break;
                
            case 0:
                printf("Encerrando sistema...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
    
    // Libera memória
    destruirHistorico(&historico);
    
    return 0;
}