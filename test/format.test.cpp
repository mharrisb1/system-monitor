#include "gtest/gtest.h"
#include "../include/format.h"

TEST(ExampleTests, FormatTime) {
    EXPECT_EQ("00:12:32",
              Format::ElapsedTime(752));
}