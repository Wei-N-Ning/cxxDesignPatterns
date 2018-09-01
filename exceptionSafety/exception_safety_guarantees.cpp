/*
 * More Exeption P137
 *
 * Exception Safety
 *
 * basic guarantee: if an exc is thrown, no resources are leaked, and 
 * objects remain in a destructible and usable but not necessarily 
 * predictable state.
 *
 * strong guarantee: if ... program state remains unchanged, this level 
 * always implies commit-or-rollback semantics, including that no 
 * references or iterators into a container be invalidated if an operation 
 * fails
 *
 * nothrow guarantee: will not emit an exception under any circumstances 
 * 
 * P137
 * the canonical form for copy assignment involves two steps.
 * 1) provide a nonthrowing swap()
 * 2) implement operator=() using the "create a temporary and swap" idiom
 * 
 * P139
 * A general technique that works on any class in order to make nearly 
 * strongly exception-safe copy assignment operator: Pimpl Idiom
 * recal C++11 atomic swap operator
 *
 * P143
 * operations on pointers can not throw
 * keep them friendly by wrapping them in manager objects (C++ STL
 * smart pointers) because this guarantees cleanup. This does not 
 * compromise the nothrowing advantages of pointers, because smart 
 * pointer operations never throw either
 *
 */

#include <memory>
#include <cassert>

// refresh my memory on ////defining special member functions////
// Modern Effective C++ Item 17 P111
//
// ////////// (C++98) rule of three ////////////
// ////////// (C++11) rule of five ////////////
//
// if you declare any of a copy ctor, copy =, or dtor, you should
// declare all three; it stems from the class performing some kind
// of resource management,

// C++11 does not generate move operations for a class with a user -
// defined dtor

// emulate the public module
///////////// the header

class Gun {
public:
    Gun();
    Gun(int numBullets);
    ~Gun();
    Gun(Gun &&other) noexcept;
    Gun &operator=(Gun &&other) noexcept;
    Gun(const Gun &other) = delete;
    Gun &operator=(const Gun &other) = delete;

    int fire();

private:
    class GunImpl;
    std::unique_ptr<GunImpl> m_impl = nullptr;
};

///////////// the source
Gun::Gun() {
    m_impl = std::make_unique<GunImpl>();
}
Gun::Gun(int numBullets) {
    m_impl = std::make_unique<GunImpl>(numBullets);
}
Gun::Gun(Gun &&other) noexcept = default;
Gun& Gun::operator=(Gun &&other) noexcept = default;
Gun::~Gun() = default;

// emulate a separate implementation module
class Gun::GunImpl {
public:
    GunImpl() = default;
    GunImpl(int numBullets)
        : m_numBullets(numBullets) {}
    int fire() {
        return m_numBullets;
    }

private:
    int m_numBullets = 1;
};

int Gun::fire() {
    return m_impl->fire();
}

void upgrade(Gun& gun) {
    Gun tmp(10);
    gun = std::move(tmp);
}

int main() {
    Gun g;
    assert(1 == g.fire());

    upgrade(g);
    assert(10 == g.fire());
    return 0;
}
