#pragma once
#include <cstddef>

namespace unsa {

template <typename T>
Vector<T>::Vector(size_t size) : _capacity(size), _data(new T[size]) {}

template <typename T>
Vector<T>::~Vector() {
  delete[] _data;
}

template <typename T>
void Vector<T>::push_back(T data) {
  if (_idx >= _capacity) {
    size_t new_cap = (_capacity == 0) ? 1 : _capacity * 2;
    T* temp = new T[new_cap];
    for (size_t i = 0; i < _capacity; ++i) {
      temp[i] = _data[i];
    }
    delete[] _data;
    _data = temp;
    _capacity = new_cap;
  }
  _data[_idx++] = data;
}

template <typename T>
void Vector<T>::pop_back() {
  if (_idx > 0) {
    --_idx;
  }
}

template <typename T>
void Vector<T>::erase(int index) {
  if (index < 0 || index >= _idx) return;

  for (int i = index; i < _idx - 1; ++i) {
    _data[i] = _data[i + 1];
  }
  --_idx;

  if (_idx < _capacity / 4 && _capacity > 1) {
    size_t new_cap = _capacity / 2;
    T* temp = new T[new_cap];
    for (size_t i = 0; i < _idx; ++i) {
      temp[i] = _data[i];
    }
    delete[] _data;
    _data = temp;
    _capacity = new_cap;
  }
}

template <typename T>
T* Vector<T>::begin() {
  return _data;
}

template <typename T>
T* Vector<T>::end() {
  return _data + _idx;
}

template <typename T>
bool Vector<T>::empty() const {
  return _idx == 0;
}

}
