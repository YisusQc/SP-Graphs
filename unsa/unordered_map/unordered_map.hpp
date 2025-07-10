#pragma once

#include <cstddef>
//#include "unsa/pair/pair.hpp"
#include "unsa/vector/vector.hpp"
#include "unsa/hash/hash.hpp"

namespace unsa {

template <typename K, typename V, typename Hash = unsa::Hash<K>>
class UnorderedMap {
private:
  using PairType = unsa::Pair<K, V>;
  using BucketType = unsa::Vector<PairType>;

  BucketType* buckets;
  size_t bucketCount;
  size_t itemCount;
  Hash hasher;

  void rehash();

public:
  UnorderedMap(size_t initialBucketCount = 8);
  ~UnorderedMap();

  void insert(const K& key, const V& value);
  V& operator[](const K& key);
  bool get(const K& key, V& value) const;
  bool erase(const K& key);
  bool contains(const K& key) const;
  size_t size() const;
  bool empty() const;
  void clear();
};

}

#include "unordered_map.tpp"
