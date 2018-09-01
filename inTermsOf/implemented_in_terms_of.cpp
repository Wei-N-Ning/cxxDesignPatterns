
#include <numeric>
#include <vector>
#include <cassert>

/*
 * More Exception P144
 *
 * is-implemented-in-terms-of:
 * can be expressed by either non-public inheritance or by containment/
 * delegation. 
 * this is when writing a class T that is implemented in terms of a 
 * class U, the two main options are to inherit privately from U or 
 * to contain a U member object
 */

// P144
// By coining expressions like has-a, is-a, uses-a, we have developed
// a convenient shorthand for describing many types of code relationship

// is-a: is-substitutable-for-a, LSPm public inheritance, by pointer or
// by reference
// interesting read:
// https://isocpp.org/wiki/faq/value-vs-ref-semantics
template<typename T>
int shoot(const T& g) {
    return g.fire();
}

class Gun {
public:
    virtual int fire() const {
        return 0x1;
    }
};

void is_a() {
    // MP40-is-a-Gun
    class MP40 : public Gun {
    public:
        int fire() const override {
            return 0xA;
        }
    };

    // Nerf is not subclass of Gun but it "shoots like a Gun", hence it
    // is a Gun
    class Nerf {
    public:
        int fire() const {
            return -1;
        }
    };

    // old way of write a function type and define a pointer to it
    int(* shootByRef)(const Gun&) = [](const Gun& g) -> int {
        return g.fire();
    };

    auto shootByPtr = [](const Gun* g) -> int {
        return g->fire();
    };

    Gun gun;
    MP40 mp40;
    Nerf nerf;

    // Note how both ref and ptr can work with virtual data (using the
    // terminology from the above article)
    assert(0x1 == shootByRef(gun));
    assert(0xa == shootByRef(mp40));
    assert(0x1 == shootByPtr(&gun));
    assert(0xa == shootByPtr(&mp40));

    // P144
    // it is important to remember, however, that there are more ways to
    // spell is-a in C++ than are in inheritance
    // is-a can also describe unrelated (by inheritance) classes that
    // support that same interface and can therefore be used
    // interchangeably in templated code that uses that common interface
    //
    // (recall Python and Golang's modelling of interface)
    //
    assert(-1 == shoot(nerf));
}

// P144
// A type T, is-implemented-in-terms-of, another type U if T uses U in
// its implementation in some form
//
// Saying "T uses U in some form"
//
// ... T being an adaptor or proxy or wrapper for U,
// ... T simply using U to implement some details of T's own services
// either T has-a U or T is derived from U non-publicly
void is_implemented_is_terms_of() {

    // T has-a U
    class Turret {
    public:
        explicit Turret(size_t numGuns) : m_guns(numGuns) {}
        int launch() const {
            return std::accumulate(
                m_guns.cbegin(),
                m_guns.cend(),
                0,
                [](int sum, const Gun& g) -> int {
                    return sum + g.fire();
                }
            );
        }
    private:
        std::vector<Gun> m_guns;
    };

    // T is derived from U non-publicly
    class MobileTurret : private Gun {
    public:
        explicit MobileTurret(int rateOfFile)
            : m_rateOfFile(rateOfFile) {}
        int launch() const {
            return m_rateOfFile * fire();
        }
    private:
        int m_rateOfFile;
    };

    assert(0x7 == Turret(0x7).launch());
    assert(0x8 == MobileTurret(0x8).launch());
}

// P145
// .. inheritance is often overused, even by experienced developers.
// A sound rule of software engineering is to minimize coupling.
// If a relationship can be expressed in more than one way, use the
// weakest relationship that is practical.
// Given that inheritance is nearly the strongest relationship we can
// express in C++, second only to friendship, it is only really
// appropriate when there is no equivalent weaker alternative

int main() {
    is_a();
    is_implemented_is_terms_of();
    return 0;
}
