
#include "page.hpp"

#include <cassert>

static Page *m_page;

void setUp() {
    m_page = new Page{};
}

void tearDown() {
    delete m_page;
    m_page = nullptr;
}

void RunTinyTests();

void test_CreatePageExpectEmpty() {
    assert(m_page->isEmpty());
}

void test_AllocateExpectValidPointerReturned() {
    auto pNumbers = (int *)m_page->alloc();
    pNumbers[0] = 10;
    assert(pNumbers[0] == 10);
}

void test_AllocateExpectPageNotEmpty() {
    auto pBlock = m_page->alloc();
    assert(! m_page->isEmpty());
}

void test_FreeMemNotInPageExpectFalse() {
    auto pBlock = new int{1};
    assert(! m_page->free(pBlock));
    delete pBlock;
}

void test_FreeMemNotAllocatedExpectFalse() {
    auto pBlock = m_page->alloc();
    auto pNotAllocated = (int *)pBlock + PageConfig::BlockSize * PageConfig::NumBlocks;
    assert(! m_page->free(pNotAllocated));
}

void test_FreeMemInPageExpectTrue() {
    auto pBlock = m_page->alloc();
    assert(m_page->free(pBlock));
}

void test_FreeMemExpectPageEmptyAgain() {
    auto pBlock = m_page->alloc();
    assert(m_page->free(pBlock));
    assert(m_page->isEmpty());
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}