#pragma once
#include <cstddef>
#include "../pair/pair.hpp"
#include "../map/map_iterator.hpp"

namespace unsa {

template <typename K, typename V>
class map {
private:
    pair<K, V>* data;
    std::size_t _size;
    std::size_t _capacity;

    void resize();

public:
    using iterator = map_iterator<K, V>;
    using const_iterator = map_const_iterator<K, V>;

    map();
    ~map();

    void insert(const K& key, const V& value);
    V& operator[](const K& key);
    bool get(const K& key, V& value) const;
    bool erase(const K& key);
    int size() const;
    bool empty() const;
    void clear();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    iterator find(const K& key);
    const_iterator find(const K& key) const;
};

}  // namespace unsa

#include "map.tpp"

