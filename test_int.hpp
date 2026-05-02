#ifndef TEST_INT_HPP_INCLUDED
#define TEST_INT_HPP_INCLUDED

#include <iostream>

class TestInt {
public:
    TestInt(int _n = 0) : n(new int) {
        *n = _n;
        std::cout << "Create : " << *this << std::endl;
    }

    TestInt(const TestInt& other) : n(new int) {
        *n = *other.n;
        std::cout << "Copy : " << *this << " from " << other << std::endl;
    }

    TestInt(TestInt&& other) noexcept : n(other.n) {
        std::cout << "Move : " << *this << " from " << other << std::endl;
        other.n = nullptr;
    }

    virtual ~TestInt() {
        std::cout << "Destruct : " << *this << std::endl;
        delete n;
    }

    friend std::ostream& operator<<(std::ostream& stream, const TestInt& ti) {
        stream << "TestInt (at " << &ti << " n at " << ti.n;
        if (ti.n != nullptr) stream << " = " << *(ti.n);
        stream << ")";
        return stream;
    }

    TestInt& operator=(const TestInt& other) {
        if (this == &other) return *this;
        std::cout << "Copy assign : " << *this << " from " << other << std::endl;
        delete n;
        n = new int;
        *n = *other.n;
        return *this;
    }

    TestInt& operator=(TestInt&& other) noexcept {
        std::cout << "Move assign : " << *this << " from " << other << std::endl;
        std::swap(n, other.n);
        return *this;
    }

private:
    int* n;
};

#endif // TEST_INT_HPP_INCLUDED
