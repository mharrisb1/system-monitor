#pragma once

template<typename T>
class Test {
public:
    Test(T test, T check) :
    test_(test),
    check_(check) {}

    T TestValue() {return test_;}
    T CheckValue() {return check_;}
    bool Pass() {return test_ == check_;}

private:
    T test_;
    T check_;
};