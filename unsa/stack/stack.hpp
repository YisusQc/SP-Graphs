#ifndef UNSA_STACK_HPP
#define UNSA_STACK_HPP

#include <vector>   // std::vector
#include <cstddef>  // std::size_t
#include <stdexcept>

namespace unsa {

/**
 * @brief Clase plantilla que implementa una pila (Stack) LIFO.
 * 
 * Estructura de datos que permite insertar (push) y eliminar (pop)
 * elementos solo desde el tope. El último elemento insertado es el
 * primero en ser removido.
 * 
 * @tparam T Tipo de los elementos a almacenar en la pila.
 */
template <typename T>
class Stack {
public:
    using value_type = T;
    using size_type = std::size_t;

    /// Constructor por defecto
    Stack();

    /// Inserta un elemento en la cima de la pila.
    void push(const T& value);

    /// Elimina el elemento en la cima de la pila.
    void pop();

    /// Retorna una referencia constante al elemento en la cima.
    const T& top() const;

    /// Verifica si la pila está vacía.
    bool empty() const noexcept;

    /// Retorna el número de elementos almacenados en la pila.
    size_type size() const noexcept;

    /// Elimina todos los elementos de la pila.
    void clear();

private:
    std::vector<T> data;  ///< Contenedor subyacente (vector dinámico).
};

} // namespace unsa

#include "stack.tpp"

#endif // UNSA_STACK_HPP
