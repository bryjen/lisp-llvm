#include "tokenizer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


bool
is_whitespace(const char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool
is_alpha(const char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool
is_numeric(const char c) {
    return (c >= '0' && c <= '9');
}

bool
is_alphanumeric(const char c) {
    return is_alpha(c) || is_numeric(c);
}


/** @brief Doubles the capacity of the passed resize array */
void
double_capacity(Token** token_arr, size_t* max_capacity) {
    size_t new_max_capacity = *max_capacity * 2;
    *token_arr = realloc(token_arr, (new_max_capacity * sizeof(Token)));
    *max_capacity = new_max_capacity;
}


TokenStream*
tokenize(const char *const source_text) {
    const int default_resize_arr_size = 25;
    Token* resize_arr = malloc(default_resize_arr_size * sizeof(Token));
    size_t num_tokens = 0;
    size_t max_capacity = default_resize_arr_size;

    size_t idx = 0;
    for (idx; idx < _mbstrlen(source_text); idx++) {

        if (num_tokens >= max_capacity) {
            double_capacity(&resize_arr, &max_capacity);
        }
    }

    TokenStream* ts = malloc(sizeof(TokenStream));
    *ts = (TokenStream){ .source_text = source_text, .tokens = resize_arr, .num_tokens = num_tokens };
    return ts;
}
