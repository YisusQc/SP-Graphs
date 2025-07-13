#pragma once
#include <cstddef>

namespace unsa {

template <typename K, typename V, typename Hash>
UnorderedMap<K, V, Hash>::UnorderedMap(size_t initialBucketCount)
  : bucketCount(initialBucketCount), itemCount(0), hasher(Hash()) {
  buckets = new BucketType[bucketCount];
}

template <typename K, typename V, typename Hash>
UnorderedMap<K, V, Hash>::~UnorderedMap() {
  delete[] buckets;
}

template <typename K, typename V, typename Hash>
void UnorderedMap<K, V, Hash>::insert(const K& key, const V& value) {
  size_t idx = hasher(key) % bucketCount;
  for (size_t i = 0; i < buckets[idx].size(); ++i) {
    if (buckets[idx][i].first() == key) {
      buckets[idx][i].second() = value;
      return;
    }
  }
  buckets[idx].push_back(PairType(key, value));
  ++itemCount;

  if (itemCount > bucketCount * 0.75) {
    rehash();
  }
}

template <typename K, typename V, typename Hash>
V& UnorderedMap<K, V, Hash>::operator[](const K& key) {
  size_t idx = hasher(key) % bucketCount;
  for (size_t i = 0; i < buckets[idx].size(); ++i) {
    if (buckets[idx][i].first() == key) {
      return buckets[idx][i].second();
    }
  }
  buckets[idx].push_back(PairType(key, V{}));
  ++itemCount;

  if (itemCount > bucketCount * 0.75) {
    rehash();
  }

  return buckets[idx][buckets[idx].size() - 1].second();
}

template <typename K, typename V, typename Hash>
bool UnorderedMap<K, V, Hash>::get(const K& key, V& value) const {
  size_t idx = hasher(key) % bucketCount;
  for (size_t i = 0; i < buckets[idx].size(); ++i) {
    if (buckets[idx][i].first() == key) {
      value = buckets[idx][i].second();
      return true;
    }
  }
  return false;
}

template <typename K, typename V, typename Hash>
bool UnorderedMap<K, V, Hash>::erase(const K& key) {
  size_t idx = hasher(key) % bucketCount;
  for (size_t i = 0; i < buckets[idx].size(); ++i) {
    if (buckets[idx][i].first() == key) {
      buckets[idx].erase(i);
      --itemCount;
      return true;
    }
  }
  return false;
}

template <typename K, typename V, typename Hash>
bool UnorderedMap<K, V, Hash>::contains(const K& key) const {
  V dummy;
  return get(key, dummy);
}

template <typename K, typename V, typename Hash>
size_t UnorderedMap<K, V, Hash>::size() const {
  return itemCount;
}

template <typename K, typename V, typename Hash>
bool UnorderedMap<K, V, Hash>::empty() const {
  return itemCount == 0;
}

template <typename K, typename V, typename Hash>
void UnorderedMap<K, V, Hash>::clear() {
  delete[] buckets;
  buckets = new BucketType[bucketCount];
  itemCount = 0;
}

template <typename K, typename V, typename Hash>
void UnorderedMap<K, V, Hash>::rehash() {
  size_t newBucketCount = bucketCount * 2;
  BucketType* newBuckets = new BucketType[newBucketCount];

  for (size_t i = 0; i < bucketCount; ++i) {
    for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it) {
      const K& key = it->first();
      const V& value = it->second();
      size_t newIdx = hasher(key) % newBucketCount;
      newBuckets[newIdx].push_back(PairType(key, value));
    }
  }

  delete[] buckets;
  buckets = newBuckets;
  bucketCount = newBucketCount;
}

}