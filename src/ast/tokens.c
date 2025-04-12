#include <stdlib.h>
#include <string.h>

#include "tokens.h"

char* 
substring(const char *str, size_t start, size_t len) {
    size_t str_len = strlen(str);
    if (start >= str_len)
            return "";
    if (start + len > str_len)
            len = str_len - start;
    char *slice = malloc(len + 1);
    if (slice == NULL)
            return NULL;
    memcpy(slice, str + start, len);
    slice[len] = '\0';
    return slice;
}


char* 
token_tostr(const Token *const token, const char *const source_text) {
    return substring(source_text, token->start, token->length);
}
