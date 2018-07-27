//
// Created by Wei on 16/03/2016.
//

#include "smartPointer.hpp"

#include <iostream>
#include <cassert>

using SPInt = classDesign::SmartPointer<int>;

void RunTinyTests();

void test_DefaultConstructorExpectNull() {
    SPInt spInt{};
    assert(! spInt);
}

void test_ConstructWithValueExpectNotNull() {
    SPInt spInt(new int{10});
    assert(spInt);
}

void test_CopyConstructExpectEqual() {
    SPInt spInt1{new int{10}};
    assert(spInt1 == SPInt{spInt1});
}

void test_CopyConstructFromInvalidInstanceExpectEquallyInvalid() {
    SPInt inv1{};
    assert(! SPInt{inv1});
}

void test_RetrieveObjectPointerExpectAddress() {
    SPInt spInt{new int{10}};
    assert(spInt == spInt.get());
}

void test_DereferenceWhenValid() {
    SPInt spInt{new int{10}};
    assert(*spInt == 10);
}

void test_CompareInvalidInstancesExpectEqual() {
    SPInt inv1{};
    SPInt inv2{};
    assert(inv1 == inv2);
}

void test_CompareValidInstanceWithInvalidInstanceExpectNotEqual() {
    SPInt inv{};
    SPInt val{new int{10}};
    assert(inv != val);
}

void test_AssignInvalidInstanceToInvalidInstance() {
    SPInt inv1{};
    SPInt inv2{};
    assert(! (inv1 = inv2));
    assert(! inv1);
}

void test_AssignInvalidInstanceToValidInstance() {
    SPInt val{new int{10}};
    SPInt inv{};
    assert(! (val = inv));
    assert(! val);
}

void test_AssignValidInstanceToInvalidInstance() {
    SPInt val{new int{10}};
    SPInt inv{};
    assert((inv = val));
    assert(inv);
}

void test_AssignValidInstanceToValidInstancePointingToSameResource() {
    SPInt spInt1{new int{10}};
    SPInt spInt2{spInt1};
    spInt1 = spInt2;
}

void test_AssignInstanceToDifferentInstance() {
    SPInt spInt1{new int{10}};
    SPInt spInt2{new int{20}};
    spInt1 = spInt2;
    assert(spInt1 == spInt2);
}

void test_MoveInvalidInstanceToInvalidInstance() {
    SPInt inv{};
    inv = SPInt{};
}

void test_MoveInvalidInstanceToValidInstance() {
    SPInt val{new int{10}};
    val = SPInt{};
    assert(! val);
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}