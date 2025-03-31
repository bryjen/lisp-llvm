#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdint.h>
#include "tokens.h"

// Note that everything in lisp is an expression, hence the following naming scheme.

typedef enum {
    EXPR_LIST,
    EXPR_VECTOR,
    EXPR_MAP,

    EXPR_USER_DEFINED_KEYWORD,  // ex: ':name'

    EXPR_IDENTIFIER,
    EXPR_DEF,

    EXPR_NUMBER,
    EXPR_STRING,
    EXPR_BOOLEAN,
    EXPR_NIL,
} ExprKind;


typedef struct Expr Expr;  // forward declare
typedef struct UserDefinedKeywordExpr UserDefinedKeywordExpr;  // forward declare


/**
 * @brief Represents a list expression.
 * @code
 * (EXPR_1 EXPR_2 ... EXPR_N)
 * @endcode
 */
typedef struct {
    Token* open_paren_token;
    Expr** inner_exprs;
    size_t exprs_count;
    Token* close_paren_token;
} ListExpr;


/**
 * @brief Represents a vector expression.
 * @code
 * [EXPR_1 EXPR_2 ... EXPR_N]
 * @endcode
 */
typedef struct {
    Token* open_bracket_token;
    Expr** inner_exprs;
    size_t exprs_count;
    Token* close_bracket_token;
} VectorExpr;


/**
 * @brief Represents a key value pair. Solely used inside map expressions.
 * @code
 * :key EXPR
 * @endcode
 */
typedef struct {
    UserDefinedKeywordExpr* user_defined_keyword_expr;
    Expr* value;
} MapKV;

/**
 * @brief Represents a map/dictionary expression.
 * @code
 * { :KEY_1 EXPR_1 :KEY_2 EXPR_2 ... :KEY_N EXPR_N }
 * @endcode
 */
typedef struct {
    Token* open_brace_token;
    MapKV** kv_pairs;
    size_t kv_pair_count;
    Token* close_brace_token;
} MapExpr;


/**
 * @brief Represents a user-defined keyword.
 * @remark Based on Clojure keywords: https://clojuredocs.org/clojure.core/keyword
 * @code
 * :KEYWORD_NAME
 * @endcode
 */
struct UserDefinedKeywordExpr {
    Token* colon_token;
    Token* name_token;
};


/**
 * @brief Represents an identifier.
 * @code
 * some_identifier
 * @endcode
 */
typedef struct {
    Token* identifier_expr;
} IdentifierExpr;


/**
 * @brief Represents variable declaration expression.
 * @code
 * def IDENTIFIER_TOKEN EXPR
 * @endcode
 */
typedef struct {
    Token* def_token;
    Token* identifier_token;
    Expr* value;
} DefExpr;


/**
 * @brief Represents a number.
 * @code
 * 52
 * @endcode
 */
typedef struct {
    Token* token;
    int32_t value;
} NumberExpr;


/**
 * @brief Represents a string literal value.
 * @code
 * "some string literal"
 * @endcode
 */
typedef struct {
    Token* token;
    char* value;
} StringExpr;


/**
 * @brief Represents a boolean value.
 * @code
 * false
 * @endcode
 * or
 * @code
 * true
 * @endcode
 */
typedef struct {
    Token* token;
    bool value;
} BooleanExpr;


/**
 * @brief Represents a nil value.
 * @code
 * nil
 * @endcode
 */
typedef struct {
    Token* token;
} NilExpr;


/**
 * @brief Represents a nil value.
 * @code
 * nil
 * @endcode
 */
struct Expr {
    ExprKind kind;

    union {
        ListExpr* list_expr;
        VectorExpr* vector_expr;
        MapExpr* map_expr;
        UserDefinedKeywordExpr* user_defined_keyword_expr;
        IdentifierExpr* identifier_expr;
        // DefExpr* def_expr;
        NumberExpr* number_expr;
        StringExpr* string_expr;
        BooleanExpr* boolean_expr;
        NilExpr* nil_expr;
    };
};




#endif
