//
// Created by Wei on 16/03/2016.
//

#ifndef CXXUSAGE_CLASSDESIGN_SMARTPOINTER_HPP
#define CXXUSAGE_CLASSDESIGN_SMARTPOINTER_HPP


namespace classDesign {

class ReferenceCounter {
public:
  void increment() { m_count++; }

  void decrement() { m_count--; }

  int count() { return m_count; }

private:
  int m_count{0};
};


template<typename T>
class SmartPointer {
public:
  SmartPointer(T *objectPtr)
      : m_objectPtr(objectPtr),
        m_refCounterPtr(new ReferenceCounter) {
    m_refCounterPtr->increment();
  }

  SmartPointer() = default;

  SmartPointer(const SmartPointer<T> &other)
      : m_objectPtr(other.m_objectPtr),
        m_refCounterPtr(other.m_refCounterPtr) {
    if (m_refCounterPtr)
      m_refCounterPtr->increment();
  }

  ~SmartPointer() {
    if (m_refCounterPtr) {
      m_refCounterPtr->decrement();
      if (!m_refCounterPtr->count())
        free();
    }
  }

  T *get() const { return m_objectPtr; }

  operator bool() const { return bool(this->m_objectPtr); }

  bool operator==(T *objectPtr) const { return this->m_objectPtr == objectPtr; }

  bool operator==(const SmartPointer<T> &other) const {
    return this->m_objectPtr == other.get();
  }

  SmartPointer<T> &operator=(const SmartPointer<T> &other) {
    if (this == &other)
      return *this;
    if (*this) {
      this->m_refCounterPtr->decrement();
      if (!this->m_refCounterPtr->count())
        this->free();
    }
    this->m_objectPtr = other.m_objectPtr;
    this->m_refCounterPtr = other.m_refCounterPtr;
    if (*this)
      this->m_refCounterPtr->increment();
    return *this;
  }

  SmartPointer<T> &operator=(SmartPointer<T> &&other) {
    if (this != &other) {
      this->m_objectPtr = other.m_objectPtr;
      this->m_refCounterPtr = other.m_refCounterPtr;
      other.m_objectPtr = nullptr;
      other.m_refCounterPtr = nullptr;
    }
    return *this;
  }

  T operator*() const { return *m_objectPtr; }

private:
  ReferenceCounter *m_refCounterPtr{nullptr};
  T *m_objectPtr{nullptr};

  void free() {
    delete m_refCounterPtr;
    m_refCounterPtr = nullptr;
    delete m_objectPtr;
    m_objectPtr = nullptr;
  }
};

} // namespace classDesign

#endif //CXXUSAGE_CLASSDESIGN_SMARTPOINTER_HPP
