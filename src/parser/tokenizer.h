#ifndef TOKENIZER_H
#define TOKENIZER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tokens.h"

/**
 * @brief
 * @param source_text
 * @return
 */
TokenStream*
tokenize(const char *source_text);


#ifdef __cplusplus
}
#endif

#endif
