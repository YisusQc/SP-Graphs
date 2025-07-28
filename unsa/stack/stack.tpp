#ifndef UNSA_STACK_TPP
#define UNSA_STACK_TPP

namespace unsa {

// ======================= Constructor =======================

template <typename T>
Stack<T>::Stack() = default;

// =================== Métodos públicos ===================

/**
 * @brief Inserta un nuevo elemento en la cima de la pila.
 * @param value Elemento a insertar.
 */
template <typename T>
void Stack<T>::push(const T& value) {
    data.push_back(value);
}

/**
 * @brief Elimina el elemento superior de la pila.
 * @throws std::out_of_range si la pila está vacía.
 */
template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack::pop: la pila está vacía");
    }
    data.pop_back();
}

/**
 * @brief Retorna el elemento superior sin eliminarlo.
 * @return Referencia constante al elemento en la cima.
 * @throws std::out_of_range si la pila está vacía.
 */
template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack::top: la pila está vacía");
    }
    return data.back();
}

/**
 * @brief Verifica si la pila está vacía.
 * @return true si no contiene elementos, false en caso contrario.
 */
template <typename T>
bool Stack<T>::empty() const noexcept {
    return data.empty();
}

/**
 * @brief Retorna el número de elementos en la pila.
 * @return Cantidad de elementos.
 */
template <typename T>
typename Stack<T>::size_type Stack<T>::size() const noexcept {
    return data.size();
}

/**
 * @brief Elimina todos los elementos de la pila.
 */
template <typename T>
void Stack<T>::clear() {
    data.clear();
}

} // namespace unsa

#endif // UNSA_STACK_TPP
