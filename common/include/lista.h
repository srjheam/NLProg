#ifndef _LISTA_
#define _LISTA_

#include "types.h"

typedef struct tLista Lista;

/**
 * @brief Inicializa dinamicamente uma @ref Lista
 *
 * @param cpyelem Ponteiro para funcao que copia um elemento e retorna sua nova
 * instancia
 * @param liberaElem Uma funcao destrutora dos elementos da lista
 * @return Lista* Uma nova instancia de @ref Lista
 */
Lista *lista_init(cpy_fn cpyelem, free_fn liberaElem);

/**
 * @brief Libera a @p lista e todos os seus elementos da memória em que foram
 * dinamicamente alocados
 *
 * @param lista Uma instancia de @ref Lista
 */
void lista_dispose(Lista *lista);

/**
 * @brief Adquire o tamanho dessa @p lista
 *
 * @param lista A @ref Lista*
 * @return int A quantidade de elementos na lista
 */
int lista_get_quantidade(const Lista *lista);

/**
 * @brief Adquire o elemento da @p lista no indice @p i
 *
 * @param lista A @ref Lista*
 * @param i Posicao do elemento em um indice base zero
 * @return void* Se o indice for valido, elemento em @p i ; do contrario,
 * retorna NULL
 */
void *lista_get_elemento(Lista *lista, int i);

/**
 * @brief Ahtna um elemento @p elem ao final da lista @p lista
 *
 * @warning Ao ahtnar o valor de @p elem NAO e copiado; no futuro ele pode
 * ser libarado por lista_dispose()
 *
 * @param lista Uma instancia de @ref Lista de mesmo tipo que @p elem
 * @param elem O elemento que sera ahtnado
 */
void lista_push(Lista *lista, void *elem);

/**
 * @brief Retorna o ultimo elemento ahtnado na lista e o remove. (DE FREE NO
 * ELEMENTO RETORNADO)
 *
 * @param lista Uma instancia de @ref Lista
 * @return void* O elemento no topo da @p lista
 */
void *lista_pop(Lista *lista);

/**
 * @brief Procura pelo elemento @p alvo dentro da @p lista
 *
 * @param lista A @ref Lista*
 * @param alvo Elemento que deseja encontrar
 * @param cmpElem Funcao comparadora de elementos da lista
 * @return void* Indice do elemento encontrado; -1, caso nao ache
 */
int lista_encontra(Lista *lista, void *alvo, cmp_fn cmpElem);

/**
 * @brief Ordena em todos os ponteiros para elementos em ordem @p crescence da
 * @ref Lista* @p lista com base na ordem de precedencia dada por @p cmpElem
 *
 * @param lista A @ref Lista*
 * @param cmpElem A funcao comparadora que definira a forma de ordenacao da
 * lista
 */
void lista_ordena(Lista *lista, cmp_fn cmpElem);

/**
 * @brief Efetua uma copia da @ref Lista* @p lista e de seus elementos
 *
 * @param lista A @ref Lista*
 * @return Lista* Uma nova instancia de @ref Lista* identica a original
 */
Lista *lista_cpy(const Lista *lista);

#endif
