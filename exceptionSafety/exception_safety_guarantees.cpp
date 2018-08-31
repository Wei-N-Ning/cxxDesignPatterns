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


int main() {
    return 0;
}
