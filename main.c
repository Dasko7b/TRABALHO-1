#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h" // Assumes this is the version with embedded Pessoa fields

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
    Atendimento *listaDeAtendimentos = (Atendimento*)malloc(sizeof(Atendimento));
    if (listaDeAtendimentos == NULL) {
        printf("Falha ao alocar memoria para a lista de atendimentos.\n");
        free(minhaFila); // Libera o que foi alocado antes
        return 1;
    }
    // Usa o nome da função do seu .h ("inicarAtendimentos")
    if (inicarAtendimentos(listaDeAtendimentos) != 0) { // Corrected based on your fila.h
        printf("Falha ao iniciar a lista de atendimentos.\n");
        free(minhaFila);
        free(listaDeAtendimentos);
        return 1;
    }

    printf(">>> Testando o sistema de fila de atendimento <<<\n\n");

    // 1. Registrar chegadas
    printf("## Registrando Pessoas na Fila ##\n");
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
    // Passar 'listaDeAtendimentos' como segundo argumento
    realizarAtendimento(minhaFila, listaDeAtendimentos, "Dr. Sim", "04/06/2025", "Primeira sessao, paciente calmo.");
    printf("\nAtendimento 2:\n");
    // Passar 'listaDeAtendimentos' como segundo argumento
    realizarAtendimento(minhaFila, listaDeAtendimentos, "Dra. Terapeuta", "04/06/2025", "Progresso notavel.");
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

    // 6. Remover da fila
    // A função removerDaFila como implementada (baseada na estrutura sem 'Pessoa*')
    // remove o primeiro da fila. A lógica de remover por CPF não está implementada nela.
    // O main.c original parecia implicar uma remoção por CPF, mas a função em si não o fazia
    // com a estrutura anterior, e com a nova estrutura, removeria o da frente.
    // Vamos chamar removerDaFila para remover o da frente (Carla Dias, neste ponto se Ana e Bruno foram atendidos).
    printf("\n## Removendo da Fila (o primeiro elemento) ##\n");
    // O elemento que seria Carla (333...) se tornou o primeiro após os 2 atendimentos.
    // Se a fila está: Carla, Daniel, Eduarda. removerDaFila remove Carla.
    if (minhaFila->nome[0] != '\0') { // Verifica se a fila não está vazia antes de tentar remover
         printf("Removendo o primeiro da fila (era %s)...\n", minhaFila->nome);
         removerDaFila(minhaFila);
    } else {
        printf("Fila já está vazia, nada para remover.\n");
    }
    listarFila(minhaFila);

    // Tentando remover novamente (o próximo da frente)
    // Se a fila era Carla, Daniel, Eduarda; após remover Carla, é Daniel, Eduarda.
    // Esta chamada removerá Daniel.
    printf("\nRemovendo o próximo da fila...\n");
    if (minhaFila->nome[0] != '\0') {
         printf("Removendo o primeiro da fila (era %s)...\n", minhaFila->nome);
         removerDaFila(minhaFila);
    } else {
        printf("Fila já está vazia, nada para remover.\n");
    }
    listarFila(minhaFila);
    printf("----------------------------------------\n");

    // 7. Realizar mais atendimentos até esvaziar (ou tentar)
    printf("\n## Esvaziando a Fila com Atendimentos ##\n");
    int i = 1;
    // O loop abaixo irá parar se a fila estiver vazia (minhaFila->nome[0] == '\0')
    // ou se realizarAtendimento retornar erro (1)
    while(minhaFila->nome[0] != '\0') { // Verifica se o nó cabeça tem dados válidos
        printf("Atendimento Extra %d:\n", i++);
        if (realizarAtendimento(minhaFila, listaDeAtendimentos, "Dr. Plantonista", "05/06/2025", "Atendimento de rotina.") == 1) {
             // Se realizarAtendimento indica que a fila ficou vazia (retornou 1 e minhaFila->nome[0] é '\0' após a chamada)
            if (minhaFila->nome[0] == '\0') {
                 printf("Fila agora esta vazia.\n");
            }
            break; // Sai do loop se houve erro ou a fila esvaziou
        }
        printf("\n");
         if (minhaFila->nome[0] == '\0') { // Checagem extra caso realizarAtendimento esvazie a fila e retorne 0
            printf("Fila esvaziada durante o atendimento.\n");
            break;
        }
    }
    if(minhaFila->nome[0] == '\0' && i == 1) { // Caso a fila já estivesse vazia antes do loop
        printf("Fila já estava vazia antes dos atendimentos extras.\n");
    }
    printf("----------------------------------------\n");

    // 8. Listar fila final (deve estar vazia se tudo correu bem)
    printf("\n## Estado Final da Fila ##\n");
    listarFila(minhaFila);
    printf("----------------------------------------\n");


    // Liberar memória alocada para os nós cabeça.
    // Os nós internos da fila e da lista de atendimentos já devem ter sido liberados
    // pelas funções de remoção e atendimento.
    // Não há mais minhaFila->pessoa ou listaDeAtendimentos->pessoa para liberar separadamente.
    free(minhaFila); // Libera o nó cabeça da fila
    free(listaDeAtendimentos); // Libera o nó cabeça da lista de atendimentos

    // É uma boa prática limpar a lista de atendimentos também,
    // mas não foi pedido e as funções atuais não liberam a lista de atendimentos inteira.
    // Para um programa completo, seria necessário uma função `liberarListaAtendimentos(listaDeAtendimentos);`
    // que percorreria e liberaria cada nó de atendimento alocado dinamicamente (exceto a cabeça que já foi liberada).

    printf("\nTestes concluidos.\n");
    return 0;
}