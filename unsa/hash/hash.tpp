#pragma once

#include <cstdint>
#include "hash.hpp" // Opcional pero recomendable

namespace unsa {

// Hash genérico
template <typename T>
struct hash {
    static_assert(sizeof(T) == 0, "No hay hash definido para este tipo");
};

// Especialización para int
template <>
struct hash<int> {
    std::size_t operator()(int key) const {
        return static_cast<std::size_t>(key * 2654435761U);
    }
};

// Especialización para unsigned int
template <>
struct hash<unsigned int> {
    std::size_t operator()(unsigned int key) const {
        return static_cast<std::size_t>(key * 2654435761U);
    }
};

// Especialización para long long
template <>
struct hash<long long> {
    std::size_t operator()(long long key) const {
        return static_cast<std::size_t>((key ^ (key >> 33)) * 0xff51afd7ed558ccdULL);
    }
};

// Especialización para float
template <>
struct hash<float> {
    std::size_t operator()(float key) const {
        union { float f; uint32_t i; } u = { key };
        return static_cast<std::size_t>(u.i * 2654435761U);
    }
};

// Especialización para double
template <>
struct hash<double> {
    std::size_t operator()(double key) const {
        union { double d; uint64_t i; } u = { key };
        return static_cast<std::size_t>((u.i ^ (u.i >> 33)) * 0xff51afd7ed558ccdULL);
    }
};

// Especialización para unsa::pair
template <typename T1, typename T2>
struct hash<unsa::pair<T1, T2>> {
    std::size_t operator()(const unsa::pair<T1, T2>& p) const {
        std::size_t h1 = hash<T1>{}(p.first);
        std::size_t h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

} // namespace unsa

