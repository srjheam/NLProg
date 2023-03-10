/**
 * @file indexador.h
 * @brief Indexa uma serie de noticias de acordo com as instrucoes do train
 * @version 0.1
 * @date 2023-01-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _INDEXADOR_
#define _INDEXADOR_

#include <stdio.h>

#include "indice.h"

HashTable *indexador_criaIdxPalavras(HashTable *idxDocumentos);

Indice *indexador_criaIndice(const char *train);

#endif // _INDEXADOR_
