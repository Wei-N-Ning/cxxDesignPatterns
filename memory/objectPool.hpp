//
// Created by Wei on 27/03/2016.
//

#ifndef CPPRECIPES_OBJECTPOOL_HPP
#define CPPRECIPES_OBJECTPOOL_HPP

#include <string>
#include <vector>


namespace AssetConstants {
constexpr int InvalidId = -1;
}


/*
 * manages a pool of objects
 */
class ObjectPool {
  friend class AssetFactory;
public:
  bool isFull() const {
    return m_pool.size() == m_pool.capacity();
  }
  int index(void *pObject) {
    for (int idx=0; idx < m_pool.capacity(); idx++)
      if (m_pool[idx] == pObject)
        return idx;
    return AssetConstants::InvalidId;
  }
  int add(void *pObject) {
    if (not isFull()) {
      for (int idx = 0; idx < m_pool.capacity(); idx++)
        if (not m_pool[idx]) {
          m_pool.emplace(m_pool.begin()+idx, pObject);
          return idx;
        }
    }
    return AssetConstants::InvalidId;
  }
  void *takeOne(int index) {
    auto one = m_pool.at(index);
    m_pool.emplace(m_pool.begin() + index, nullptr);
    return one;
  }
  int size() {
    return m_pool.size();
  }
private:
  ObjectPool() {
    initializePool(4);
  }
  ObjectPool(unsigned int poolSize) {
    initializePool(poolSize);
  }
  void initializePool(unsigned int poolSize) {
    m_pool.reserve(poolSize);
    flush();
  }
  void flush() {
    for (int idx=0; idx != m_pool.capacity(); idx++)
      m_pool[idx] = nullptr;
  }
  using Pool = std::vector<void *>;
  Pool m_pool;
};


/*
 * an asset describe a real world asset; it has a name, a resource location and an automatically issued id
 */
class Asset {
  friend class AssetFactory;
public:
  std::string name() const {
    return m_name;
  }
  std::string path() const {
    return m_path;
  }
  int id() const {
    return m_id;
  }
private:
  Asset()
      : Asset::Asset(std::string{}, std::string{}) {
  }
  Asset(std::string name, std::string path)
      : m_name(name), m_path(path) {
  }
  void setId(int id) {
    m_id = id;
  }
  std::string m_name{};
  std::string m_path{};
  int m_id{AssetConstants::InvalidId};
};


class AssetFactory {
public:
  AssetFactory()
      : m_objectPool(ObjectPool{4}) {
  }
  Asset *create(std::string name, std::string path) {
    if (m_objectPool.isFull())
      return nullptr;
    Asset *pAsset{new Asset{name, path}};
    auto index = m_objectPool.add(pAsset);
    pAsset->setId(index);
    return pAsset;
  }
  bool del(Asset *pAsset) {
    auto index = m_objectPool.index(pAsset);
    if (index == AssetConstants::InvalidId)
      return false;
    m_objectPool.takeOne(index);
    delete pAsset;
    return true;
  }
private:
  ObjectPool m_objectPool;
};


#endif //CPPRECIPES_OBJECTPOOL_HPP
