#include "gtest/gtest.h"
#include "../include/format.h"

TEST(ExampleTests, FormatTime) {
    std::string result = Format::ElapsedTime(83552);
    EXPECT_EQ("23:12:32", result);
}