#pragma once
#include <cstddef>
#include <initializer_list>

namespace unsa {

template <typename T>
class vector {
private:
  size_t _capacity;
  T* _data;
  size_t _idx;


public:
  vector(size_t size = 0);
  vector(std::initializer_list<T> init);//constructor {}
  ~vector();

  void resize(size_t new_capacity);
  void push_back(const T& data);
  void pop_back();
  void erase(int index);
  //emplace_back
  template <typename... Args>
  T& emplace_back(Args&&... args);

  T& operator[](size_t idx);
  const T& operator[](size_t idx) const;

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

  bool empty() const;
  size_t size() const;

  void reserve(size_t new_cap);
  void clear();
  void swap(vector& swapped) noexcept;

  //test functions
  void print();
};

}
#include "vector.tpp"
