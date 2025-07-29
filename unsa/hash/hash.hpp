#pragma once
#include <cstdint>
#include "../pair/pair.hpp"
namespace unsa {

template <typename T>
struct hash;

template <>
struct hash<int>;

template <>
struct hash<unsigned int>;

template <>
struct hash<long long>;

template <>
struct hash<float>;

template <>
struct hash<double>;

template <typename T1, typename T2>
struct hash<unsa::pair<T1, T2>>;

} // namespace unsa

#include "hash.tpp"

