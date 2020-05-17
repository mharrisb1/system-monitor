#include "format.h"  // Format::ElapsedTime()
#include "testkit/tester.hpp"
#include <cstdio>

int main() {

    /* Test 1
     *
     * INPUT:           83552
     * EXPECTED OUTPUT: 23:12:32
     *
     */
    Test<std::string> test1(Format::ElapsedTime(83552), "23:12:32");
    printf("Test 1: Looking for %s and got %s\n", test1.CheckValue().c_str(), test1.TestValue().c_str());

    /* Test 2
     *
     * INPUT:           1380
     * EXPECTED OUTPUT: 00:23:00
     *
     */
    Test<std::string> test2(Format::ElapsedTime(1380), "00:23:00");
    printf("Test 2: Looking for %s and got %s\n", test2.CheckValue().c_str(), test2.TestValue().c_str());

    /* Test 3
     *
     * INPUT:           36000
     * EXPECTED OUTPUT: 10:00:00
     *
     */
    Test<std::string> test3(Format::ElapsedTime(36000), "10:00:00");
    printf("Test 2: Looking for %s and got %s\n", test3.CheckValue().c_str(), test3.TestValue().c_str());

    /* Test 4
     *
     * INPUT:           15534
     * EXPECTED OUTPUT: 04:18:54
     *
     */
    Test<std::string> test4(Format::ElapsedTime(15534), "04:18:54");
    printf("Test 2: Looking for %s and got %s\n", test4.CheckValue().c_str(), test4.TestValue().c_str());

    if(test1.Pass() && test2.Pass() && test3.Pass() && test4.Pass()) {
       return 0;
    } else {
       return 1;
    }
}
