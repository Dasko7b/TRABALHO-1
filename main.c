#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "historico.h"

int main() {
    Fila fila;
    Atendimento listaAtendimentos;
    Historico historico;

    // Inicialização
    iniciarFila(&fila);
    inicarAtendimentos(&listaAtendimentos);
    inicializarHistorico(&historico);

    int opcao;
    char nome[100], cpf[15], curso[50], psicologo[100], data[10], resumo[500];

    do {
        printf("\n======= SISTEMA DE PLANTAO PSICOLOGICO =======\n");
        printf("1. Registrar chegada do estudante\n");
        printf("2. Realizar atendimento\n");
        printf("3. Consultar historico por CPF\n");
        printf("4. Cancelar atendimento (remover da fila)\n");
        printf("5. Emitir relatorio de todos os atendimentos\n");
        printf("6. Listar fila de espera\n");
        printf("7. Consultar historico por curso\n");
        printf("8. Consultar historico por psicologo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar o buffer

        switch (opcao) {
            case 1:
                printf("Nome do estudante: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("CPF: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0';

                printf("Curso: ");
                fgets(curso, sizeof(curso), stdin);
                curso[strcspn(curso, "\n")] = '\0';

                regitrarChegada(&fila, nome, cpf, curso);
                break;

            case 2:
                printf("Nome do psicologo: ");
                fgets(psicologo, sizeof(psicologo), stdin);
                psicologo[strcspn(psicologo, "\n")] = '\0';

                printf("Data do atendimento (DD/MM/AAAA): ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';

                printf("Resumo do atendimento: ");
                fgets(resumo, sizeof(resumo), stdin);
                resumo[strcspn(resumo, "\n")] = '\0';

                realizarAtendimento(&fila, &historico, &listaAtendimentos, psicologo, data, resumo);
                break;

            case 3:
                printf("Informe o CPF: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0';

                listarAtendimentosPorCPF(&historico, cpf);
                break;

            case 4:
                removerDaFila(&fila);
                break;

            case 5:
                listarTodosAtendimentos(&historico);
                break;

            case 6:
                listarFila(&fila);
                break;

            case 7:
                printf("Informe o curso: ");
                fgets(curso, sizeof(curso), stdin);
                curso[strcspn(curso, "\n")] = '\0';

                listarAtendimentosPorCurso(&historico, curso);
                break;

            case 8:
                printf("Informe o nome do psicologo: ");
                fgets(psicologo, sizeof(psicologo), stdin);
                psicologo[strcspn(psicologo, "\n")] = '\0';

                listarAtendimentosPorPsicologo(&historico, psicologo);
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opção invalida.\n");
        }

    } while (opcao != 0);

    destruirHistorico(&historico);
    return 0;
}
