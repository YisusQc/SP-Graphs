#pragma once

namespace unsa {
    template<typename T>
    void queue<T>::push(const T& value) {
        data.push_back(value);
    }

    template<typename T>
    void queue<T>::pop() {
        if (!data.empty()) {
            for (size_t i = 1; i < data.size(); ++i)
                data[i - 1] = data[i];
            data.pop_back();
        }
    }

    template<typename T>
    T& queue<T>::front() {
        return data[0];
    }

    template<typename T>
    const T& queue<T>::front() const {
        return data[0];
    }

    template<typename T>
    bool queue<T>::empty() const {
        return data.empty();
    }

    template<typename T>
    std::size_t queue<T>::size() const {
        return data.size();
    }
}
