#include <cstddef>
#include <stdexcept>
#include <utility>

namespace unsa {

template <typename T>
Vector<T>::Vector(size_t size) : _capacity(size), _data(new T[size]), _idx(0) {}

template <typename T>
Vector<T>::~Vector() {
  delete[] _data;
}

template <typename T>
void Vector<T>::resize(size_t new_capacity) {
  T* temp = new T[new_capacity];
  for (size_t i = 0; i < _idx; ++i) {
    temp[i] = std::move(_data[i]);
  }
  delete[] _data;
  _data = temp;
  _capacity = new_capacity;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
  if (_idx >= _capacity) {
    resize((_capacity == 0) ? 1 : _capacity * 2);
  }
  _data[_idx++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
  if (_idx == 0) return;
  --_idx;
}

template <typename T>
void Vector<T>::erase(int index) {
  if (index < 0 || static_cast<size_t>(index) >= _idx) return;
  for (size_t i = index; i < _idx - 1; ++i) {
    _data[i] = std::move(_data[i + 1]);
  }
  --_idx;
}

template <typename T>
T& Vector<T>::operator[](size_t idx) {
  if (idx >= _idx) throw std::out_of_range("Index out of range");
  return _data[idx];
}

template <typename T>
const T& Vector<T>::operator[](size_t idx) const {
  if (idx >= _idx) throw std::out_of_range("Index out of range");
  return _data[idx];
}

template <typename T>
T* Vector<T>::begin() { return _data; }

template <typename T>
T* Vector<T>::end() { return _data + _idx; }

template <typename T>
const T* Vector<T>::begin() const { return _data; }

template <typename T>
const T* Vector<T>::end() const { return _data + _idx; }

template <typename T>
bool Vector<T>::empty() const { return _idx == 0; }

template <typename T>
size_t Vector<T>::size() const { return _idx; }

}
