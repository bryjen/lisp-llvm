#include "tokenizer.h"
#include "ast.h"
#include "tokens.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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



/**
 * @brief 
 * @returns 
 */
size_t
read_character_sequence(bool (*predicate)(char), const char *const source_text, size_t source_text_len, size_t start) {
    size_t idx = start;
    while (idx < source_text_len && predicate(source_text[idx])) {
        idx++;
    };
    return idx - start;
}

void
try_tokenize_operator(
    const char *const source_text, 
    size_t source_text_len, 
    size_t idx, 
    size_t *out_len, 
    TokenKind *out_tokenkind) {

    // init default values for out params
    out_len = malloc(sizeof(size_t));
    *out_len = 1;

    out_tokenkind = malloc(sizeof(TokenKind));
    *out_tokenkind = TOKEN_KIND_BAD_TOKEN;


    // try parsing as double symbol first
    if (idx + 1 < source_text_len) {
        if (source_text[idx] == '=' && source_text[idx] == '=') {
            *out_len = 2;
            *out_tokenkind = TOKEN_KIND_EQUALS_EQUALS;
            return;
        }
        else if (source_text[idx] == '!' && source_text[idx] == '=') {
            *out_len = 2;
            *out_tokenkind = TOKEN_KIND_EXCLAMATION_EQUALS;
            return;
        }
        else if (source_text[idx] == '<' && source_text[idx] == '=') {
            *out_len = 2;
            *out_tokenkind = TOKEN_KIND_LESS_EQUAL_THAN;
            return;
        }
        else if (source_text[idx] == '>' && source_text[idx] == '=') {
            *out_len = 2;
            *out_tokenkind = TOKEN_KIND_GREATER_EQUAL_THAN;
            return;
        }
    }

    // then we try parsing as a single symbol
    switch (source_text[idx]) {
        case '(':
            *out_tokenkind = TOKEN_KIND_OPEN_PAREN;
            break;
        case ')':
            *out_tokenkind = TOKEN_KIND_CLOSE_PAREN;
            break;
        case '[':
            *out_tokenkind = TOKEN_KIND_OPEN_BRACKET;
            break;
        case ']':
            *out_tokenkind = TOKEN_KIND_CLOSE_BRACKET;
            break;
        case '{':
            *out_tokenkind = TOKEN_KIND_OPEN_BRACE;
            break;
        case '}':
            *out_tokenkind = TOKEN_KIND_CLOSE_BRACE;
            break;
        case '$':
            *out_tokenkind = TOKEN_KIND_DOLLAR;
            break;
        case '!':
            *out_tokenkind = TOKEN_KIND_EXCLAMATION;
            break;
        case '-':
            *out_tokenkind = TOKEN_KIND_MINUS;
            break;
        case '+':
            *out_tokenkind = TOKEN_KIND_PLUS;
            break;
        case '/':
            *out_tokenkind = TOKEN_KIND_SLASH;
            break;
        case '*':
            *out_tokenkind = TOKEN_KIND_ASTERISK;
            break;
        case '%':
            *out_tokenkind = TOKEN_KIND_PERCENT;
            break;
        case ':':
            *out_tokenkind = TOKEN_KIND_PERCENT;
            break;
        case ';':
            *out_tokenkind = TOKEN_KIND_SEMICOLON;
            break;
        case '"':
            *out_tokenkind = TOKEN_KIND_DOUBLE_QUOTE;
            break;
        case '\'':
            *out_tokenkind = TOKEN_KIND_SLASH;
            break;
        case '.':
            *out_tokenkind = TOKEN_KIND_DOT;
            break;
        case '>':
            *out_tokenkind = TOKEN_KIND_GREATER_THAN;
            break;
        case '<':
            *out_tokenkind = TOKEN_KIND_LESS_THAN;
            break;
        default:
            *out_len = 0;
            break;
    }
}


TokenStream*
tokenize(const char *const source_text) {
    const int default_resize_arr_size = 25;
    Token* resize_arr = malloc(default_resize_arr_size * sizeof(Token));
    size_t num_tokens = 0;
    size_t max_capacity = default_resize_arr_size;

    size_t source_text_len = strlen(source_text);

    size_t idx = 0;
    do {
        size_t token_start = idx;
        size_t trivia_len = read_character_sequence(is_whitespace, source_text, source_text_len, idx);
        idx = token_start + trivia_len;

        size_t actual_token_len = 0;
        TokenKind token_kind = TOKEN_KIND_BAD_TOKEN;  // use this as a default

        if (is_alpha(source_text[idx])) {
            actual_token_len = read_character_sequence(is_alphanumeric, source_text, source_text_len, idx);
            token_kind = TOKEN_KIND_IDENTIFIER;
        } 
        else if (is_numeric(source_text[idx])) {
            actual_token_len = read_character_sequence(is_numeric, source_text, source_text_len, idx);
            token_kind = TOKEN_KIND_NUMERIC;
        }
        else {
            // we treat as if we're parsing a symbol
            size_t* size_ptr = NULL;
            TokenKind* token_kind_ptr = NULL;
            try_tokenize_operator(source_text, source_text_len, idx, size_ptr, token_kind_ptr);

            actual_token_len = *size_ptr;
            token_kind = *token_kind_ptr;

            // safe cause we're guaranteed to be returned something from 'try_tokenize_operator'
            free(size_ptr);
            free(token_kind_ptr);
        }

        idx = idx + actual_token_len;

        Token as_token = {
            .token_kind = token_kind,

            .full_start = token_start,
            .full_length = idx - token_start,

            .start = token_start + trivia_len,
            .length = idx - token_start + trivia_len,

            .line = 0,
            .column = 0,
        };


        printf("%zu\n", idx);

        /*
        char* as_str = token_tostr(&as_token, source_text);
        printf("%s\n", as_str);
        free(as_str);
         */

        if (num_tokens >= max_capacity) {
            double_capacity(&resize_arr, &max_capacity);
        }
    }
    while (idx <= source_text_len);

    TokenStream* ts = malloc(sizeof(TokenStream));
    *ts = (TokenStream){ .source_text = source_text, .tokens = resize_arr, .num_tokens = num_tokens };
    return ts;
}
