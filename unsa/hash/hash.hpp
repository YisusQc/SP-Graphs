#pragma once

namespace unsa {

template <typename K>
class Hash {
public:
  size_t operator()(const K& key) const {
    return static_cast<size_t>(key);
  }
};

}