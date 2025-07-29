#pragma once
#include "../pair/pair.hpp"

namespace unsa {
template <typename K, typename V>
class map;
template <typename K, typename V>
class map_iterator {
public:
    using value_type = pair<K, V>;
    using pointer = pair<K, V>*;
    using reference = pair<K, V>&;

    map_iterator() : ptr(nullptr) {}
    explicit map_iterator(pointer p) : ptr(p) {}

    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }

    map_iterator& operator++() {
        ++ptr;
        return *this;
    }

    map_iterator operator++(int) {
        map_iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const map_iterator& other) const {
        return ptr == other.ptr;
    }

    bool operator!=(const map_iterator& other) const {
        return ptr != other.ptr;
    }

private:
    pointer ptr;

    // Permitir que map acceda a este iterador
    friend class map<K, V>;
};


template <typename K, typename V>
class map_const_iterator {
public:
    using value_type = const pair<K, V>;
    using pointer = const pair<K, V>*;
    using reference = const pair<K, V>&;

    map_const_iterator() : ptr(nullptr) {}
    explicit map_const_iterator(pointer p) : ptr(p) {}

    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }

    map_const_iterator& operator++() {
        ++ptr;
        return *this;
    }

    map_const_iterator operator++(int) {
        map_const_iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const map_const_iterator& other) const {
        return ptr == other.ptr;
    }

    bool operator!=(const map_const_iterator& other) const {
        return ptr != other.ptr;
    }

private:
    pointer ptr;

    friend class map<K, V>;
};

}  // namespace unsa

