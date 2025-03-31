#ifndef TOKENS_H
#define TOKENS_H
#include <stddef.h>


/**
 * \brief
 */
typedef enum {
    // symbols
    TOKEN_KIND_OPEN_PAREN,
    TOKEN_KIND_CLOSE_PAREN,
    TOKEN_KIND_OPEN_BRACE,
    TOKEN_KIND_CLOSE_BRACE,
    TOKEN_KIND_OPEN_BRACKET,
    TOKEN_KIND_CLOSE_BRACKET,

    TOKEN_KIND_DOLLAR,
    TOKEN_KIND_EXCLAMATION,
    TOKEN_KIND_MINUS,
    TOKEN_KIND_PLUS,
    TOKEN_KIND_SLASH,
    TOKEN_KIND_ASTERISK,
    TOKEN_KIND_PERCENT,
    TOKEN_KIND_EQUALS_EQUALS,
    TOKEN_KIND_EXCLAMATION_EQUALS,
    TOKEN_KIND_LESS_THAN,
    TOKEN_KIND_GREATER_THAN,
    TOKEN_KIND_LESS_EQUAL_THAN,
    TOKEN_KIND_GREATER_EQUAL_THAN,

    TOKEN_KIND_COLON,
    TOKEN_KIND_SEMICOLON,

    TOKEN_KIND_DOUBLE_QUOTE,
    TOKEN_KIND_SINGLE_QUOTE,

    TOKEN_KIND_DOT,
    TOKEN_KIND_EOF,

    // other
    TOKEN_KIND_IDENTIFIER,
    TOKEN_KIND_NUMERIC,
    TOKEN_KIND_STRING_TOKEN,
    TOKEN_KIND_COLON_IDENTIFIER,  // ":something", relevant in clojure

    TOKEN_KIND_NIL_KEYWORD,
    TOKEN_KIND_INT_KEYWORD,
    TOKEN_KIND_INT16_KEYWORD,
    TOKEN_KIND_INT32_KEYWORD,
    TOKEN_KIND_INT64_KEYWORD,
    TOKEN_KIND_FLOAT_KEYWORD,
    TOKEN_KIND_STRING_KEYWORD,

    TOKEN_KIND_DEF_KEYWORD,
} TokenKind;


/**
 * \brief
 */
typedef struct {
    TokenKind token_kind;
    const char* const start_slice;
    size_t start;
    size_t length;
    size_t line;
    size_t column;
} Token;


/**
 * \brief
 */
typedef struct {
    const char* const source_text;
    const Token* const tokens;
    size_t num_tokens;
} TokenStream;



#endif
