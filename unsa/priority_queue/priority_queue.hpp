#pragma once
#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm> // para std::swap
#include "../vector/vector.hpp"
namespace unsa {

template <typename T>
  void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
  }

template <typename T, typename Container = unsa::vector<T>, typename Compare = std::less<T>>
class priority_queue {
private:
    Container container;
    Compare comp;

    void heapifyUp(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (!comp(container[parent], container[idx])) break;
            unsa::swap(container[parent], container[idx]);
            idx = parent;
        }
    }

    void heapifyDown(size_t idx) {
        size_t size = container.size();
        while (true) {
            size_t left = 2 * idx + 1;
            size_t right = 2 * idx + 2;
            size_t best = idx;

            if (left < size && comp(container[best], container[left])) best = left;
            if (right < size && comp(container[best], container[right])) best = right;

            if (best == idx) break;
            unsa::swap(container[idx], container[best]);
            idx = best;
        }
    }

public:
    priority_queue() : container(), comp() {}

    void push(const T& value) {
        container.push_back(value);
        heapifyUp(container.size() - 1);
    }

    void pop() {
        if (container.empty()) throw std::out_of_range("Empty priority_queue");
        container[0] = container.back();
        container.pop_back();
        heapifyDown(0);
    }

    const T& top() const {
        if (container.empty()) throw std::out_of_range("Empty priority_queue");
        return container.front();
    }

    bool empty() const { return container.empty(); }
    size_t size() const { return container.size(); }
};

} // namespace unsa

