#ifndef UNSA_VECTOR_TPP
#define UNSA_VECTOR_TPP

#include <new>
#include <stdexcept>
namespace unsa {

template <typename T>
vector<T>::vector() : data(nullptr), _size(0), _capacity(0) {}

template <typename T>
vector<T>::vector(std::size_t n) : data(new T[n]()), _size(n), _capacity(n){}
template <typename T>
vector<T>::vector(std::initializer_list<T> init)
    : data(new T[init.size()]), _size(init.size()), _capacity(init.size()) {
    std::size_t i = 0;
    for (const T& val : init) data[i++] = val;
}

template <typename T>
vector<T>::vector(const vector& other)
    : data(new T[other._capacity]), _size(other._size), _capacity(other._capacity) {
    for (std::size_t i = 0; i < _size; ++i)
        data[i] = other.data[i];
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this != &other) {
        delete[] data;
        _capacity = other._capacity;
        _size = other._size;
        data = new T[_capacity];
        for (std::size_t i = 0; i < _size; ++i)
            data[i] = other.data[i];
    }
    return *this;
}

template <typename T>
vector<T>::~vector() {
    delete[] data;
}

template <typename T>
void vector<T>::reallocate(std::size_t new_capacity) {
    T* newData = new T[new_capacity];
    for (std::size_t i = 0; i < _size; ++i)
        newData[i] = std::move(data[i]);
    delete[] data;
    data = newData;
    _capacity = new_capacity;
}
template <typename T>
void vector<T>::pop_back() {
    if (_size == 0) throw std::out_of_range("pop_back() called on empty vector");
    --_size;
}
template <typename T>
void vector<T>::push_back(const T& value) {
    if (_size >= _capacity)
        reallocate(_capacity == 0 ? 1 : _capacity * 2);
    data[_size++] = std::move(value);
}

template <typename T>
void vector<T>::emplace_back(T&& value) {
    if (_size >= _capacity)
        reallocate(_capacity == 0 ? 1 : _capacity * 2);
    data[_size++] = value;
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args&&... args) {
    if (_size >= _capacity)
        reallocate(_capacity == 0 ? 1 : _capacity * 2);
    data[_size++] = T(std::forward<Args>(args)...);
}

template <typename T>
void vector<T>::clear() {
    _size = 0;
}

template <typename T>
bool vector<T>::empty() const {
    return _size == 0;
}

template <typename T>
std::size_t vector<T>::size() const {
    return _size;
}

template <typename T>
T& vector<T>::operator[](std::size_t index) {
    if (index >= _size) throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
const T& vector<T>::operator[](std::size_t index) const {
    if (index >= _size) throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
T* vector<T>::begin() {
    return data;
}

template <typename T>
T* vector<T>::end() {
    return data + _size;
}

template <typename T>
const T* vector<T>::begin() const {
    return data;
}

template <typename T>
const T* vector<T>::end() const {
    return data + _size;
}

template <typename T>
T& vector<T>::front() {
    if (_size == 0) throw std::out_of_range("front() called on empty vector");
    return data[0];
}

template <typename T>
const T& vector<T>::front() const {
    if (_size == 0) throw std::out_of_range("front() called on empty vector");
    return data[0];
}

template <typename T>
T& vector<T>::back() {
    if (_size == 0) throw std::out_of_range("back() called on empty vector");
    return data[_size - 1];
}

template <typename T>
const T& vector<T>::back() const {
    if (_size == 0) throw std::out_of_range("back() called on empty vector");
    return data[_size - 1];
}

} // namespace unsa

#endif // UNSA_VECTOR_TPP

