#pragma once

namespace unsa {

template <typename T1, typename T2>
class pair {
public:
    T1 first;
    T2 second;

    pair();
    pair(const T1& a, const T2& b);

    bool operator==(const pair& other) const;
    bool operator!=(const pair& other) const;
    bool operator<(const pair& other) const;
    bool operator>(const pair& other) const;
    bool operator<=(const pair& other) const;
    bool operator>=(const pair& other) const;
};

}  // namespace unsa

#include "pair.tpp"

