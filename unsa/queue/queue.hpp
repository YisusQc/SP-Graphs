#pragma once
#include "../vector/vector.hpp"

namespace unsa {
    template<typename T>
    class queue {
    private:
      unsa::vector<T> data;
    public:
        void push(const T& value);
        void pop();
        T& front();
        const T& front() const;
        bool empty() const;
        std::size_t size() const;
    };
}

#include "queue.tpp"
