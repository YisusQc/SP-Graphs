#pragma once
#include <cstddef>

namespace unsa {

template <typename T>
class Vector {
private:
  size_t _capacity;
  T* _data;
  size_t _idx = 0;

public:
  Vector(size_t size = 0);
  ~Vector();

  void push_back(T data);
  void pop_back();
  void erase(int index);

  T* begin();
  T* end();
  bool empty() const;
};

}

#include "vector.tpp"
