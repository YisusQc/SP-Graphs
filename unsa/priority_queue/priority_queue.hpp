#include "../vector/vector.hpp"

namespace unsa {
template <typename T, typename Compare>
class PriorityQueue {
private:
  unsa::Vector<T> heap;
  Compare cmp;
  void sift_up(int idx);
  void sift_down(int idx);
public:
  PriorityQueue();
  void push(const T& value);
  void pop();
  T& top();
  bool empty() const;
  int size() const;
};
}
#include "priority_queue.tpp"
