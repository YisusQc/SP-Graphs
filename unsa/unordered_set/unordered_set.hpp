#pragma once

#include <cstddef>

namespace unsa {

class unordered_set {
public:
    unordered_set();
    ~unordered_set();

    bool insert(long long value);
    bool contains(long long value) const;

private:
    static const std::size_t DEFAULT_CAPACITY = 4096;

    struct Node {
        long long value;
        Node* next;
    };

    Node** buckets;
    std::size_t capacity;

    std::size_t hash(long long value) const;
    void clear();
};

} // namespace unsa

#include "unordered_set.tpp"
