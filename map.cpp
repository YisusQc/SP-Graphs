#include "map.hpp"
template <class K, class V> 
Map<K, V>::Map() {
  capacity = 4;
  size = 0;
  keys = new K[capacity];
  values = new V[capacity];
}

template <class K, class V> 
Map<K, V>::~Map() {
  delete[] keys;
  delete[] values;
}

template <class K, class V> 
void Map<K, V>::resize() {
  capacity *= 2;
  K *newKeys = new K[capacity];
  V *newValues = new V[capacity];

  for (int i = 0; i < size; ++i) {
    newKeys[i] = keys[i];
    newValues[i] = values[i];
  }

  delete[] keys;
  delete[] values;

  keys = newKeys;
  values = newValues;
}

template <class K, class V>
void Map<K, V>::insert(const K &key, const V &value) {
  for (int i = 0; i < size; ++i) {
    if (keys[i] == key) {
      values[i] = value;
      return;
    }
  }

  if (size == capacity)
    resize();
  keys[size] = key;
  values[size] = value;
  ++size;
}

template <class K, class V> 
V &Map<K, V>::operator[](const K &key) {
  for (int i = 0; i < size; ++i)
    if (keys[i] == key)
      return values[i];

  if (size == capacity)
    resize();
  keys[size] = key;
  values[size] = V{};
  ++size;
  return values[size - 1];
}

template <class K, class V> 
bool Map<K, V>::get(const K &key, V &value) const {
  for (int i = 0; i < size; ++i) {
    if (keys[i] == key) {
      value = values[i];
      return true;
    }
  }
  return false;
}

template <class K, class V> 
bool Map<K, V>::erase(const K &key) {
  for (int i = 0; i < size; ++i) {
    if (keys[i] == key) {
      keys[i] = keys[size - 1];
      values[i] = values[size - 1];
      --size;
      return true;
    }
  }
  return false;
}

template <class K, class V> 
int Map<K, V>::getSize() const {
  return size;
}

template <class K, class V> 
bool Map<K, V>::isEmpty() const {
  return size == 0;
}

template <class K, class V> 
void Map<K, V>::clear() { 
  size = 0; 
}
