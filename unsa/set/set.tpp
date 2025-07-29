#pragma once

namespace unsa {

    template<typename T>
    set<T>::set() {}

    template<typename T>
    bool set<T>::insert(const T& value) {
        if (!contains(value)) {
            data.push_back(value);
            return true;
        }
        return false;
    }

    template<typename T>
    bool set<T>::contains(const T& value) const {
        for (const auto& v : data)
            if (v == value) return true;
        return false;
    }

    template<typename T>
    bool set<T>::erase(const T& value) {
        for (std::size_t i = 0; i < data.size(); ++i) {
            if (data[i] == value) {
                for (std::size_t j = i; j + 1 < data.size(); ++j)
                    data[j] = data[j + 1];
                data.pop_back();
                return true;
            }
        }
        return false;
    }

    template<typename T>
    typename set<T>::iterator set<T>::erase(iterator it) {
        std::size_t i = it - &data[0];
        for (std::size_t j = i; j + 1 < data.size(); ++j)
            data[j] = data[j + 1];
        data.pop_back();
        return &data[i];
    }

    template<typename T>
    typename set<T>::iterator set<T>::begin() {
        return &data[0];
    }

    template<typename T>
    typename set<T>::iterator set<T>::end() {
        return &data[0] + data.size();
    }

    template<typename T>
    typename set<T>::const_iterator set<T>::begin() const {
        return &data[0];
    }

    template<typename T>
    typename set<T>::const_iterator set<T>::end() const {
        return &data[0] + data.size();
    }

    template<typename T>
    std::size_t set<T>::size() const {
        return data.size();
    }

    template<typename T>
    bool set<T>::empty() const {
        return data.empty();
    }

    template<typename T>
    std::size_t set<T>::count(const T& value) const {
      for (const auto& v : data)
          if (v == value)
              return 1;
      return 0;
    }
}

