#pragma once
#include <stdexcept>
#include <new>

namespace unsa {

template <typename K, typename V>
map<K, V>::map() : data(nullptr), _size(0), _capacity(0) {}

template <typename K, typename V>
map<K, V>::~map() {
    delete[] data;
}

template <typename K, typename V>
void map<K, V>::resize() {
    std::size_t new_capacity = (_capacity == 0) ? 4 : _capacity * 2;
    auto* new_data = new pair<K, V>[new_capacity];

    for (std::size_t i = 0; i < _size; ++i)
        new_data[i] = data[i];

    delete[] data;
    data = new_data;
    _capacity = new_capacity;
}

template <typename K, typename V>
void map<K, V>::insert(const K& key, const V& value) {
    for (std::size_t i = 0; i < _size; ++i) {
        if (data[i].first == key) {
            data[i].second = value;
            return;
        }
    }

    if (_size == _capacity) resize();
    data[_size++] = pair<K, V>(key, value);
}

template <typename K, typename V>
V& map<K, V>::operator[](const K& key) {
    for (std::size_t i = 0; i < _size; ++i) {
        if (data[i].first == key)
            return data[i].second;
    }

    if (_size == _capacity) resize();
    data[_size++] = pair<K, V>(key, V{});
    return data[_size - 1].second;
}

template <typename K, typename V>
bool map<K, V>::get(const K& key, V& value) const {
    for (std::size_t i = 0; i < _size; ++i) {
        if (data[i].first == key) {
            value = data[i].second;
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
bool map<K, V>::erase(const K& key) {
    for (std::size_t i = 0; i < _size; ++i) {
        if (data[i].first == key) {
            for (std::size_t j = i; j < _size - 1; ++j)
                data[j] = data[j + 1];
            --_size;
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
int map<K, V>::size() const {
    return _size;
}

template <typename K, typename V>
bool map<K, V>::empty() const {
    return _size == 0;
}

template <typename K, typename V>
void map<K, V>::clear() {
    _size = 0;
}

template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::begin() {
    return iterator(data);
}

template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::end() {
    return iterator(data + _size);
}

template <typename K, typename V>
typename map<K, V>::const_iterator map<K, V>::begin() const {
    return const_iterator(data);
}

template <typename K, typename V>
typename map<K, V>::const_iterator map<K, V>::end() const {
    return const_iterator(data + _size);
}

template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::find(const K& key) {
    for (std::size_t i = 0; i < _size; ++i) {
        if (data[i].first == key)
            return iterator(data + i);
    }
    return end();
}

template <typename K, typename V>
typename map<K, V>::const_iterator map<K, V>::find(const K& key) const {
    for (std::size_t i = 0; i < _size; ++i) {
        if (data[i].first == key)
            return const_iterator(data + i);
    }
    return end();
}

}  // namespace unsa

