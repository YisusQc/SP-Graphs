#include <cstddef>
#include <stdexcept>
#include <utility>
#include <iostream>
namespace unsa {

template <typename T>
vector<T>::vector(size_t size) : _capacity(size), _data(new T[size]), _idx(0) {}

template <typename T>
vector<T>::~vector() {
  delete[] _data;
}

template <typename T>
void vector<T>::resize(size_t new_capacity) {
    //Caso 1: Sobra
    if (new_capacity <= _capacity) { 
        for (size_t i = new_capacity; i < _idx; ++i) {
            _data[i].~T();
        }
        _idx = new_capacity;
        return;
    }

    //Caso 2: Falta
    T* temp = new T[new_capacity];
    for (size_t i = 0; i < _idx; ++i) {
        temp[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data     = temp;
    _capacity = new_capacity;
}

template <typename T>
void vector<T>::push_back(const T& value) {
  if (_idx >= _capacity) {
    resize((_capacity == 0) ? 1 : _capacity * 2);
  }
  _data[_idx++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (_idx == 0) return;
  --_idx;
}

template <typename T>
void vector<T>::erase(int index) {
  if (index < 0 || static_cast<size_t>(index) >= _idx) return;
  for (size_t i = index; i < _idx - 1; ++i) {
    _data[i] = std::move(_data[i + 1]);
  }
  --_idx;
}

template <typename T>
T& vector<T>::operator[](size_t idx) {
  if (idx >= _idx) throw std::out_of_range("Index out of range");
  return _data[idx];
}

template <typename T>
const T& vector<T>::operator[](size_t idx) const {
  if (idx >= _idx) throw std::out_of_range("Index out of range");
  return _data[idx];
}

template <typename T>
T* vector<T>::begin() { return _data; }

template <typename T>
T* vector<T>::end() { return _data + _idx; }

template <typename T>
const T* vector<T>::begin() const { return _data; }

template <typename T>
const T* vector<T>::end() const { return _data + _idx; }

template <typename T>
bool vector<T>::empty() const { return _idx == 0; }

template <typename T>
size_t vector<T>::size() const { return _idx; }

template <typename T>
void vector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= _capacity)
        return;
    T* temp = new T[new_capacity];
    for (size_t i = 0; i < _idx; ++i) {
        temp[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = temp;
    _capacity = new_capacity;
}

template <typename T>
void vector<T>::clear() {
    // Destruimos los elementos actuales (opcional: llamar a destructor si fuese necesario)
    for (size_t i = 0; i < _idx; ++i) {
        _data[i].~T();
    }
    _idx = 0;
}

template <typename T>
void vector<T>::swap(vector& other) noexcept {
    using std::swap;
    swap(_data,    other._data);
    swap(_capacity, other._capacity);
    swap(_idx,      other._idx);
}

template<typename T>
void vector<T>::print(){
  for(size_t i=0;i<this->size();i++){
    std::cout<<_data[i]<<" ";
  }
  std::cout<<"\n";
}

}
