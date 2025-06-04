#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h" // Certifique-se que este arquivo está no mesmo diretório ou no include path

int main() {
    // Aloca memória para o nó cabeça da fila
    Fila *minhaFila = (Fila*)malloc(sizeof(Fila));
    if (minhaFila == NULL) {
        printf("Falha ao alocar memoria para a fila.\n");
        return 1;
    }
    // Inicializa a fila (o nó cabeça)
    if (iniciarFila(minhaFila) != 0) {
        printf("Falha ao iniciar a fila.\n");
        free(minhaFila);
        return 1;
    }

    // Aloca memória para o nó cabeça da lista de atendimentos
    // Embora não possamos popular esta lista diretamente com o protótipo atual de realizarAtendimento,
    // a estrutura existe no .h, então vamos inicializá-la.
    Atendimento *listaDeAtendimentos = (Atendimento*)malloc(sizeof(Atendimento));
    if (listaDeAtendimentos == NULL) {
        printf("Falha ao alocar memoria para a lista de atendimentos.\n");
        free(minhaFila); // Libera o que foi alocado antes
        return 1;
    }
    // Usa o nome da função do seu .h ("inicarAtendimentos")
    if (inicarAtendimentos(listaDeAtendimentos) != 0) {
        printf("Falha ao iniciar a lista de atendimentos.\n");
        free(minhaFila);
        free(listaDeAtendimentos);
        return 1;
    }

    printf(">>> Testando o sistema de fila de atendimento <<<\n\n");

    // 1. Registrar chegadas
    printf("## Registrando Pessoas na Fila ##\n");
    // Usa o nome da função do seu .h ("regitrarChegada")
    regitrarChegada(minhaFila, "Ana Silva", "111.111.111-11", "Engenharia");
    regitrarChegada(minhaFila, "Bruno Costa", "222.222.222-22", "Medicina");
    regitrarChegada(minhaFila, "Carla Dias", "333.333.333-33", "Direito");
    regitrarChegada(minhaFila, "Daniel Souza", "444.444.444-44", "Arquitetura");
    printf("----------------------------------------\n");

    // 2. Listar fila
    printf("\n## Estado Atual da Fila ##\n");
    listarFila(minhaFila);
    printf("----------------------------------------\n");

    // 3. Realizar atendimentos
    printf("\n## Realizando Atendimentos ##\n");
    printf("Atendimento 1:\n");
    realizarAtendimento(minhaFila, "Dr. Sim", "04/06/2025", "Primeira sessão, paciente calmo.");
    printf("\nAtendimento 2:\n");
    realizarAtendimento(minhaFila, "Dra. Terapeuta", "04/06/2025", "Progresso notável.");
    printf("----------------------------------------\n");

    // 4. Listar fila novamente
    printf("\n## Estado da Fila Apos Atendimentos ##\n");
    listarFila(minhaFila);
    printf("----------------------------------------\n");

    // 5. Adicionar mais uma pessoa
    printf("\n## Registrando mais uma Pessoa ##\n");
    regitrarChegada(minhaFila, "Eduarda Lima", "555.555.555-55", "Psicologia");
    listarFila(minhaFila);
    printf("----------------------------------------\n");

    // 6. Remover da fila por CPF
    printf("\n## Removendo da Fila por CPF ##\n");
    printf("Removendo CPF: 333.333.333-33 (Carla Dias)...\n");
    removerDaFila(minhaFila);
    listarFila(minhaFila);

    printf("\nTentando remover CPF inexistente: 999.999.999-99...\n");
    removerDaFila(minhaFila);
    listarFila(minhaFila);
    printf("----------------------------------------\n");

    // 7. Realizar mais atendimentos até esvaziar (ou tentar)
    printf("\n## Esvaziando a Fila com Atendimentos ##\n");
    int i = 1;
    // O loop abaixo irá parar se a fila estiver vazia ou se realizarAtendimento retornar erro (1)
    while(minhaFila->pessoa != NULL) {
        printf("Atendimento Extra %d:\n", i++);
        if (realizarAtendimento(minhaFila, "Dr. Plantonista", "04/06/2025", "Atendimento de rotina.") == 1 && minhaFila->pessoa == NULL) {
             // Se realizarAtendimento indica que a fila ficou vazia (retornou 1 e fila->pessoa é NULL)
            printf("Fila agora esta vazia.\n");
            break;
        }
        printf("\n");
    }
    printf("----------------------------------------\n");

    // 8. Listar fila final (deve estar vazia)
    printf("\n## Estado Final da Fila ##\n");
    listarFila(minhaFila);
    printf("----------------------------------------\n");


    // Liberar memória alocada para os nós cabeça.
    // As funções de remoção e atendimento devem ter liberado as Pessoas e os Nós da Fila.
    // Se o nó cabeça 'minhaFila' ainda contiver uma 'Pessoa' (caso a fila não tenha sido totalmente esvaziada),
    // essa 'Pessoa' também deve ser liberada. A lógica de 'realizarAtendimento' e 'removerDaFila'
    // tenta lidar com isso ao setar 'fila->pessoa = NULL'.
    if (minhaFila != NULL && minhaFila->pessoa != NULL) {
        free(minhaFila->pessoa); // Libera a pessoa se o nó cabeça ainda tiver uma
    }
    free(minhaFila); // Libera o nó cabeça da fila

    if (listaDeAtendimentos != NULL && listaDeAtendimentos->pessoa != NULL) {
        free(listaDeAtendimentos->pessoa); // Libera pessoa do nó cabeça de atendimentos, se houver
    }
    free(listaDeAtendimentos); // Libera o nó cabeça da lista de atendimentos

    printf("\nTestes concluidos.\n");
    return 0;
}