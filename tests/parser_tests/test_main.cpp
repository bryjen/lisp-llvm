#include <gtest/gtest.h>

#include "parser.h"
#include "tokenizer.h"


TEST(SOMETHING, 1) {
    const std::string source_text = "(+ 5 5)";
    tokenize(source_text.c_str());
    EXPECT_TRUE(true);
}
