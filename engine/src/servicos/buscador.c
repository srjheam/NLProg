#include <libgen.h>
#include <stdlib.h>
#include <string.h>

#include "documento.h"
#include "exception.h"
#include "extlib.h"
#include "indice.h"
#include "key_value_pair.h"
#include "palavra.h"
#include "ref_palavra.h"
#include "repo_noticias.h"

#include "buscador.h"

static int cmp_tfidf_listanoticias(const KeyValuePair *x,
                                   const KeyValuePair *y) {
    return *(float *)kvp_get_value(y) * 1e6 - *(float *)kvp_get_value(x) * 1e6;
}

Lista *buscador_buscaNoticias(char *query, HashTable *idxPalavras) {
    // HashTable <string, float>
    HashTable *documentos =
        ht_init((hash_fn)hashStr, (cpy_fn)strdup, (cpy_fn)floatdup,
                (cmp_fn)strcmp, (free_fn)free, (free_fn)free);

    char *saveptr = NULL, *token = NULL;
    int i;
    for (i = 1, token = query;; i++, token = NULL) {
        token = strtok_r(token, " ", &saveptr);
        if (token == NULL)
            break;

        Palavra *pal = ht_get(idxPalavras, token);

        if (pal == NULL)
            continue;

        HashTable *refs_doc = palavra_get_refDocumentos(pal);

        KeyValuePair *curr_refdoc = NULL;
        void *saveptr = NULL;
        while ((curr_refdoc = ht_iter(refs_doc, &saveptr)) != NULL) {
            RefDocumento *refdoc = kvp_get_value(curr_refdoc);
            char *titulo = refdoc_get_documento(refdoc);

            if (ht_get(documentos, titulo) == NULL) {
                float relevancia = 0;
                ht_insert(documentos, titulo, &relevancia);
            }

            float *tfidf_ptr = ht_get(documentos, titulo);
            *tfidf_ptr += refdoc_get_tdIdf(refdoc);
        }
    }

    Lista *lista_noticias = ht_to_list(documentos);

    ht_dispose(documentos);

    lista_ordena(lista_noticias, (cmp_fn)cmp_tfidf_listanoticias);

    return lista_noticias;
}