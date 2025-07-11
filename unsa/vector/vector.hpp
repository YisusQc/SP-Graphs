#pragma once
#include <cstddef>

namespace unsa {

template <typename T>
class Vector {
private:
  size_t _capacity;
  T* _data;
  size_t _idx;
  void resize(size_t new_capacity);

public:
  Vector(size_t size = 0);
  ~Vector();

  void push_back(const T& data);
  void pop_back();
  void erase(int index);

  T& operator[](size_t idx);
  const T& operator[](size_t idx) const;

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

  bool empty() const;
  size_t size() const;
};

}
#include "vector.tpp"
