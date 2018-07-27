//
// Created by Wei on 20/03/2016.
//

#ifndef CPPRECIPES_PAGE_HPP
#define CPPRECIPES_PAGE_HPP

#include <cstring>


namespace PageConfig {
constexpr int BlockSize = 32;
constexpr int NumBlocks = 1024;
constexpr int BlockIsFree = 1;
constexpr int BlockIsNotFree = 0;
constexpr int InvalidBlockIndex = -1;
} // namespace PageConfig


class Page {
public:
  Page()
      : m_pNextPage(nullptr) {
    std::memset(m_free, PageConfig::BlockIsFree, PageConfig::NumBlocks);
  }
  ~Page() {
    if (m_pNextPage) {
      delete m_pNextPage;
      m_pNextPage = nullptr;
    }
  }
  void *alloc() {
    auto index = findFreeBlock();
    if (index != PageConfig::InvalidBlockIndex)
        return allocateBlockByIndex(index);
    return nullptr;
  }
  bool free(void *pMem) {
    if (not inPage(pMem))
      return false;
    return freeBlockByIndex(findBlockIndex(pMem));
  }
  bool isEmpty() const {
    for (int i=0; i<PageConfig::NumBlocks; i++)
      if (!isBlockFree(i))
        return false;
    return true;
  }
private:
  bool inPage(void *pMem) {
    return pMem >= m_memory and pMem <= (m_memory + (PageConfig::NumBlocks - 1) * PageConfig::BlockSize);
  }
  int findBlockIndex(void *pMem) {
    for (int i=0; i<PageConfig::NumBlocks; i++)
      if (pMem >= m_memory + i * PageConfig::BlockSize and pMem <= m_memory + (i + 1) * PageConfig::BlockSize)
        return i;
    return PageConfig::InvalidBlockIndex;
  }
  bool isBlockFree(int index) const {
    if (m_free[index] == PageConfig::BlockIsFree)
      return true;
    return false;
  }
  void *allocateBlockByIndex(int index) {
    m_free[index] = PageConfig::BlockIsNotFree;
    return m_memory + index * PageConfig::BlockSize;
  }
  bool freeBlockByIndex(int index) {
    m_free[index] = PageConfig::BlockIsFree;
    return true;
  }
  int findFreeBlock() const {
    for (int i=0; i<PageConfig::NumBlocks; i++)
      if (isBlockFree(i))
        return i;
    return PageConfig::InvalidBlockIndex;
  }
  char m_memory[PageConfig::BlockSize * PageConfig::NumBlocks]{};
  bool m_free[PageConfig::NumBlocks]{};
  Page *m_pNextPage{nullptr};
};


#endif //CPPRECIPES_PAGE_HPP
