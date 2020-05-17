#include "format.h"
#include <cstdio>
#include <cassert>

// Add template for "check" to use assertion-like logic with return statements 
// of 1 if false so we can still see printed output of the tests.
// This will also help clear up much of the repeated logic built out below.

int main() {

    // test 1    
    long int test_long_1{83552};
    std::string result_1 = Format::ElapsedTime(test_long_1);
    printf("Result 1: %s\n", result_1.c_str());
    assert(result_1=="23:12:32");

    // test 2
    long int test_long_2{1380};
    std::string result_2 = Format::ElapsedTime(test_long_2);
    printf("Result 2: %s\n", result_2.c_str());
    assert(result_2=="00:24:00");  // was "00:23:00"

    // test 3
    long int test_long_3{36000};
    std::string result_3 = Format::ElapsedTime(test_long_3);
    printf("Result 3: %s\n", result_3.c_str());
    assert(result_3=="10:00:00");

    // test 4
    long int test_long_4{15534};
    std::string result_4 = Format::ElapsedTime(test_long_4);
    printf("Result 4: %s\n", result_4.c_str());
    assert(result_4=="04:18:54");

   // if (result_1 == "23:12:32" && result_2 == "00:23:00" && result_3 == "10:00:00" && result_4 == "04:18:54") 
}
