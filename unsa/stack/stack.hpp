#ifndef UNSA_STACK_HPP
#define UNSA_STACK_HPP

#include <vector>
#include <cstddef>  // std::size_t
#include <stdexcept>
#include "../vector/vector.hpp"
namespace unsa {
template <typename T>
class Stack {
public:
    using value_type = T;
    using size_type = std::size_t;

    Stack();
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const noexcept;
    size_type size() const noexcept;
    void clear();

private:
    unsa::vector<T> data;
};

} // namespace unsa

#include "stack.tpp"

#endif // UNSA_STACK_HPP
