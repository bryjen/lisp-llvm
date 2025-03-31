#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ast.h"

typedef struct {
    char*** errors;
    size_t error_count;
} ParseErrors;

typedef struct {
    Expr** exprs;
    size_t exprs_count;
} ParseResults;


/**
 * @brief
 * @param source_text
 * @return
 */
ParseResults*
try_parse(const char *const source_text, ParseErrors** out_parse_errors);


#ifdef __cplusplus
}
#endif

#endif
