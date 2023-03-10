#include <stdlib.h>
#include <string.h>

#include "documento.h"
#include "extlib.h"

#include "repo_noticias.h"

Documento *reponoticias_carregaDocumento(FILE *noticia, const char *nome,
                                         const char *classe) {
    char *buffer = NULL;
    size_t len = 0;
    if (getline(&buffer, &len, noticia) == -1) {
        free(buffer);
        return NULL;
    }

    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';

    // HashTable<string, RefPalavra>
    HashTable *refPalavras =
        ht_init((hash_fn)hashStr, (cpy_fn)strdup, (cpy_fn)refpalavra_cpy,
                (cmp_fn)strcmp, (free_fn)free, (free_fn)refpalavra_dispose);

    char *saveptr = NULL, *token = NULL;
    int i;
    for (i = 1, token = buffer;; i++, token = NULL) {
        token = strtok_r(token, " ", &saveptr);
        if (token == NULL)
            break;

        RefPalavra *ref = ht_get(refPalavras, token);
        if (ref == NULL) {
            RefPalavra *ref = refpalavra_init(token, 1);
            ht_insert(refPalavras, token, ref);
            refpalavra_dispose(ref);
        } else
            refpalavra_incrementaFreqPor(ref, 1);
    }
    free(buffer);

    Documento *doc = doc_init(nome, classe, refPalavras);

    ht_dispose(refPalavras);

    return doc;
}
