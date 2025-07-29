#ifndef UNSA_VECTOR_HPP
#define UNSA_VECTOR_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace unsa {

template <typename T>
class vector {
private:
    T* data;
    std::size_t _size;
    std::size_t _capacity;

    void reallocate(std::size_t new_capacity);

public:
    vector();
    vector(std::initializer_list<T> init);
    vector(const vector& other);
    vector& operator=(const vector& other);
    vector(std::size_t n);
    ~vector();

    void push_back(const T& value);
    void pop_back();
    void emplace_back(T&& value);

    template <typename... Args>
    void emplace_back(Args&&... args);

    void clear();
    bool empty() const;
    std::size_t size() const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
};

} // namespace unsa

#include "vector.tpp"

#endif // UNSA_VECTOR_HPP

