#pragma once
#include <stdexcept>
#include <utility>

namespace unsa {

template <typename T, typename Compare>
PriorityQueue<T, Compare>::PriorityQueue() : heap(), cmp(Compare()) {}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::sift_up(int idx) {
  while (idx > 0) {
    int parent = (idx - 1) / 2;
    if (!cmp(heap[idx], heap[parent])) break;
    std::swap(heap[idx], heap[parent]);
    idx = parent;
  }
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::sift_down(int idx) {
  int n = heap.size();
  while (true) {
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int smallest = idx;

    if (left < n && cmp(heap[left], heap[smallest])) smallest = left;
    if (right < n && cmp(heap[right], heap[smallest])) smallest = right;
    if (smallest == idx) break;

    std::swap(heap[idx], heap[smallest]);
    idx = smallest;
  }
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T& value) {
  heap.push_back(value);
  sift_up(static_cast<int>(heap.size() - 1));
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::pop() {
  if (empty()) throw std::runtime_error("PriorityQueue is empty");
  heap[0] = heap[heap.size() - 1];
  heap.pop_back();
  if (!empty()) sift_down(0);
}

template <typename T, typename Compare>
T& PriorityQueue<T, Compare>::top() {
  if (empty()) throw std::runtime_error("PriorityQueue is empty");
  return heap[0];
}

template <typename T, typename Compare>
bool PriorityQueue<T, Compare>::empty() const {
  return heap.empty();
}

template <typename T, typename Compare>
int PriorityQueue<T, Compare>::size() const {
  return static_cast<int>(heap.size());
}

}
