#include "gtest/gtest.h"
#include <cassert>
#include "../include/format.h"

TEST(ExampleTests, FormatTime) {
    std::string result = Format::ElapsedTime(83552);
    assert(result == "23:12:32");
}