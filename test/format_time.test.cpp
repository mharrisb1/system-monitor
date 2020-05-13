#include "format.h"
#include <cassert>

int main() {
    long int seconds = 9756;

    assert(Format::ElapsedTime(seconds) == "02:42:36");
}