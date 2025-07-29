#pragma once
#include "../vector/vector.hpp"

namespace unsa {
    template<typename T>
    class set {
    private:
        unsa::vector<T> data;

    public:
        using iterator = T*;
        using const_iterator = const T*;

        set();

        bool insert(const T& value);
        bool contains(const T& value) const;
        bool erase(const T& value);
        iterator erase(iterator it);

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        std::size_t size() const;
        bool empty() const;
        std::size_t count(const T& value) const;
    };
}

#include "set.tpp"

