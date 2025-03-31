#include <gtest/gtest.h>

#include "parser.h"
#include "tokenizer.h"

// Sample function to test
int square(int x) {
    return x * x;
}

bool is_even(int x) {
    return x % 2 == 0;
}

// Test cases
TEST(MathTest, Square) {
    EXPECT_EQ(square(3), 9);
    EXPECT_EQ(square(-4), 16);
    EXPECT_EQ(square(0), 0);
}

TEST(MathTest, IsEven) {
    EXPECT_TRUE(is_even(2));
    EXPECT_TRUE(is_even(0));
    EXPECT_FALSE(is_even(3));
}

TEST(SOMETHING, 1) {
    std::string source_text;
    tokenize(source_text.c_str());
    EXPECT_TRUE(is_even(2));
}
