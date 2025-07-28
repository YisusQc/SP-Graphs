#ifndef UNSA_ARRAY_TPP
#define UNSA_ARRAY_TPP

#include <stdexcept>   // std::out_of_range
#include <algorithm>   // std::fill_n, std::swap_ranges

namespace unsa {

// ===== Implementación de métodos de Array<T, N> =====

template <typename T, std::size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
    if (pos >= N) {
        throw std::out_of_range("Array::at: índice fuera de rango");
    }
    return elems[pos];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::const_reference Array<T, N>::at(size_type pos) const {
    if (pos >= N) {
        throw std::out_of_range("Array::at: índice fuera de rango");
    }
    return elems[pos];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) noexcept {
    return elems[pos];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::const_reference Array<T, N>::operator[](size_type pos) const noexcept {
    return elems[pos];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::front() noexcept {
    // Se asume que el array no está vacío
    return elems[0];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::const_reference Array<T, N>::front() const noexcept {
    // Se asume que el array no está vacío
    return elems[0];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::back() noexcept {
    // Se asume que el array no está vacío
    return elems[N - 1];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::const_reference Array<T, N>::back() const noexcept {
    // Se asume que el array no está vacío
    return elems[N - 1];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::pointer Array<T, N>::data() noexcept {
    return elems;
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::const_pointer Array<T, N>::data() const noexcept {
    return elems;
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::iterator Array<T, N>::begin() noexcept {
    return elems;
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::const_iterator Array<T, N>::begin() const noexcept {
    return elems;
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::iterator Array<T, N>::end() noexcept {
    return elems + N;
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::const_iterator Array<T, N>::end() const noexcept {
    return elems + N;
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::size_type Array<T, N>::size() const noexcept {
    return N;
}

template <typename T, std::size_t N>
constexpr bool Array<T, N>::empty() const noexcept {
    return N == 0;
}

template <typename T, std::size_t N>
void Array<T, N>::fill(const T& value) {
    // Rellena todos los elementos con el valor dado
    std::fill_n(elems, N, value);
}

template <typename T, std::size_t N>
void Array<T, N>::swap(Array& other) noexcept(std::is_nothrow_swappable<T>::value) {
    // Intercambia los elementos con otro array del mismo tipo y tamaño
    std::swap_ranges(elems, elems + N, other.elems);
}

// ===== Funciones auxiliares get<I>() =====

template <std::size_t I, typename T, std::size_t N>
constexpr T& get(Array<T, N>& a) noexcept {
    static_assert(I < N, "get: índice fuera de rango");
    return a[I];
}

template <std::size_t I, typename T, std::size_t N>
constexpr const T& get(const Array<T, N>& a) noexcept {
    static_assert(I < N, "get: índice fuera de rango");
    return a[I];
}

} // namespace unsa

#endif // UNSA_ARRAY_TPP
