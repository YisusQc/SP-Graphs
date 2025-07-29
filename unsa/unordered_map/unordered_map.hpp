#pragma once
#include "../vector/vector.hpp"
#include "../pair/pair.hpp"
#include "../hash/hash.hpp"

namespace unsa {

template <typename Key, typename T, typename Hash = hash<Key>>
class unordered_map {
private:
    static constexpr std::size_t default_bucket_count = 16;

    struct Entry {
        pair<Key, T> data;
        Entry* next;
        Entry(const Key& key, const T& value) : data(key, value), next(nullptr) {}
    };

    vector<Entry*> buckets;
    std::size_t count;
    Hash hasher;

public:
    unordered_map();
    ~unordered_map();

    class iterator {
    private:
        unordered_map* map;
        std::size_t bucket_index;
        Entry* node;

        void advance();

    public:
        iterator(unordered_map* map, std::size_t index, Entry* node);
        pair<Key, T>& operator*() const;
        pair<Key, T>* operator->() const;
        iterator& operator++();
        bool operator!=(const iterator& other) const;
        bool operator==(const iterator& other) const;
    };

    using const_iterator = const iterator;

    T& operator[](const Key& key);
    T& at(const Key& key);
    const T& at(const Key& key) const;

    std::size_t size() const;
    bool empty() const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    iterator find(const Key& key);
    const_iterator find(const Key& key) const;

    void insert(const pair<Key, T>& value);
    void erase(const Key& key);
    bool contains(const Key& key) const;
    void clear();
};

}  // namespace unsa

#include "unordered_map.tpp"

