#include <cstdlib>

namespace unsa {

inline unordered_set::unordered_set() : capacity(DEFAULT_CAPACITY) {
    buckets = new Node*[capacity];
    for (std::size_t i = 0; i < capacity; ++i)
        buckets[i] = nullptr;
}

inline unordered_set::~unordered_set() {
    clear();
    delete[] buckets;
}

inline void unordered_set::clear() {
    for (std::size_t i = 0; i < capacity; ++i) {
        Node* current = buckets[i];
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
    }
}

inline std::size_t unordered_set::hash(long long value) const {
    return static_cast<std::size_t>(value) % capacity;
}

inline bool unordered_set::insert(long long value) {
    std::size_t idx = hash(value);
    Node* current = buckets[idx];
    while (current) {
        if (current->value == value)
            return false;
        current = current->next;
    }
    Node* newNode = new Node{value, buckets[idx]};
    buckets[idx] = newNode;
    return true;
}

inline bool unordered_set::contains(long long value) const {
    std::size_t idx = hash(value);
    Node* current = buckets[idx];
    while (current) {
        if (current->value == value)
            return true;
        current = current->next;
    }
    return false;
}

} // namespace unsa
