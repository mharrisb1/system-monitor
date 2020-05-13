#include "gtest/gtest.h"
#include "../include/format.h"

TEST(ExampleTests, FormatTime) {
    std::string result{Format::ElapsedTime(752)};
    EXPECT_EQ("00:12:32",
              result);
}