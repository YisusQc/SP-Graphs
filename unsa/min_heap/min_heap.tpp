#ifndef UNSA_MIN_HEAP_TPP
#define UNSA_MIN_HEAP_TPP

#include <algorithm>  // std::swap

namespace unsa {

// =================== Constructor ===================

template <typename T>
MinHeap<T>::MinHeap() = default;

// =================== Métodos públicos ===================

template <typename T>
void MinHeap<T>::push(const T& value) {
    data.push_back(value);
    heapify_up(data.size() - 1);
}

template <typename T>
void MinHeap<T>::pop() {
    if (empty())
        throw std::out_of_range("MinHeap::pop: heap vacío");
    data[0] = data.back();
    data.pop_back();
    if (!empty())
        heapify_down(0);
}

template <typename T>
const T& MinHeap<T>::top() const {
    if (empty())
        throw std::out_of_range("MinHeap::top: heap vacío");
    return data.front();
}

template <typename T>
bool MinHeap<T>::empty() const noexcept {
    return data.empty();
}

template <typename T>
typename MinHeap<T>::size_type MinHeap<T>::size() const noexcept {
    return data.size();
}

template <typename T>
void MinHeap<T>::clear() {
    data.clear();
}

// =================== Métodos auxiliares ===================

template <typename T>
void MinHeap<T>::heapify_up(size_type index) {
    while (index > 0) {
        size_type p = parent(index);
        if (data[index] < data[p]) {
            std::swap(data[index], data[p]);
            index = p;
        } else {
            break;
        }
    }
}

template <typename T>
void MinHeap<T>::heapify_down(size_type index) {
    size_type n = data.size();
    while (true) {
        size_type l = left(index);
        size_type r = right(index);
        size_type smallest = index;

        if (l < n && data[l] < data[smallest])
            smallest = l;
        if (r < n && data[r] < data[smallest])
            smallest = r;

        if (smallest != index) {
            std::swap(data[index], data[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

template <typename T>
typename MinHeap<T>::size_type MinHeap<T>::parent(size_type index) const {
    return (index - 1) / 2;
}

template <typename T>
typename MinHeap<T>::size_type MinHeap<T>::left(size_type index) const {
    return 2 * index + 1;
}

template <typename T>
typename MinHeap<T>::size_type MinHeap<T>::right(size_type index) const {
    return 2 * index + 2;
}

} // namespace unsa

#endif // UNSA_MIN_HEAP_TPP
