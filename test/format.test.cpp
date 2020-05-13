#include "gtest/gtest.h"
#include "../include/format.h"

TEST(ExampleTests, FormatTime) {
    EXPECT_EQ("23:12:32",
              Format::ElapsedTime(83552));
}