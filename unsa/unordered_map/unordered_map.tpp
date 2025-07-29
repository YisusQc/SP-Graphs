#pragma once

namespace unsa {

template <typename Key, typename T, typename Hash>
unordered_map<Key, T, Hash>::unordered_map() : buckets(default_bucket_count), count(0), hasher(Hash()) {
    for (std::size_t i = 0; i < default_bucket_count; ++i)
        buckets[i] = nullptr;
}

template <typename Key, typename T, typename Hash>
unordered_map<Key, T, Hash>::~unordered_map() {
    clear();
}

template <typename Key, typename T, typename Hash>
void unordered_map<Key, T, Hash>::clear() {
    for (std::size_t i = 0; i < buckets.size(); ++i) {
        Entry* head = buckets[i];
        while (head) {
            Entry* tmp = head;
            head = head->next;
            delete tmp;
        }
        buckets[i] = nullptr;
    }
    count = 0;
}

template <typename Key, typename T, typename Hash>
std::size_t unordered_map<Key, T, Hash>::size() const {
    return count;
}

template <typename Key, typename T, typename Hash>
bool unordered_map<Key, T, Hash>::empty() const {
    return count == 0;
}

template <typename Key, typename T, typename Hash>
T& unordered_map<Key, T, Hash>::operator[](const Key& key) {
    std::size_t index = hasher(key) % buckets.size();
    Entry* node = buckets[index];

    while (node) {
        if (node->data.first == key) return node->data.second;
        node = node->next;
    }

    Entry* new_node = new Entry(key, T());
    new_node->next = buckets[index];
    buckets[index] = new_node;
    ++count;
    return new_node->data.second;
}

template <typename Key, typename T, typename Hash>
T& unordered_map<Key, T, Hash>::at(const Key& key) {
    auto it = find(key);
    if (it == end()) throw "Key not found";
    return it->second;
}

template <typename Key, typename T, typename Hash>
const T& unordered_map<Key, T, Hash>::at(const Key& key) const {
    auto it = find(key);
    if (it == end()) throw "Key not found";
    return it->second;
}

template <typename Key, typename T, typename Hash>
void unordered_map<Key, T, Hash>::insert(const pair<Key, T>& value) {
    std::size_t index = hasher(value.first) % buckets.size();
    Entry* node = buckets[index];

    while (node) {
        if (node->data.first == value.first) {
            node->data.second = value.second;
            return;
        }
        node = node->next;
    }

    Entry* new_node = new Entry(value.first, value.second);
    new_node->next = buckets[index];
    buckets[index] = new_node;
    ++count;
}

template <typename Key, typename T, typename Hash>
void unordered_map<Key, T, Hash>::erase(const Key& key) {
    std::size_t index = hasher(key) % buckets.size();
    Entry* node = buckets[index];
    Entry* prev = nullptr;

    while (node) {
        if (node->data.first == key) {
            if (prev)
                prev->next = node->next;
            else
                buckets[index] = node->next;

            delete node;
            --count;
            return;
        }
        prev = node;
        node = node->next;
    }
}

template <typename Key, typename T, typename Hash>
bool unordered_map<Key, T, Hash>::contains(const Key& key) const {
    return find(key) != end();
}

template <typename Key, typename T, typename Hash>
typename unordered_map<Key, T, Hash>::iterator unordered_map<Key, T, Hash>::find(const Key& key) {
    std::size_t index = hasher(key) % buckets.size();
    Entry* node = buckets[index];

    while (node) {
        if (node->data.first == key) return iterator(this, index, node);
        node = node->next;
    }

    return end();
}

template <typename Key, typename T, typename Hash>
typename unordered_map<Key, T, Hash>::const_iterator unordered_map<Key, T, Hash>::find(const Key& key) const {
    std::size_t index = hasher(key) % buckets.size();
    Entry* node = buckets[index];

    while (node) {
        if (node->data.first == key) return iterator(const_cast<unordered_map*>(this), index, node);
        node = node->next;
    }

    return end();
}

template <typename Key, typename T, typename Hash>
typename unordered_map<Key, T, Hash>::iterator unordered_map<Key, T, Hash>::begin() {
    for (std::size_t i = 0; i < buckets.size(); ++i) {
        if (buckets[i]) return iterator(this, i, buckets[i]);
    }
    return end();
}

template <typename Key, typename T, typename Hash>
typename unordered_map<Key, T, Hash>::iterator unordered_map<Key, T, Hash>::end() {
    return iterator(this, buckets.size(), nullptr);
}

template <typename Key, typename T, typename Hash>
typename unordered_map<Key, T, Hash>::const_iterator unordered_map<Key, T, Hash>::begin() const {
    return const_cast<unordered_map*>(this)->begin();
}

template <typename Key, typename T, typename Hash>
typename unordered_map<Key, T, Hash>::const_iterator unordered_map<Key, T, Hash>::end() const {
    return const_cast<unordered_map*>(this)->end();
}

// Iterator

template <typename Key, typename T, typename Hash>
unordered_map<Key, T, Hash>::iterator::iterator(unordered_map* m, std::size_t i, Entry* n)
    : map(m), bucket_index(i), node(n) {}

template <typename Key, typename T, typename Hash>
void unordered_map<Key, T, Hash>::iterator::advance() {
    if (node && node->next) {
        node = node->next;
        return;
    }

    ++bucket_index;
    while (bucket_index < map->buckets.size()) {
        if (map->buckets[bucket_index]) {
            node = map->buckets[bucket_index];
            return;
        }
        ++bucket_index;
    }
    node = nullptr;
}

template <typename Key, typename T, typename Hash>
unsa::pair<Key, T>& unordered_map<Key, T, Hash>::iterator::operator*() const {
    return node->data;
}

template <typename Key, typename T, typename Hash>
unsa::pair<Key, T>* unordered_map<Key, T, Hash>::iterator::operator->() const {
    return &node->data;
}

template <typename Key, typename T, typename Hash>
typename unordered_map<Key, T, Hash>::iterator& unordered_map<Key, T, Hash>::iterator::operator++() {
    advance();
    return *this;
}

template <typename Key, typename T, typename Hash>
bool unordered_map<Key, T, Hash>::iterator::operator!=(const iterator& other) const {
    return node != other.node;
}

template <typename Key, typename T, typename Hash>
bool unordered_map<Key, T, Hash>::iterator::operator==(const iterator& other) const {
    return node == other.node;
}

} // namespace unsa

