#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Historico* inicializarLista() {
    Historico* lista = (Historico*) malloc(sizeof(Historico));
    if (lista == NULL) {
        return NULL; 
    }

    lista->proximo = NULL;

    return lista;
}
