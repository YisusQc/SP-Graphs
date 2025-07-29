#ifndef UNSA_STACK_TPP
#define UNSA_STACK_TPP

namespace unsa {

template <typename T>
Stack<T>::Stack() = default;

template <typename T>
void Stack<T>::push(const T& value) {
    data.push_back(value);
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack::pop: la pila está vacía");
    }
    data.pop_back();
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack::top: la pila está vacía");
    }
    return data.back();
}
template <typename T>
bool Stack<T>::empty() const noexcept {
    return data.empty();
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const noexcept {
    return data.size();
}

template <typename T>
void Stack<T>::clear() {
    data.clear();
}

} // namespace unsa

#endif // UNSA_STACK_TPP
