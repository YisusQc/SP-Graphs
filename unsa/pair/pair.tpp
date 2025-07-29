#pragma once

namespace unsa {

template <typename T1, typename T2>
pair<T1, T2>::pair() : first(), second() {}

template <typename T1, typename T2>
pair<T1, T2>::pair(const T1& a, const T2& b) : first(a), second(b) {}

template <typename T1, typename T2>
bool pair<T1, T2>::operator==(const pair& other) const {
    return first == other.first && second == other.second;
}

template <typename T1, typename T2>
bool pair<T1, T2>::operator!=(const pair& other) const {
    return !(*this == other);
}

template <typename T1, typename T2>
bool pair<T1, T2>::operator<(const pair& other) const {
    return first < other.first || (!(other.first < first) && second < other.second);
}

template <typename T1, typename T2>
bool pair<T1, T2>::operator>(const pair& other) const {
    return other < *this;
}

template <typename T1, typename T2>
bool pair<T1, T2>::operator<=(const pair& other) const {
    return !(other < *this);
}

template <typename T1, typename T2>
bool pair<T1, T2>::operator>=(const pair& other) const {
    return !(*this < other);
}

}  // namespace unsa

